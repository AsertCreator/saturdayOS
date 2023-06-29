import os
import copy
import sys
import json
import shutil
import fnmatch

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class MakeEngine32:
	def __init__(self):
		self.sourceext = [".c", ".cpp", ".cxx", ".c++", ".asm", ".s"];
		self.output = "";
		self.arch = 0;
		self.struct = None;

	def clean(self):
		shutil.rmtree("build" + str(self.arch));
		os.mkdir("build" + str(self.arch));

	def readfile(self, file):
		fd = open(file);
		res = fd.read();
		fd.close();
		return res;

	def listfiles(self, curdir):
		res = [];
		files = os.listdir(curdir);
		for file in files:
			if os.path.isfile(curdir + "/" + file):
				res.append(file);
		return res;
		
	def filtersource(self, files):
		res = [];
		for file in files:
			for ext in self.sourceext:
				if ext in file:
					res.append(file);
					break;
		return res;

	def compilefile(self, file, outdir, settings, link):
		obj = None;
		for ext in self.sourceext:
			if ext in file:
				obj = file.replace(ext, ".o").replace("src/", outdir) if link else file.replace(ext, "").replace("src/", outdir);
				self.mkdirut(os.path.dirname(obj))

				if ext == ".asm":
					if os.system("nasm -felf32 -o " + obj + " " + file) == 0:
						print(bcolors.OKCYAN + "\tcompiled file " + file + bcolors.ENDC);
					else:
						print(bcolors.FAIL + "\tfailed to compile file " + file + bcolors.ENDC);
						return -1;
				elif ext == ".c":
					if os.system(settings["compiler"] + " -Wall -Wextra -Werror -fms-extensions -nostdlib -o " + obj + " " + file + " -ffreestanding -mgeneral-regs-only -mno-red-zone -O0" + (" -s" if "--preserve-symbols" not in sys.argv else "") + (" -c" if link else "") + " -I " + settings["id"] + " -DARCH=" + str(self.arch)) == 0:
						print(bcolors.OKCYAN + "\tcompiled file " + file + bcolors.ENDC);
					else:
						print(bcolors.FAIL + "\tfailed to compile file " + file + bcolors.ENDC);
						return -1;
				elif ext == ".cpp":
					if os.system(settings["compiler"] + " -Wall -Wextra -Werror -fms-extensions -nostdlib  -o " + obj + " " + file + " -ffreestanding -mgeneral-regs-only -mno-red-zone -fno-exceptions -fno-asynchronous-unwind-tables -O0" + ("-s" if "--preserve-symbols" not in sys.argv else "") + (" -c" if link else "") + " -I " + settings["id"] + " -DARCH=" + str(self.arch)) == 0:
						print(bcolors.OKCYAN + "\tcompiled file " + file + bcolors.ENDC);
					else:
						print(bcolors.FAIL + "\tfailed to compile file " + file + bcolors.ENDC);
						return -1;
				break;
		return obj;

	def linkfiles(self, files, out, settings):
		if os.system(settings["linker"] + " -T " + "src/sdk/" + settings["ls"] + " -o " + out + " " + " ".join(files) + " -ffreestanding -nostdlib -lgcc -O0" + ("-s" if "--preserve-symbols" not in sys.argv else "")) == 0:
			print(bcolors.OKGREEN + "\tlinked program to " + out + bcolors.ENDC);
			return 0;
		else:
			print(bcolors.FAIL + "\tfailed to link program " + file + bcolors.ENDC);
			return 1;

	def fail(self, msg):
		print(bcolors.FAIL + "failed! msg: " + msg + bcolors.ENDC)
		sys.exit(1)

	def mkdirut(self, newdir):
		dirs = newdir.split("/");
		fulldir = "";
		for dire in dirs:
			fulldir += dire + "/";
			try: os.mkdir(fulldir); 
			except: pass;

	def makefullstruct(self):
		try: os.mkdir("build" + str(self.arch) + "/" + "iso"); 
		except: pass;

		file = open("src/sdk/systemstruct.json")
		structure = json.load(file)
		file.close()
		for dire in structure["directories"]:
			try: os.mkdir("build" + str(self.arch) + "/" + "iso/" + dire); 
			except: pass;

		self.struct = structure;

	def processpointer(self, ptr, curdir, settings):
		lines = ptr.replace("\r\n", "\n").split('\n');
		preserveobjects = False;
		objects = [];
		linked = None;
		for line in lines:
			#print(line + ", current directory: " + curdir);
			if not line.startswith("#"):
				words = line.split(' ');
				opcode = words[0];
				if opcode == "compile":
					directory = words[1];
					
					if len(words) > 2:
						prop = words[3];
						exvl = words[5];

						if prop == "arch" and int(exvl) != self.arch:
							continue

					nptr = self.readfile(curdir + "/" + directory + "/pointer.txt");
					res = self.processpointer(nptr, curdir + "/" + directory, copy.deepcopy(settings));
					if preserveobjects:
						objects += res;
				elif opcode == "compilefile":
					selector = words[1];
					files = self.listfiles(curdir);
					files = self.filtersource(files);
					files = fnmatch.filter(files, selector);
					
					try: os.mkdir("build" + str(self.arch) + "/" + curdir); 
					except: pass;

					for file in files:
						objfile = self.compilefile(curdir + "/" + file, "build" + str(self.arch) + "/", settings, True);
						if objfile == -1:
							self.fail("couldn't compile file " + file);
						if objfile != None:
							objects.append(objfile);
				elif opcode == "compilelink":
					selector = words[1];
					files = self.listfiles(curdir);
					files = self.filtersource(files);
					files = fnmatch.filter(files, selector);
					
					try: os.mkdir("build" + str(self.arch) + "/" + curdir); 
					except: pass;

					for file in files:
						linked = self.compilefile(curdir + "/" + file, "build" + str(self.arch) + "/", settings, False);
						if linked == -1:
							self.fail("couldn't compile file " + file);
				elif opcode == "linkall":
					name = words[1];
					if self.linkfiles(objects, "build" + str(self.arch) + "/" + curdir.replace("src", ".") + "/" + name, settings) == 1:
						self.fail("couldn't link program " + name);
					linked = "build" + str(self.arch) + "/" + curdir.replace("src", ".") + "/" + name;
				elif opcode == "copyto":
					to = int(words[1]);
					if to != -1:
						shutil.copy(linked, "build" + str(self.arch) + "/iso/" + self.struct["directories"][to]);
					else:
						shutil.copy(linked, "build" + str(self.arch) + "/iso/");
				elif opcode == "copyraw":
					what = words[1];
					to = int(words[2]);
					if to != -1:
						shutil.copy(curdir + "/" + what, "build" + str(self.arch) + "/iso/" + self.struct["directories"][to]);
					else:
						shutil.copy(curdir + "/" + what, "build" + str(self.arch) + "/iso/");
				elif opcode == "buildlimineiso":
					config = words[1];
					
					shutil.copy("src/" + config, "build" + str(self.arch) + "/iso/");

					cmd = """xorriso -as mkisofs -b limine-cd.bin \
-no-emul-boot -boot-load-size 4 -boot-info-table \
--efi-boot limine-cd-efi.bin -efi-boot-part \
--efi-boot-image --protective-msdos-label \
-o """ + "./build" + str(self.arch) + "/os_build.iso" + " ./build" + str(self.arch) + "/iso"

					if os.system(cmd) != 0:
						self.fail("couldn't make an iso")

					cmd = ".\src\limine\limine-deploy " + "./build" + str(self.arch) + "/os_build.iso"
					if os.system(cmd) != 0:
						self.fail("couldn't deploy limine to iso")
				elif opcode == "incdir":
					dire = int(words[1]);
					settings["id"] = dire;
				elif opcode == "freestanding":
					settings["ff"] = True;
				elif opcode == "linkscript":
					settings["ls"] = words[1];
				elif opcode == "preserveobj":
					preserveobjects = True;
		return objects;

class StartEngine32:
	def __init__(self, iso, biospath):
		self.qemu = "i386";
		self.bios = biospath;
		self.memory = 128;
		self.iso = iso

	def run(self):
		if os.system("qemu-system-" + self.qemu + " -m " + str(self.memory) + " -cdrom " + self.iso + " -pflash " + self.bios) == 0:
			print("qemu stopped successfully! i'm hoping you had fun using freshly baked saturdayOS!");
		else:
			print("uh-oh, qemu has crashed!");

if __name__ == "__main__":
	print("starting build...")
	mkengine = MakeEngine32();
	settings = {}
	settings["ff"] = False;
	settings["ls"] = "app.ld";
	settings["compiler"] = "i686-elf-gcc";
	settings["linker"] = "i686-elf-gcc";
	settings["id"] = "src/sdk/"

	if "clean" not in sys.argv:
		rootptr = mkengine.readfile("src/pointer.txt");
		if "--arch" in sys.argv:
			mkengine.arch = int(sys.argv[sys.argv.index("--arch") + 1])
		mkengine.makefullstruct();
		mkengine.processpointer(rootptr, "src", settings);
		print("built successfully")

		if "run" in sys.argv:
			stengine = StartEngine32("./build" + str(mkengine.arch) + "/os_build.iso", "\"C:/Program Files/qemu/share/edk2-i386-code.fd\"");
			stengine.run();
	else:
		mkengine.clean();
		print("cleaned successfully")
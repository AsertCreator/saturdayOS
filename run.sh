make -j$(nproc)
qemu-system-i386 -cdrom ./final/os_build.iso -m 256 -serial stdio
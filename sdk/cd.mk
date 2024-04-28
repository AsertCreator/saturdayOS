.SILENT:
all:
	echo [cd] building a cd...
	rm -rf $(OUT_DIR)/os_build.iso
	cp $(BOOT)/limine-bios-cd.bin $(OUT_DIR)/boot
	cp $(BOOT)/limine-bios.sys $(OUT_DIR)/boot
	cp $(SRC)/limine.cfg $(OUT_DIR)/boot
	xorriso -as mkisofs -b boot/limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --protective-msdos-label -o $(OUT_DIR)/os_build.iso $(OUT_DIR) >> /dev/null
.SILENT:
all:
	echo [limine] building limine...
	$(NATIVECC) -o limine ./limine.c -O2
	echo [limine] installing limine...
	./limine bios-install $(OUT_DIR)/os_build.iso >> /dev/null
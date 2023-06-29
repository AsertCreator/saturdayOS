#pragma once
#include <stdint.h>

#define ELF_MAGIC 1179403647

#define ELF_PT_NULL 0
#define ELF_PT_LOAD 1
#define ELF_PT_DYNAMIC 2
#define ELF_PT_INTERP 3
#define ELF_PT_NOTE 4
#define ELF_PT_SHLIB 5
#define ELF_PT_PHDR 6
#define ELF_PT_TLS 7
#define ELF_PF_X 1
#define ELF_PF_W 2
#define ELF_PF_R 4

#define ELF_SHT_NULL 0
#define ELF_SHT_PROGBITS 1
#define ELF_SHT_SYMTAB 2
#define ELF_SHT_STRTAB 3
#define ELF_SHT_RELA 4
#define ELF_SHT_HASH 5
#define ELF_SHT_DYNAMIC 6
#define ELF_SHT_NOTE 7
#define ELF_SHT_NOBITS 8
#define ELF_SHT_REL 9
#define ELF_SHT_SHLIB 10
#define ELF_SHT_DYNSYM 11
#define ELF_SHT_INIT_ARRAY 14
#define ELF_SHT_FINI_ARRAY 15
#define ELF_SHT_PREINIT_ARRAY 16
#define ELF_SHT_GROUP 17
#define ELF_SHT_SYMTAB_SHNDX 18
#define ELF_SHF_WRITE 0x1
#define ELF_SHF_ALLOC 0x2
#define ELF_SHF_EXECINSTR 0x4
#define ELF_SHF_MERGE 0x10
#define ELF_SHF_STRINGS 0x20
#define ELF_SHF_INFO_LINK 0x40
#define ELF_SHF_LINK_ORDER 0x80
#define ELF_SHF_OS_NONCONFORMING 0x100
#define ELF_SHF_GROUP 0x200
#define ELF_SHF_TLS 0x400
#define ELF_SHF_COMPRESSED 0x800

// ElfHeader32 "<-" SystemObject
typedef struct {
	uint32_t ei_magic;
	uint8_t ei_class;
	uint8_t ei_data;
	uint8_t ei_version;
	uint8_t ei_osabi;
	uint8_t ei_abiversion;
	uint8_t ei_pad[7];
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_version;
	uint32_t e_entry;
	uint32_t e_phoff;
	uint32_t e_shoff;
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
} ElfHeader32;

// ElfProgramHeader32 "<-" SystemObject
typedef struct {
	uint32_t p_type;
	uint32_t p_offset;
	uint32_t p_vaddr;
	uint32_t p_paddr;
	uint32_t p_filesz;
	uint32_t p_memsz;
	uint32_t p_flags;
	uint32_t p_align;
} ElfProgramHeader32;

// ElfSectionHeader32 "<-" SystemObject
typedef struct {
	uint32_t sh_name;
	uint32_t sh_type;
	uint32_t sh_flags;
	uint32_t sh_addr;
	uint32_t sh_offset;
	uint32_t sh_size;
	uint32_t sh_link;
	uint32_t sh_info;
	uint32_t sh_addralign;
	uint32_t sh_entsize;
} ElfSectionHeader32;
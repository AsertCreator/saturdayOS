ENTRY(_start)
 
SECTIONS
{
	. = 2048M;

	/* code */

	.text BLOCK(4M) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
	/* data */

	.rodata BLOCK(4M) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4M) : ALIGN(4K)
	{
		*(.data)
	}

	.bss BLOCK(4M) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
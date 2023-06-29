ENTRY(_start)
 
SECTIONS
{
	. = 4M;

	/* code */

	.text BLOCK(2M) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
	/* data */

	.rodata BLOCK(2M) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(2M) : ALIGN(4K)
	{
		*(.data)
	}

	.bss BLOCK(2M) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
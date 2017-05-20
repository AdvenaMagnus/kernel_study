ENTRY(start)

SECTIONS {
	. = 1M;

	.boot : 
	{
		*(.multiboot_header)
	}

	.text 0x1000 :
	{
		*(.text)
	}
	
	.bss :
	{
		*(.bss)
	}
}

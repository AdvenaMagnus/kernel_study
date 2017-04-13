global start
extern kernel_main

section .text
	bits 32
	start:
	;mov dword [0xb8000], 0x2f4b2f4f
	call kernel_main;
	hlt


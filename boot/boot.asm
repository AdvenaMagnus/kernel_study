global start
global write_port
global read_port
global load_idt
global load_gdt
global keyboard_handler_asm
global test_handler
global general_protection_fault_asm
global loadPageDirectory
global enablePaging
extern kernel_main
extern keyboard_handler
extern test_handler_impl
extern general_protection_fault

section .text
	bits 32
start:
	;mov dword [0xb8000], 0x2f4b2f4f
	;cli
	mov esp, stack_space
	call kernel_main;
	hlt

; write_port(port_num, value) / arguments is got from stack
write_port: 
	mov edx, [esp+4]
	mov al, [esp+4+4]
	out dx, al
	ret
read_port:
	mov edx, [esp+4]
	in al, dx
	ret
load_idt:
	mov edx, [esp+4]
	lidt [edx]
	sti
	ret

load_gdt:
	mov edx, [esp + 4]
	lgdt [edx]
	 mov ax, 0x10
   	 mov ds, ax
   	 mov es, ax
   	 mov fs, ax
   	 mov gs, ax
   	 mov ss, ax
	ret

keyboard_handler_asm:
	    pusha
;    push ds
;    push es
;    push fs
;    push gs
;    mov ax, 0x10
;    mov ds, ax
;    mov es, ax
;    mov fs, ax
;    mov gs, ax
;    mov eax, esp
;    push eax
	cld
	call keyboard_handler
	;mov dword [0xb8000], 0x2f4b2f4f

	;pop eax
;	pop esp
;    pop gs
;    pop fs
;    pop es
;    pop ds
    popa
	sti
   ;add esp, 8
	ret

test_handler:
	;cli
	 pusha
    push ds
    push es
    push fs
    push gs
	push eax
	mov dword [0xb8000 + 80*2], 0x2f4b2f4f
	;call test_handler_impl
	;call keyboard_handler
	    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
	iretd
general_protection_fault_asm:
	;call general_protection_fault
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    call general_protection_fault
    mov dword [0xb8000 + 2*80*2], 0x2f4b2f4f

    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

loadPageDirectory:
	push ebp
	mov ebp, esp
	mov eax, [esp+8]
	mov cr3, eax
	mov esp, ebp
	pop ebp
	ret

enablePaging:
	push ebp
	mov ebp, esp
	mov eax, cr0
	or eax, 0x80000000
	mov cr0,  eax
	mov esp, ebp
	pop ebp
	ret

section .bss
resb 8192;
stack_space:

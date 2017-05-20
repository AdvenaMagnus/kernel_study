#include "keyboard_map.h"

extern write_port(unsigned short port, unsigned char data);
extern read_port(unsigned short port);
//extern load_gdt(struct gdt_ptr *gdt_ptr);
extern load_idt(struct idtr_val  *val);
extern keyboard_handler_asm(void);
extern test_handler(void);
extern general_protection_fault_asm(void);

void keyboard_handler();
void test_handler_impl();
void general_protection_fault();
void init_pics();

struct IDT_entry {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits; 
	
}__attribute__((packed));

/* struct IDT_entry2 {
        unsigned short int offset_lowerbits;
        unsigned short int selector;
        unsigned short int conf;
        unsigned short int offset_higherbits; 
}__attribute__((packed)); */


struct idtr_val {
	unsigned short length;
	unsigned long base;
}__attribute__((packed));

struct IDT_entry IDT[256];
//struct IDT_entry2 IDT2[256];

//bool enter_fired = false;
typedef int bool;
enum { false, true };
bool button_pressed = false;

char keyboard_buff[80];
unsigned int keyboard_buffCount = 0;



void keyboard_init(){
	write_string("Initialize keyboard");
	//unsigned long keyboard_address = (unsigned long) keyboard_handler;
	unsigned long keyboard_address =(unsigned long) keyboard_handler_asm;
	unsigned long test_handler_address =(unsigned long) test_handler;
	unsigned long general_protection_address =(unsigned long) general_protection_fault_asm;
	int i=0;
	//for(i; i<32; i++){
	//	IDT2[i].offset_lowerbits = keyboard_address & 0xffff;
        //	IDT2[i].selector = 0x08;
        //	IDT2[i].conf = 0b0000000011100001;
        //	IDT2[i].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;
	//}
	 for(i; i<32; i++){
		//IDT[i].offset_lowerbits = test_handler_address & 0xffff;
		IDT[i].offset_lowerbits = test_handler_address & 0xffff;
	       	IDT[i].selector = 0x08;
	      	IDT[i].zero = 0;
	    	 IDT[i].type_attr = 0x8e;
	  	 IDT[i].offset_higherbits = (test_handler_address >> 16) & 0xffff;
	}
	 IDT[13].offset_lowerbits = general_protection_address   & 0xffff;
         IDT[13].selector = 0x08;
         IDT[13].zero = 0;
         IDT[13].type_attr = 0x8e;
         IDT[13].offset_higherbits = ( general_protection_address >> 16) & 0xffff;

	for(i; i<34; i++){
		 IDT[i].offset_lowerbits = keyboard_address & 0xffff;
                IDT[i].selector = 0x08;
                IDT[i].zero = 0;
                 IDT[i].type_attr = 0x8e;
                 IDT[i].offset_higherbits = (keyboard_address >> 16) & 0xffff;

	}

	struct idtr_val idtv;
	idtv.length = 256*8-1;
	idtv.base = &IDT;
	load_idt(&idtv);

	init_pics();
	write_port(0x21, 0xFD);
}

void init_pics(void){
	write_port(0x20, 0x11);
        write_port(0xA0, 0x11);

        //write_port(0x21, 0x20);
        //write_port(0xA1, 0x28);

	write_port(0x21, 0x20);
        write_port(0xA1, 0x28);


        write_port(0x21, 0x04);
        write_port(0xA1, 0x02);

        write_port(0x21, 0x01);
        write_port(0xA1, 0x01);

        write_port(0x21, 0x0);
       	write_port(0xA1, 0x0);
}

void keyboard_handler(){
	/* write EOI */
	write_port(0x20, 0x20);
	//write_port(0xA0, 0x20);

	unsigned char status = read_port(0x64);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		char keycode = read_port(0x60);
		if(keycode > 0) {
			/*
			if(keyboard_map[keycode]=='\n'){
				enter_fired=true;
				keyboard_buff[keyboard_buffCount]='\0';
				//keyboard_buffCount=0;
				//printc(keyboard_map[keycode]);
				return;
			} */
			button_pressed=true;
			keyboard_buff[keyboard_buffCount]=keyboard_map[keycode];
			keyboard_buffCount = keyboard_buffCount+1;
			//printc(keyboard_map[keycode]);
			return;
		} else {
			button_pressed=false;
		}
	}

}

void test_handler_impl(){
	write_string("test_handler");
}

void general_protection_fault(){
	write_string("general protection fault");
}

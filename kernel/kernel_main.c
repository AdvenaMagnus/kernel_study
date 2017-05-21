#include "types.h"
#include "screen_init.h"
#include "paging.h"
#include "keyboard_init.h"
#include "gdt_init.h"
#include "console.h"

void kernel_main(void){
	clearScreen();
	paging_init();
	write_string("Starting kernel...");
	gdt_install();
	keyboard_init();

	run_console();

}


void test_func(void){
	write_string("mustnt be shown");
}





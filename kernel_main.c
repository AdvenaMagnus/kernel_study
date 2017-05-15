#include "screen_init.h"
#include "keyboard_init.h"
//#include "gdt_init.h"
#include "gdt_init2.h"
#include "console.h"

//void write_string(char* str);
//void clearScreen();
//static int lineCount = 0;

bool strcmp(char* str1, char* str2){
	int size1=0;
	int size2=0;
	int i=0;
	while(str1[size1]!='\0'){
		size1++;
	}
	while(str2[size2]!='\0'){
		size2++;
	}
	if(size1 == size2){
		for(i=0;i<size1;i++){
			if(str1[i] != str2[i]) return false;
		}
		return true;
	}
	return false;
}

void kernel_main(void){
	clearScreen();
	write_string("Starting kernel...");
	//gdt_init();
	gdt_install();
	keyboard_init();

	run_console();

}


void test_func(void){
	write_string("mustnt be shown");
}





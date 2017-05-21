void dispatch_command(char* command);

void run_console(){
	while(1){
		keyboard_buffCount = 0;
		printc('>');
		while(1){
                	asm volatile ("hlt");
			if(button_pressed==true){
				if(keyboard_buff[keyboard_buffCount-1]=='\n'){
					printc(keyboard_buff[keyboard_buffCount-1]);
					keyboard_buff[keyboard_buffCount-1]='\0';
					break;
				}
				if(keyboard_buff[keyboard_buffCount-1]=='\b'){
					keyboard_buffCount = keyboard_buffCount-2;
					printc(keyboard_buff[keyboard_buffCount+1]);
					continue;
				}
				printc(keyboard_buff[keyboard_buffCount-1]);
			}
        	}
		//write_string(keyboard_buff);
		dispatch_command(keyboard_buff);
	}
}

void dispatch_command(char* command){
	if(strcmp("reboot", command)){
		write_string("reboot");
		asm volatile ("cli");
		write_port(0x64, 0xfe);
	}
	if(strcmp("help", command)){
		write_string("reboot - Reboot OS;");
		write_string("clear - Clear screen;");
	}
	if(strcmp("clear", command)){
		clearScreen();
	}
}


void write_string(char* str){
	char *vidptr = (char*)0xb8000;
	int j=0, i=0;
	while(str[j]!='\0'){
		vidptr[i] = str[j];
		vidptr[i+1] = 0x07;
		j++;
		i = i+2;
	}
	return;
}

void kernel_main(void){
	write_string("string from kernel_main \n");
}

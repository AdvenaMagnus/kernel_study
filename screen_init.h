static int lineCount = 0;
static int charCount = 0;

void write_string(char* str){
        //char *vidptr = (char*)0xb8000;
        char *vidptr = (char*)(0xb8000+lineCount);
        int j=0, i=0;
        while(str[j]!='\0'){
                vidptr[i] = str[j];
                vidptr[i+1] = 0x07;
                j++;
                i = i+2;
        }
        lineCount = lineCount + 80*2;
        return;
}

void clearScreen(){
        char *screen = (char*)0xb8000;
        int j=0;
        while(j<80*25*2){
                screen[j] = ' ';
                screen[j+1]=0x07;
                j = j+2;
        }
	lineCount=0;
	charCount=0;
}

void printc(char c){
	char *vidptr = (char*) (0xb8000+lineCount+charCount);
	if(c=='\n'){
		 lineCount = lineCount+ 80*2;
		charCount = 0;
		return;
	}
	if(c=='\b'){
		vidptr = (char*) (0xb8000+lineCount+charCount-2);
		vidptr[0] = ' ';
		vidptr[1] = 0x07;
		charCount=charCount-2;
		return;
	}
	vidptr[0] = c;
        vidptr[1] = 0x07;
	charCount = charCount+2;

}


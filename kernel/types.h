typedef int bool;
enum { false, true };
bool button_pressed = false;

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


#include "ADT.h"

char checksum_str(char* x, int length) {
	int n = 0;
	while(length--) {
		n += (char) *(x++);
	}
	return (char) n;
}

struct frame initialize_frame(int SequentialNumber, int Length, char* buff){
    struct frame temp;
    temp.SOH = 0x1;
    temp.SeqNum = SequentialNumber;
    temp.DataLength = Length;
    int i = SequentialNumber-1;
    int j = 0;
    stringToBinary(buff);
    //char CheckSum;
    return temp;
}

char* stringToBinary(char* s) {
    if(s == NULL) return 0; /* no input string */
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

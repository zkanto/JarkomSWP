#include <stdio.h>
#include <stdlib.h>
#include <ADT.h>

char checksum_str(char* x, int length) {
	int n = 0;
	while(length--) {
		n += (char) *(x++);
	}
	return (char) n;
}

frame initialize_frame(int SequentialNumber, int Length, char buff[]){
    SOH = 0x1;
    SeqNum = SequentialNumber;
    DataLength = Length;
    int i = SequentialNumber-1;
    int j = 0;
    char* c = buff[i][j];
    array_frame[i].Data = malloc (sizeof (char) * 1024);
    strcpy(array_frame[i].Data, c);
    while ((j<=1023) && (buff[i][j] != '\0')){
        if((i!=0)||(j!=0)){
            char* c = buff[i][j];
            strcat(array_frame[i].Data, c);
        }
        j++;
    }
    //char CheckSum;
}

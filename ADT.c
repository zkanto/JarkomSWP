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
    if(s == NULL) return 0; // no input string
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    size_t i;
    int j;
    for(i = 0; i < len; ++i) {
        char ch = s[i];
        for(j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

struct ACK initialize_ack(char ack, int NextSequentialNumber) {
    struct ACK a;
    a.ACK = ack;
    a.NextSeqNum = NextSequentialNumber;
    return a;
}


void printcharbin(char a) {
    char x = a;
    int i;
    printf(">");
    for (i = 0; i < 8; i++) {
        printf("%d", !!((x << i) & 0x80));
    }
    printf("\n");
}

unsigned char checksum(char* x, int length) {
    unsigned char sumtemp = 0;
    unsigned char sum = 0;
    unsigned char temp = 0;
    int i;
    for (i = 0; i < length; i++) {
        temp = x[i];
        sumtemp = sum;
        sum = sum + temp;
        if (sumtemp > sum) {
            sum++;
        }
    }
    return ~sum;
}

void printbinary(struct ACK a) {
    char x = a.ACK;
    char y = a.CheckSum;
    int i, c, k;
    int n = a.NextSeqNum;
    for (i = 0; i < 8; i++) {
        printf("%d", !!((x << i) & 0x80));
    }
    printf("\n");
    for (c = 31; c >= 0; c--) {
        k = n >> c;
        if (k&1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
    for (i = 0; i < 8; i++) {
        printf("%d", !!((y << i) & 0x80));
    }
    printf("\n");
}

int checksumvalid(struct ACK a) {
    char chksum = a.CheckSum;
    char b = checksum(&(a.ACK), 5);
    if (chksum == b) {
        return 1;
    } else {
        return 0;
    }
}

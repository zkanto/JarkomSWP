#include "ADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define DATALEN 1024

struct serverSWP{
    int LAR;
    int SWS;
    int LFS;
    int BufferSize;
};

void die(char* s) {
    perror(s);
    exit(1);
}

/*
void SWP (struct clientSWP client, ...) {

}

*/

int main (int argc, char* argv[]) {
    if (argc < 6) {
        perror("filename windowsize buffersize destinationIp port");
        exit(1);
    }

    char* filename = argv[1];
    int windowsize = atoi(argv[2]);
    int buffersize = atoi(argv[3]);
    char* destinationIp = argv[4];
    int port = atoi(argv[5]);

    // Test socket
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char *buff[buffersize];
 
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(port);
     
    if (inet_aton(destinationIp , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    //printf("Enter buff : ");
    //gets(buff);
    for (i = 0; i < buffersize; i++) {
        buff[i] = (char*) malloc(DATALEN*sizeof(char));
    }

    int length_frame[buffersize];
    int j;

    for (i = 0; i < buffersize; i++) {
        for (j = 0; j < 1024; j++) {
            buff[i][j] = '\0';
        }
    }



    FILE *fileinput = fopen("input.txt", "r");
    i = 0; j = 0;
    
    while (!feof(fileinput)){
        do {
            buff[j][i] = fgetc(fileinput);
            i++;
        } while (i < DATALEN);
        length_frame[j] = i;
        i = 0;
        j++;
    }

    fclose(fileinput);
         
    struct frame *packet[j];

    for (i = 0; i < j; i++) {
        packet[i] = (struct frame *) malloc(sizeof(struct frame));
        packet[i]->SOH = 0x1;
        packet[i]->SeqNum = i+1;
        packet[i]->DataLength = length_frame[i];
        packet[i]->Data = (char*) malloc(DATALEN*sizeof(char));
        memcpy(packet[i]->Data, buff[i], DATALEN);
        packet[i]->Data[DATALEN] = '\0';
        packet[i]->CheckSum = 0x43; //checksum dummy, fix later
        
    }


    char sendpacket[1034];
    sendpacket[0] = packet[0]->SOH;
    memcpy(sendpacket+1, &(packet[0]->SeqNum), 4);
    memcpy(sendpacket+5, &(packet[0]->DataLength), 4);
    memcpy(sendpacket+9, packet[0]->Data, 1024);
    memcpy(sendpacket+1033, &(packet[0]->CheckSum), 1);

    printf("%s\n", sendpacket+9);
    
    //int k = 0;
    //while (k < j) {
        if (sendto(s, sendpacket, 1034 , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
        //k++;
    //}
    
    //printf("%s", packet[0]->Data);

    close(s);
    return 0;

/*
    
    char *buff[buffersize];
    int i, j, k, l;
    for (i = 0; i < buffersize; i++) {
        buff[i] = (char*) malloc(1024*sizeof(char));
    }

    for (i = 0; i < buffersize; i++) {
        for (j = 0; j < 1024; j++) {
            buff[i][j] = '\0';
        }
    }

    FILE *fileinput = fopen(filename, "r");
    i = 0;
    j = 0;

    do {
        buff[i][j] = fgetc(fileinput);
        if (j == 1023) {
            //buff[i][1023] = '\0';
            j=0;
            i++;
        } else {
            j++;
        }
    } while (buff[i][j] == feof(fileinput));
    fclose(fileinput);
    
    int length = i;

    
    i = 0;
    do {
        printf("%s", buff[i]);
        i++;
    } while (i <= length);

    return 0;
}
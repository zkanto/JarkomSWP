#include "ADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 1024

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
        buff[i] = (char*) malloc(BUFLEN*sizeof(char));
    }
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
        } while (i < BUFLEN);
        j++;
        i = 0;
    }

    fclose(fileinput);
         
        //send the buff
    int k = 0;
    while (k < j) {
        if (sendto(s, buff[k], BUFLEN , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
        k++;
    }
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
    
    FILE *fileoutput = fopen("output.txt", "w");
    for (i = 0; i <= length; i++) {
        if (i == length) {
            fwrite(buff[i], j-1, 1, fileoutput);    
        } else {
            fwrite(buff[i], 1024, 1, fileoutput);
        }
    }
    fclose(fileoutput);

    for (i = 0; i < buffersize; i++) {
        free(buff[i]);
    }

    */

    //printf("%s %d %d %d\n", filename, windowsize, buffersize, port);

    /*
    
    struct ACK a = initialize_ack(48, 56);
    char *x = &(a.ACK);
    a.CheckSum = checksum(x, 5);

    printf("%c %d %c\n", a.ACK, a.NextSeqNum, a.CheckSum);

    if (checksumvalid(a)) {
        printf("ACK valid!");
    } else {
        printf("ACK not valid!");
    }*/

    return 0;
}
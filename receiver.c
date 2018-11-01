#include "ADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 1024
struct clientSWP {
    int LFS;
    int RWS;
    int LAF;
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
    if (argc < 5) {
        die("filename windowsize buffersize port");
    }

    char* filename = argv[1];
    int windowsize = atoi(argv[2]);
    int buffersize = atoi(argv[3]);
    int port = atoi(argv[4]);
    
    /*
    struct clientSWP client;
    client.RWS = windowsize;
    client.LFS = 0;
    client.LAF = client.RWS + client.LFS;
    client.BufferSize = buffersize;
    */
    //printf("WORKS!");

    struct sockaddr_in si_me, si_other;
     
    int s, i, slen = sizeof(si_other) , recv_len;
    char buf[1034];
     
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     
    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);
         
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, 1034, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n" , buf+9);

        for (i = 0; i < BUFLEN; i++) {
            buf[i] = '0';
        }
         
    }
    
    //print details of the client/peer and the data received
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

    FILE *fileinput = fopen("test.txt", "r");
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
    
    int length = i;

    fclose(fileinput);

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

    //printf("%c %d %c\n", a.ACK, a.NextSeqNum, a.CheckSum);

    if (checksumvalid(a)) {
        printf("ACK valid!");
    } else {
        printf("ACK not valid!");
    }

    */
    return 0;
}
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

#define SEGMENTSIZE 9
/*
typedef struct {
  segment* segments;
  int length;
} BufferArray;
*/
void initsocket(int* udpSocket, int port){
    /*Create UDP socket*/
    *udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(*udpSocket < 0){
        die("Failed create UDP Socket");
    }

    /*Configure settings in address struct*/
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // setting timeout
    struct timeval tv;
    tv.tv_sec = 0.5;
    tv.tv_usec = 0;  // Not init'ing this can cause strange errors
    setsockopt(*udpSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval));

    /*Bind socket with address struct*/
    if(bind(*udpSocket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        die("Couldn't bind socket");
    }

    printf("[%d] socket success on port %d\n", (int) time(0), port);
    fflush(stdout);
}

void writeToFile(char* filename, char* message, int n) {
    for(int i=0; i<n; i++){
        printf("WRITE : %c\n", message[i]);
    }
    FILE *fp;
    fp=fopen(filename, "a+");
    fwrite(message, sizeof(message[0]), n, fp);
    fclose(fp);
}

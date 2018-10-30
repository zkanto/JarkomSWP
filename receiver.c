#include "ADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[]) {
    if (argc < 5) {
        printf("filename windowsize buffersize port");
        exit(1);
    }

    char* filename = argv[1];
    int windowsize = atoi(argv[2]);
    int buffersize = atoi(argv[3]);
    int port = atoi(argv[4]);
    printf("%s %d %d %d\n", filename, windowsize, buffersize, port);

    struct ACK a = initialize_ack(48, 56);
    char *x = &(a.ACK);
    a.CheckSum = checksum(x, 5);

    printf("%c %d %c\n", a.ACK, a.NextSeqNum, a.CheckSum);

    if (checksumvalid(a)) {
        printf("ACK valid!");
    } else {
        printf("ACK not valid!");
    }
    return 0;
}
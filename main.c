#include "ADT.h"
#include <arpa/inet.h>
#include <sys/socket.h>

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

int readfile(char* file, char buff[9999][1024], int* length_frame){
    //read from file and fill to buff and length frame
    FILE *fileinput = fopen(file, "r");
    int i = 0;
    int j = 0;
    do {
        buff[i][j] = fgetc(fileinput);
        if(j==1023){
            j=0;
            i++;
            length_frame[i] = 1024;
            //printf("Frame %i: %s\n WITH LENGTH: %i\n",i,buff[i-1],length_frame[i]);
        }
        else{
            j++;
        }
        if(feof(fileinput)){
            length_frame[i] = j;
        }
    } while(buff[i][j]==feof(fileinput));
    //printf("Frame %i: %s\n WITH LENGTH: %i\n",i+1,buff[i],length_frame[i]);
    fclose(fileinput);
    return i;
}

void SWP(int s, char* destinationIp, struct sockaddr_in si_other, int slen, struct serverSWP server, struct frame* array_frame, int total_frame){
    struct sendpacket receiver_buffer[server.BufferSize];
    int i=0;
    int MaxSeqNum = total_frame;
	char sendpacket[1034];
    while(1){
        while((total_frame > 0) ||(server.BufferSize > 0)){
			if(receiver_buffer[i].packet.SOH =='\0'){
				receiver_buffer[i].packet = array_frame[i];
				total_frame --;
				server.BufferSize--;
			}
			i++;
        }
		for(i = 0; i <= ReceiverWindowSize; i++){
			char sendpacket[1034];
			sendpacket[0] = receiver_buffer[i].packet.SOH;
			memcpy(sendpacket+1, &(receiver_buffer[i].packet.SeqNum), 4);
			memcpy(sendpacket+5, &(receiver_buffer[i].packet.DataLength), 4);
			memcpy(sendpacket+9, receiver_buffer[i].packet.Data, 1024);
			memcpy(sendpacket+1033, &(receiver_buffer[i].packet.CheckSum), 1);
			if((server.LAR == receiver_buffer[i].packet.SeqNum) && (ReceiverWindowSize_now != 0)) {
				if (sendto(s, sendpacket, 10 + receiver_buffer[i].packet.DataLength , 0 , (struct sockaddr *) &si_other, slen)==-1){
					die("sendto()");
				}
				printf("Message with SeqNum %i has been sent", receiver_buffer[i].packet.SeqNum);
			}		
		}
        time_t temptime, time_ACK_arrived,time_now;
        temptime = time(NULL);
        receiver_buffer[server.LAR].time = temptime;
        ReceiverWindowSize--;
        //if ACK is found within time
        /*time_now = time(NULL);
        for(i=0; i <= sizeof(receiver_buffer)-1 ;i++){
            if((receiver_buffer[i].time != NULL) &&(difftime(receiver_buffer[i].time,time_now) > 1)){
                //send again
                temptime = time(NULL);
                receiver_buffer[i].time = temptime;
            }
        }*/
        /*if(ACK){
            time(time_ACK_arrived);
            double diff_t = difftime(time_ACK_arrived, array_frame[ACK.NextSeqNum-1].time);
            if((ACK.CheckSum == array_frame[ACK.NextSeqNum-1].packet.CheckSum) &&(diff_t > 0.1) &&(ACK.ACK == '1')){
                receiver_buffer[server.LAR] = NULL;
                server.LAR = NextSeqNum-1;
                server.LFS = server.LAR + server.SWS;
                total_frame--;
            }
            else if((diff_t > 0.0001) &&(ACK.ACK == '0')){
                //send again
                temptime = time(NULL);
                receiver_buffer[i].time = temptime;
            }
            else
        }
        if((total_frame == 0)&&(MaxSeqNum == server.LAR)){
            break; //done
        }
        */
    }
}

int main(int argc, char* argv[]){
    if (argc < 6) {
        perror("filename windowsize buffersize destinationIp port");
        exit(1);
    }
    // Test socket
    struct sockaddr_in si_other;
    int s, slen=sizeof(si_other), recv_len;
    char* destinationIp = argv[4];
    int port = atoi(argv[5]);

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(port);

    if (inet_aton(destinationIp , &si_other.sin_addr) == 0){
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    static char buff[9999][1024];
    int length_frame[9999];
    int i = 0;
    int j = 0;
    struct frame array_frame[9999];
    char* framedata[9999];
    char* file_name = argv[1];
    int total_frame = readfile(file_name, buff, length_frame);
    for (i=0;i<=total_frame;i++){
        array_frame[i] = initialize_frame(i+1, length_frame[i], buff[i]);
        printf("SOH : %x\n",array_frame[i].SOH);
        printf("SeqNum : %i\n",array_frame[i].SeqNum);
        printf("Data Length : %i\n",array_frame[i].DataLength);
        printf("Data : %s\n",array_frame[i].Data);
        printf("CheckSum : %x\n",array_frame[i].CheckSum);
    }
    struct serverSWP server;
    server.LAR = 0;
    server.SWS = atoi(argv[2]);
    server.LFS = server.LAR + server.SWS;
    server.BufferSize = atoi(argv[3]);
    SWP(s, destinationIp, si_other, slen, server, array_frame, total_frame);
    return 0;
}

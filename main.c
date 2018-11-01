#include "ADT.h"

struct serverSWP{
    int LAR;
    int SWS;
    int LFS;
    int BufferSize;
};

int readfile(char* file, char buff[][1024], int* length_frame){
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
        if(buff[i][j]==feof(fileinput)){
            length_frame[i] = j;
        }
    } while(buff[i][j]==feof(fileinput));
    //printf("Frame %i: %s\n WITH LENGTH: %i\n",i+1,buff[i],length_frame[i]);
    fclose(fileinput);
    return i;
}

void SWP(struct serverSWP server, struct frame* array_frame, int ReceiverWindowSize, int total_frame){
    struct sendpacket receiver_buffer[server.BufferSize];
    int i=0;
    while((total_frame > 0) ||(server.BufferSize > 0)){
        receiver_buffer[i].packet = array_frame[i];
        total_frame --;
        server.BufferSize--;
        i++;
    }
    while(1){
        //kirim ke socket
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
            if((ACK.CheckSum == array_frame[ACK.NextSeqNum-1].packet.CheckSum) &&(diff_t > 0.0001) &&(ACK.ACK == '1')){
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
        }
        if(total_frame == 0){
            break; //done
        }
        */
    }
}

int main(){
    static char buff[9999][1024];
    int length_frame[9999];
    int i = 0;
    int j = 0;
    struct frame array_frame[9999];
    char* framedata[9999];
    int ReceiverWindowSize;
    int total_frame = readfile("input.txt", buff, length_frame);
    //printf("%i",total_frame);
    for (i=0;i<=total_frame;i++){
        //printf("%i",length_frame[i]);
        array_frame[i] = initialize_frame(i+1, length_frame[i], buff[i]);
        printf("SOH : %x\n",array_frame[i].SOH);
        printf("SeqNum : %i\n",array_frame[i].SeqNum);
        printf("Data Length : %i\n",array_frame[i].DataLength);
        //printf("SOH : %x\n",array_frame[i].SOH);
        //printf("SOH : %x\n",array_frame[i].SOH);
    }

    struct serverSWP server;
    server.LAR = 0;
    server.SWS = 4; //depends on senderwindowsize
    server.LFS = server.LAR + server.SWS;
    server.BufferSize = 10; //depends on buffer size
    //Listen to connection, Receiver must send the buffersize
    scanf("%i",&ReceiverWindowSize);
    if(ReceiverWindowSize != 0){
        printf("Yeay!");
        //SWP(server, array_frame, ReceiverWindowSize, total_frame);
    }
    return 0;
}

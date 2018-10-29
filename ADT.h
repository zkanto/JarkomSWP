#ifndef ADT_H_INCLUDED
#define ADT_H_INCLUDED
struct frame{
    char SOH;
    int SeqNum;
    int DataLength;
    char* Data;
    char CheckSum;
};

struct ACK{
    char ACK;
    int NextSeqNum;
    char CheckSum;
};

frame initialize_frame(int SequentialNumber, int Length, char buff[][]);



#endif // ADT_H_INCLUDED

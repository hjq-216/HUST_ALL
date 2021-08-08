//
// Created by huangjunqidemac on 2020/10/29.
//

#ifndef SR_SRRDTSENDER_H
#define SR_SRRDTSENDER_H
#include "RdtSender.h"

typedef struct SRPacket{
    Packet sendPacket;
    int ack;
}SRPacket;
class SRRdtSender : public RdtSender{
    int nextSeq;
    int base;
    int sendnum;
    bool waitingState;
    Packet packetwaitingAck;
    int PacketWaitingSeqnum;
    SRPacket packetWindows[4];
public:
    bool getWaitingState();
    bool send(const Message& message);
    void receive(const Packet& ackPkt);
    void timeoutHandler(int seqNum);
    SRRdtSender();
    virtual ~SRRdtSender();
};
#endif //SR_SRRDTSENDER_H

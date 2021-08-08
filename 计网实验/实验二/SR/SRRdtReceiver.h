//
// Created by huangjunqidemac on 2020/10/29.
//

#ifndef SR_SRRDTRECEIVER_H
#define SR_SRRDTRECEIVER_H
#include "RdtReceiver.h"

typedef struct RcvPacket{
    Packet rcv;
    int cache;
}RcvPacket;

class SRRdtReceiver: public RdtReceiver {
    int expectSequenceNumber;
    Packet lastAckPkt;
    RcvPacket RcvpacketWindow[4];
    int N;
    int rcv_base;
public:
    SRRdtReceiver();
    virtual ~SRRdtReceiver();
    void receive(const Packet& packet);
};


#endif //SR_SRRDTRECEIVER_H

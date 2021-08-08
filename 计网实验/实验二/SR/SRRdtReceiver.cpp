//
// Created by huangjunqidemac on 2020/10/29.
//

#include "SRRdtReceiver.h"
#include "Global.h"
#include "stdafx.h"
SRRdtReceiver::SRRdtReceiver() {
    expectSequenceNumber=0;
    lastAckPkt.acknum=-1;
    lastAckPkt.checksum=0;
    lastAckPkt.seqnum=-1;
    rcv_base=0;
    N=0;
    for(int i=0;i<Configuration::PAYLOAD_SIZE;i++){
        lastAckPkt.payload[i]='.';
    }
    for(int i=0;i<4;i++){
        RcvpacketWindow[i].cache=0;
        RcvpacketWindow[i].rcv=lastAckPkt;
    }
    lastAckPkt.checksum=pUtils->calculateCheckSum(lastAckPkt);
}

SRRdtReceiver::~SRRdtReceiver() {

}
void SRRdtReceiver::receive(const Packet &packet) {
    int checkSum=pUtils->calculateCheckSum(packet);
    int i=0;
    int a,b,c;
    if(checkSum==packet.checksum){
        a = this->rcv_base <= (this->rcv_base + 4)%8;
        b = packet.seqnum >= this->rcv_base && packet.seqnum < (this->rcv_base + 4)%8;
        c = packet.seqnum >= this->rcv_base || packet.seqnum < (this->rcv_base + 4)%8;
        if((a&&b) || ((!a)&&c)){

            RcvpacketWindow[(packet.seqnum-rcv_base+8)%8].cache=1;
            RcvpacketWindow[(packet.seqnum-rcv_base+8)%8].rcv=packet;
            pUtils->printPacket("接收方正确收到发送方的报文",packet);
            if(N<4) N++;
            printf("窗口大小%d",N);
            printf("\n*********************接收方：窗口滑动前***********************\n");
            for (i = 0; i < 4; i++)
            {
                if (this->RcvpacketWindow[i].rcv.seqnum != -1)
                {
                    printf("报文序号：%d cahes：%d\t", this->RcvpacketWindow[i].rcv.seqnum, this->RcvpacketWindow[i].cache);
                    pUtils->printPacket("报文内容：",this->RcvpacketWindow[i].rcv);
                }
            }
            printf("*********************接收方：窗口滑动前***********************\n\n");

            i=0;
            lastAckPkt.acknum=packet.seqnum;
            lastAckPkt.checksum=pUtils->calculateCheckSum(lastAckPkt);
            pUtils->printPacket("接收方发送确认报文", lastAckPkt);
            //调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
            pns->sendToNetworkLayer(SENDER, lastAckPkt);

            int prercv_base=rcv_base;
            while (RcvpacketWindow[i].cache!=0&&i<4){
                Message msg;
                memcpy(msg.data,RcvpacketWindow[i].rcv.payload,sizeof(RcvpacketWindow->rcv.payload));
                pns->delivertoAppLayer(RECEIVER,msg);
                rcv_base=(rcv_base+1)%8;
                i++;
                N--;
            }

            int j=(rcv_base-prercv_base+8)%8;
            i=0;
            while(j<4){
                RcvpacketWindow[i]=RcvpacketWindow[j];
                i++;
                j++;
            }
            while (i < 4)									//将移动后空出来的窗口置零
            {
                this->RcvpacketWindow[i].cache = 0;
                this->RcvpacketWindow[i].rcv.seqnum = -1;
                i++;
            }
            printf("\n*********************接收方：窗口滑动后***********************\n");
            for (i = 0; i < 4; i++)
            {
                if (this->RcvpacketWindow[i].rcv.seqnum != -1)
                {
                    printf("报文序号：%d cache: %d\t", this->RcvpacketWindow[i].rcv.seqnum, this->RcvpacketWindow[i].cache);
                    pUtils->printPacket("报文内容：", this->RcvpacketWindow[i].rcv);
                }
            }
            printf("*********************接收方：窗口滑动后***********************\n\n");
        }
        else{
            //窗口序号在[rcvbase-N, rcvbase-1]时发送ACK
            a = (this->rcv_base - 4 + 8) % 8 < (this->rcv_base) % 8;
            b = packet.seqnum >= (this->rcv_base - 4+8) % 8 && packet.seqnum < (this->rcv_base) % 8;
            c = packet.seqnum >= (this->rcv_base - 4+8) % 8 || packet.seqnum < (this->rcv_base) % 8;
            if ((a && b) || ((!a) && c))
            {
                lastAckPkt.acknum = packet.seqnum;								//确认序号等于收到的报文序号
                lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
                pUtils->printPacket("接收方发送确认报文", lastAckPkt);
                //调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
                pns->sendToNetworkLayer(SENDER, lastAckPkt);
            }
    }

    }
}
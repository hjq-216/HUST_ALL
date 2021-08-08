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
            pUtils->printPacket("���շ���ȷ�յ����ͷ��ı���",packet);
            if(N<4) N++;
            printf("���ڴ�С%d",N);
            printf("\n*********************���շ������ڻ���ǰ***********************\n");
            for (i = 0; i < 4; i++)
            {
                if (this->RcvpacketWindow[i].rcv.seqnum != -1)
                {
                    printf("������ţ�%d cahes��%d\t", this->RcvpacketWindow[i].rcv.seqnum, this->RcvpacketWindow[i].cache);
                    pUtils->printPacket("�������ݣ�",this->RcvpacketWindow[i].rcv);
                }
            }
            printf("*********************���շ������ڻ���ǰ***********************\n\n");

            i=0;
            lastAckPkt.acknum=packet.seqnum;
            lastAckPkt.checksum=pUtils->calculateCheckSum(lastAckPkt);
            pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
            //����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�
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
            while (i < 4)									//���ƶ���ճ����Ĵ�������
            {
                this->RcvpacketWindow[i].cache = 0;
                this->RcvpacketWindow[i].rcv.seqnum = -1;
                i++;
            }
            printf("\n*********************���շ������ڻ�����***********************\n");
            for (i = 0; i < 4; i++)
            {
                if (this->RcvpacketWindow[i].rcv.seqnum != -1)
                {
                    printf("������ţ�%d cache: %d\t", this->RcvpacketWindow[i].rcv.seqnum, this->RcvpacketWindow[i].cache);
                    pUtils->printPacket("�������ݣ�", this->RcvpacketWindow[i].rcv);
                }
            }
            printf("*********************���շ������ڻ�����***********************\n\n");
        }
        else{
            //���������[rcvbase-N, rcvbase-1]ʱ����ACK
            a = (this->rcv_base - 4 + 8) % 8 < (this->rcv_base) % 8;
            b = packet.seqnum >= (this->rcv_base - 4+8) % 8 && packet.seqnum < (this->rcv_base) % 8;
            c = packet.seqnum >= (this->rcv_base - 4+8) % 8 || packet.seqnum < (this->rcv_base) % 8;
            if ((a && b) || ((!a) && c))
            {
                lastAckPkt.acknum = packet.seqnum;								//ȷ����ŵ����յ��ı������
                lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
                pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
                //����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�
                pns->sendToNetworkLayer(SENDER, lastAckPkt);
            }
    }

    }
}
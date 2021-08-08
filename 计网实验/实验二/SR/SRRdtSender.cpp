//
// Created by huangjunqidemac on 2020/10/29.
//
#include "stdafx.h"
#include "SRRdtSender.h"
#include "Global.h"
SRRdtSender::SRRdtSender() :nextSeq(0),waitingState(false){

    sendnum=0;
    PacketWaitingSeqnum=0;
    base=0;
    for(int i=0;i<4;i++){
        packetWindows[i].ack=0;
    }
}
SRRdtSender::~SRRdtSender() noexcept {

}

bool SRRdtSender::getWaitingState() {
    return waitingState;
}

bool SRRdtSender::send(const Message &message) {
    if (waitingState) return false;
    if ((nextSeq - base + 8) % 8 < 4) {
        packetWindows[sendnum].sendPacket.acknum = -1;
        packetWindows[sendnum].sendPacket.seqnum = nextSeq;
        packetWindows[sendnum].sendPacket.checksum = 0;
        packetWindows[sendnum].ack = 0;
        memcpy(packetWindows[sendnum].sendPacket.payload, message.data, sizeof(message.data));
        packetWindows[sendnum].sendPacket.checksum = pUtils->calculateCheckSum(packetWindows[sendnum].sendPacket);
        pUtils->printPacket("���ͷ����ͱ���", this->packetWindows[sendnum].sendPacket);        //��ӡ���ݱ�
        if (base == nextSeq)
            pns->startTimer(SENDER, Configuration::TIME_OUT,
                            this->packetWindows[sendnum].sendPacket.seqnum);            //�������ͷ���ʱ��
        pns->sendToNetworkLayer(RECEIVER, packetWindows[sendnum].sendPacket);
        nextSeq = (nextSeq + 1) % 8;
        sendnum++;
        waitingState = false;
        if (sendnum == 4) {
            waitingState = true;
            return false;
        }
        return true;
    }
    else{
        waitingState = true;
        return false;
    }
}
void SRRdtSender::receive(const Packet &ackPkt) {
    int checkSum=pUtils->calculateCheckSum(ackPkt);
    int i;
    if(checkSum!=ackPkt.checksum) return;
    if (this->base <= this->nextSeq)
    {
        if ((ackPkt.acknum < this->base) || (ackPkt.acknum >= this->nextSeq))
            return;
    }
    if (this->base > this->nextSeq)
    {
        if ((ackPkt.acknum < this->base) && (ackPkt.acknum >= this->nextSeq))
            return;
    }
    printf("\n*********************���ͷ������ڻ���ǰ***********************\n");
    for (i = 0; i < (this->nextSeq - this->base + 8)%8; i++)
    {
        printf("������ţ�%d cache: %d\t", this->packetWindows[i].sendPacket.seqnum, this->packetWindows[i].ack);
        pUtils->printPacket("�������ݣ�", this->packetWindows[i].sendPacket);
    }
    printf("*********************���ͷ������ڻ���ǰ***********************\n\n");

    i=0;
    int prebase=base;
    packetWindows[(ackPkt.acknum-base+8)%8].ack=1;
    pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
    pns->stopTimer(SENDER, this->packetWindows[(ackPkt.acknum - this->base + 8) % 8].sendPacket.seqnum);
    if(ackPkt.acknum==base){
        waitingState= false;
        while(packetWindows[i].ack&&i<4){
            base=(base+1)%8;
            i++;
            sendnum--;
        }
        int j=(base-prebase+8)%8;
        i=0;
        while(j<(nextSeq-prebase+8)%8){
            packetWindows[i]=packetWindows[j];
            i++;
            j++;
        }
        while(i<4){
            packetWindows[i].ack=0;
            i++;
        }
        printf("\n*********************���ͷ������ڻ�����***********************\n");
        for (i = 0; i < (this->nextSeq - this->base + 8)%8; i++)
        {
            printf("������ţ�%d cache: %d\t", this->packetWindows[i].sendPacket.seqnum, this->packetWindows[i].ack);
            pUtils->printPacket("�������ݣ�", this->packetWindows[i].sendPacket);
        }
        printf("*********************���ͷ������ڻ�����***********************\n\n");
    }
    if (this->base == this->nextSeq) {
        this->waitingState = false;
    }
    else
    {

        //Ϊ��ǰ�����л�û���յ�ȷ�ϵı��Ŀ�����ʱ��
        for (i = 0; i < (this->nextSeq - this->base + 8) % 8; i++)
        {
            if (this->packetWindows[i].ack == 0)
            {
                pns->stopTimer(SENDER, this->packetWindows[i].sendPacket.seqnum);
                pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWindows[i].sendPacket.seqnum);
            }
        }
    }
}
void SRRdtSender::timeoutHandler(int seqNum) {
    for(int i = 0;i < this->sendnum;i++)
    {
        if (this->packetWindows[i].ack == 0)
        {
            pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط��ϴη��͵ı���", this->packetWindows[i].sendPacket);
            pns->stopTimer(SENDER, this->packetWindows[i].sendPacket.seqnum);									//���ȹرն�ʱ��
            pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWindows[i].sendPacket.seqnum);			//�����������ͷ���ʱ��
            pns->sendToNetworkLayer(RECEIVER, this->packetWindows[i].sendPacket);								//���·������ݰ�
        }
    }
}

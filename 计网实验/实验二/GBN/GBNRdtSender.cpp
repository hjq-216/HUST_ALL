//
// Created by huangjunqidemac on 2020/10/22.
//
#include "Global.h"
#include "GBNRdtSender.h"
#include "stdafx.h"
GBNRdtSender::GBNRdtSender() :nextseqnum(0),waitingState(false){
    expectSequenceNumberSend=0;
    sendnum=0;
    base=0;
    nextseqnum=0;
}
GBNRdtSender::~GBNRdtSender() noexcept {

}
bool GBNRdtSender::getWaitingState() {
    return waitingState;
}
bool GBNRdtSender::send(const Message &message) {
    if(waitingState) return false;
    if((nextseqnum-base+8)%8<4){
        packetWindow[sendnum].acknum=-1;
        packetWindow[sendnum].seqnum=nextseqnum;
        packetWindow[sendnum].checksum=0;
        memcpy(packetWindow[sendnum].payload,message.data,sizeof(message.data));
        packetWindow[sendnum].checksum=pUtils->calculateCheckSum(packetWindow[sendnum]);
        pUtils->printPacket("���ͷ����ͱ���",packetWindow[sendnum]);
        if(base==nextseqnum)
            pns->startTimer(SENDER,Configuration::TIME_OUT,packetWindow[sendnum].seqnum);
        pns->sendToNetworkLayer(RECEIVER,packetWindow[sendnum]);
        nextseqnum=(nextseqnum+1)%8;
        sendnum++;
        waitingState= false;
        if(sendnum==4){
            waitingState=true;
            return false;
        }
        return true;
    }
    else{
        waitingState=true;
        return false;
    }
}
void GBNRdtSender::receive(const Packet &ackPkt) {
    //�����ǰ�������ڵı���
    int i;
    int checkSum=pUtils->calculateCheckSum(ackPkt);
    i=0;
    if(checkSum!=ackPkt.checksum){
        printf("����ͳ���\n");
        return;
    }
    if (this->base <= this->nextseqnum)
    {
        if ((ackPkt.acknum < this->base) || (ackPkt.acknum >= this->nextseqnum))
            return;
    }

    if (this->base > this->nextseqnum)//ѭ������
    {
        if ((ackPkt.acknum < this->base) && (ackPkt.acknum >= this->nextseqnum))
            return;
    }
    printf("\n*********************���ڻ���ǰ***********************\n");
    for (i = 0; i < (this->nextseqnum - this->base + 8) % 8; i++)
    {
        printf("������ţ�%d\t", this->packetWindow[i].seqnum);
        pUtils->printPacket("�������ݣ�", this->packetWindow[i]);
    }
    printf("*********************���ڻ���ǰ***********************\n\n");
    int preBase=base;

    for(i=0;i<=(ackPkt.acknum-preBase+8)%8;i++){
        waitingState= false;
        pUtils->printPacket("���ͷ���ȷ�յ�ȷ��",ackPkt);
        base=(base+1)%8;//��α���ͬ���п����ղ���˳���ȷ�ϣ�����Ϊ�ۻ�ȷ��˵��n֮ǰ���յ���
        sendnum--;
    }
    pns->stopTimer(SENDER,packetWindow[0].seqnum);
    //�ƶ�����
    int j=(base-preBase+8)%8;
    i=0;
    while(j<(nextseqnum-preBase+8)%8){
        packetWindow[i]=packetWindow[j];
        i++;
        j++;
    }
    printf("\n*********************���ڻ�����***********************\n");
    for (i = 0; i < (this->nextseqnum - this->base + 8)%8; i++)
    {
        printf("������ţ�%d\t", this->packetWindow[i].seqnum);
        pUtils->printPacket("�������ݣ�", this->packetWindow[i]);
    }
    printf("*********************���ڻ�����***********************\n\n");
    if(base==nextseqnum) waitingState= false;
    else{
        i=0;
        pns->stopTimer(SENDER,packetWindow[i].seqnum);
        pns->startTimer(SENDER,Configuration::TIME_OUT,packetWindow[i].seqnum);
    }
}
void GBNRdtSender::timeoutHandler(int seqNum) {
    printf("\n************�ش�%d�Լ�֮������б���***********\n", this->base);
    pns->stopTimer(SENDER, this->packetWindow[0].seqnum);									//���ȹرն�ʱ��
    pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWindow[0].seqnum);
    for(int i = 0;i < this->sendnum;i++)
    {
        pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط��ϴη��͵ı���", this->packetWindow[i]);
        		//�����������ͷ���ʱ��
        pns->sendToNetworkLayer(RECEIVER, this->packetWindow[i]);								//���·������ݰ�
    }
    printf("************�ش�%d�Լ�֮������б���***********\n\n", this->base);

}


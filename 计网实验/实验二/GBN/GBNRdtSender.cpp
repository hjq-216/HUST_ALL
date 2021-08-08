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
        pUtils->printPacket("发送方发送报文",packetWindow[sendnum]);
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
    //输出当前滑动窗口的报文
    int i;
    int checkSum=pUtils->calculateCheckSum(ackPkt);
    i=0;
    if(checkSum!=ackPkt.checksum){
        printf("检验和出错\n");
        return;
    }
    if (this->base <= this->nextseqnum)
    {
        if ((ackPkt.acknum < this->base) || (ackPkt.acknum >= this->nextseqnum))
            return;
    }

    if (this->base > this->nextseqnum)//循环窗口
    {
        if ((ackPkt.acknum < this->base) && (ackPkt.acknum >= this->nextseqnum))
            return;
    }
    printf("\n*********************窗口滑动前***********************\n");
    for (i = 0; i < (this->nextseqnum - this->base + 8) % 8; i++)
    {
        printf("报文序号：%d\t", this->packetWindow[i].seqnum);
        pUtils->printPacket("报文内容：", this->packetWindow[i]);
    }
    printf("*********************窗口滑动前***********************\n\n");
    int preBase=base;

    for(i=0;i<=(ackPkt.acknum-preBase+8)%8;i++){
        waitingState= false;
        pUtils->printPacket("发送方正确收到确认",ackPkt);
        base=(base+1)%8;//与课本不同：有可能收不到顺序的确认，但因为累积确认说明n之前都收到了
        sendnum--;
    }
    pns->stopTimer(SENDER,packetWindow[0].seqnum);
    //移动窗口
    int j=(base-preBase+8)%8;
    i=0;
    while(j<(nextseqnum-preBase+8)%8){
        packetWindow[i]=packetWindow[j];
        i++;
        j++;
    }
    printf("\n*********************窗口滑动后***********************\n");
    for (i = 0; i < (this->nextseqnum - this->base + 8)%8; i++)
    {
        printf("报文序号：%d\t", this->packetWindow[i].seqnum);
        pUtils->printPacket("报文内容：", this->packetWindow[i]);
    }
    printf("*********************窗口滑动后***********************\n\n");
    if(base==nextseqnum) waitingState= false;
    else{
        i=0;
        pns->stopTimer(SENDER,packetWindow[i].seqnum);
        pns->startTimer(SENDER,Configuration::TIME_OUT,packetWindow[i].seqnum);
    }
}
void GBNRdtSender::timeoutHandler(int seqNum) {
    printf("\n************重传%d以及之后的所有报文***********\n", this->base);
    pns->stopTimer(SENDER, this->packetWindow[0].seqnum);									//首先关闭定时器
    pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWindow[0].seqnum);
    for(int i = 0;i < this->sendnum;i++)
    {
        pUtils->printPacket("发送方定时器时间到，重发上次发送的报文", this->packetWindow[i]);
        		//重新启动发送方定时器
        pns->sendToNetworkLayer(RECEIVER, this->packetWindow[i]);								//重新发送数据包
    }
    printf("************重传%d以及之后的所有报文***********\n\n", this->base);

}


//
// Created by huangjunqidemac on 2020/10/22.
//
#include "Global.h"
#include "GBNRdtReceiver.h"
#include "stdafx.h"
GBNRdtReceiver::GBNRdtReceiver() :expectSequenceNumberRcvd(0)
{
    lastAckPkt.acknum = -1; //��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ-1��ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ-1
    lastAckPkt.checksum = 0;
    lastAckPkt.seqnum = -1;	//���Ը��ֶ�
    for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
        lastAckPkt.payload[i] = '.';
    }
    lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}


GBNRdtReceiver::~GBNRdtReceiver()
{
}

void GBNRdtReceiver::receive(const Packet& packet) {
    //���У����Ƿ���ȷ
    int checkSum = pUtils->calculateCheckSum(packet);

    //���У�����ȷ��ͬʱ�յ����ĵ��������
    if (checkSum == packet.checksum && this->expectSequenceNumberRcvd == packet.seqnum) {
        pUtils->printPacket("���շ���ȷ�յ����ͷ��ı���", packet);

        //ȡ��Message�����ϵݽ���Ӧ�ò�
        Message msg;
        memcpy(msg.data, packet.payload, sizeof(packet.payload));
        pns->delivertoAppLayer(RECEIVER, msg);

        lastAckPkt.acknum = packet.seqnum; //ȷ����ŵ����յ��ı������
        lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
        pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);

        //����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�
        pns->sendToNetworkLayer(SENDER, lastAckPkt);

        this->expectSequenceNumberRcvd = (this->expectSequenceNumberRcvd+1)%8;			    //������ż�һ�����ڱ���Ϊ3����Ϊ8
    }
    else {
        if (checkSum != packet.checksum) {
            pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,����У�����", packet);
        }
        else {
            pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,������Ų���", packet);
        }
        pUtils->printPacket("���շ����·����ϴε�ȷ�ϱ���", lastAckPkt);

        //����ģ�����绷����sendToNetworkLayer��ͨ������㷢���ϴε�ȷ�ϱ���
        pns->sendToNetworkLayer(SENDER, lastAckPkt);
    }
}

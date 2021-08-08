//
// Created by huangjunqidemac on 2020/10/29.
//
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "SRRdtSender.h"
#include "SRRdtReceiver.h"
#include "stdafx.h"

int main(int argc, char* argv[])
{
    //freopen("C:\\Users\\huangjunqidemac\\Desktop\\SR\\SR.txt", "w", stdout);
    RdtSender* ps = new SRRdtSender();
    RdtReceiver* pr = new SRRdtReceiver();
    //pns->setRunMode(0);  //VERBOSģʽ
    pns->setRunMode(1);  //����ģʽ
    pns->init();
    pns->setRtdSender(ps);
    pns->setRtdReceiver(pr);
    pns->setInputFile("C:\\Users\\huangjunqidemac\\source\\repos\\SR\\Debug\\input.txt");
    pns->setOutputFile("C:\\Users\\huangjunqidemac\\source\\repos\\SR\\Debug\\output.txt");

    pns->start();

    delete ps;
    delete pr;
    delete pUtils;									//ָ��Ψһ�Ĺ�����ʵ����ֻ��main��������ǰdelete
    delete pns;										//ָ��Ψһ��ģ�����绷����ʵ����ֻ��main��������ǰdelete
    //fclose(stdout);
    return 0;
}

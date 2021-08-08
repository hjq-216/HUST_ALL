//
// Created by huangjunqidemac on 2020/10/22.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "GBNRdtSender.h"
#include "GBNRdtReceiver.h"
#include "stdafx.h"
int main(){

    //freopen("C:\\Users\\huangjunqidemac\\source\\repos\\GBN\\Debug\\GBN.txt","w",stdout);
    RdtSender *ps=new GBNRdtSender();
    RdtReceiver *pr=new GBNRdtReceiver();
    pns->setRunMode(0);
    pns->init();
    pns->setRtdSender(ps);
    pns->setRtdReceiver(pr);
    pns->setInputFile("C:\\Users\\huangjunqidemac\\source\\repos\\GBN\\Debug\\input.txt");
    pns->setOutputFile("C:\\Users\\huangjunqidemac\\source\\repos\\GBN\\Debug\\output.txt");

    pns->start();

    delete ps;
    delete pr;
    delete pUtils;									//ָ��Ψһ�Ĺ�����ʵ����ֻ��main��������ǰdelete
    delete pns;										//ָ��Ψһ��ģ�����绷����ʵ����ֻ��main��������ǰdelete
    //fclose(stdout);

    return 0;
}
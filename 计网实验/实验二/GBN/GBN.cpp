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
    delete pUtils;									//指向唯一的工具类实例，只在main函数结束前delete
    delete pns;										//指向唯一的模拟网络环境类实例，只在main函数结束前delete
    //fclose(stdout);

    return 0;
}
#include <QCoreApplication>
#include <stdio.h>

#include "stockstruct.h"
#include <fstream>
#include <QDebug>
#include <stockutils.h>
#include <QFile>
#include <QDataStream>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    StockUtils::ConnectDB(StockUtils::dataBase);
    QFile file("../stockid.txt");
    file.open(QIODevice::ReadOnly);
    QString szorsh;
    QString stockcode;
    QTextStream  stream(&file);
    QStringList sl;
    while(1){
        stream>>szorsh >>stockcode;
        if(szorsh.isEmpty()) break;
        sl.push_back(szorsh);
        sl.push_back(stockcode);
    }
    file.close();
    StockUtils::QueryAndSaveAllStockList(sl,"20200101","20201231");
      qDebug()<<"程序结束！！！";
    return a.exec();
    ////////////////五日线大于60日线，价高于20小于50
    file.open(QIODevice::ReadOnly);
    QTextStream  stream1(&file);
    while(1){
        stream1>>szorsh >>stockcode;
        if(szorsh.isEmpty()) break;
        CStock Stock(szorsh,stockcode);
        double _5dayline = Stock.getNdayline(5);
        double _60dayline = Stock.getNdayline(60);
        double _p5dayline = Stock.getpreNdayline(5);
        double _p60dayline = Stock.getpreNdayline(60);
        if(_p5dayline<_p60dayline&&_5dayline>_60dayline
                &&Stock.getCurrentPrice()>20&&Stock.getCurrentPrice()<50
                &&Stock.m_udpercent<2&&Stock.m_preudpercent<2)
            qDebug()<<Stock.getStockName()<<Stock.getStockID()<<_p5dayline<<_p60dayline<<(_p5dayline-_p60dayline)/Stock.getCurrentPrice()<<(_5dayline-_60dayline)/Stock.getCurrentPrice()<<"";
//        if((_60dayline-_5dayline)/Stock.getCurrentPrice()<0.002&&_60dayline>_5dayline)
//            qDebug()<<Stock.getStockName()<<Stock.getStockID()<<_p5dayline<<_p60dayline<<(_p5dayline-_p60dayline)/Stock.getCurrentPrice()<<(_5dayline-_60dayline)/Stock.getCurrentPrice()<<"";
    }
    file.close();
//    ////////////////均线分散
//    file.open(QIODevice::ReadOnly);
//    QTextStream  stream1(&file);
//    while(1){
//        stream1>>szorsh >>stockcode;
//        CStock Stock(szorsh,stockcode);
//        double _5dayline = Stock.getNdayline(5);
//        double _20dayline = Stock.getNdayline(20);
//        double _30dayline = Stock.getNdayline(30);
//        double _60dayline = Stock.getNdayline(60);
//        if(_5dayline>_20dayline&&_20dayline>_30dayline&&_30dayline>_60dayline
//                &&Stock.getCurrentPrice()>20&&Stock.getCurrentPrice()<50
//                &&Stock.m_udpercent<2&&Stock.m_preudpercent<2)
//            qDebug()<<Stock.getStockName()<<Stock.getStockID()<<Stock.getCurrentPrice()<<"";
//    }
//    file.close();

//    CStock Stock(szorsh,stockcode);
//    Stock.getDataFromTo("20190820","20201231"); continue;
//    double _5dayline = Stock.getNdayline(5);
//    double _60dayline = Stock.getNdayline(60);
//    double _p5dayline = Stock.getpreNdayline(5);
//    double _p60dayline = Stock.getpreNdayline(60);
//    qDebug()<<Stock.getStockName()<<Stock.getStockID()<<(_p5dayline-_p60dayline)/Stock.getCurrentPrice()<<(_5dayline-_60dayline)/Stock.getCurrentPrice()<<"";
//    int a=0;

    StockUtils::dataBase.close();
    qDebug()<<"程序结束！！！";
    return a.exec();
}

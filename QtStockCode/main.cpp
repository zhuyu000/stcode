#include <QCoreApplication>
#include <stdio.h>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTextCodec>
#include "stockstruct.h"
#include <iostream>
#include <QDebug>
#include <stockutils.h>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // URL
    //    QString baseUrl = "http://hq.sinajs.cn/list=sh600547";
//    QString baseUrl = "http://quotes.money.163.com/service/chddata.html?code=0600756&start=20160902&end=20171108&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;TURNOVER;VOTURNOVER;VATURNOVER;TCAP;MCAP";
    QString baseUrl = "http://qt.gtimg.cn/q=sz000002";
    // 构造请求
    QNetworkRequest request;
    request.setUrl(QUrl(baseUrl));

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    // 发送请求
    QNetworkReply *pReplay = manager->get(request);

    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 获取响应信息
    QByteArray bytes = pReplay->readAll();
//    //qDebug() << bytes;
//    //printf(bytes);
    QTextCodec *gbk = QTextCodec::codecForName("gbk");
    QTextCodec::setCodecForLocale(gbk);
    QString strUnicode= gbk->toUnicode(bytes);

//    StockStruct test = StockUtils::convertSinaHTTPtxtToStruct(strUnicode);
    CStock testclass;
    testclass.convertgtImgHTTPtxtToStruct(strUnicode);
    testclass.ShowStockStruct();
//    StockStruct test = StockUtils::convertgtImgHTTPtxtToStruct(strUnicode);
//    StockUtils::ShowStockStruct(test);
//    qDebug()<<strUnicode;
//    cout<<QString(bytes).tolo.toStdString()<<endl;
    //cout<<QString("收到罚单\t").toLocal8Bit().toStdString()<<endl;
    //printf(strUnicode.toStdString());
    return a.exec();
}

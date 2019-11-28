#include <QCoreApplication>
#include <stdio.h>

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
    QString baseUrl = "http://quotes.money.163.com/service/chddata.html?code=0600756&start=20160101&end=20171231&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;TURNOVER;VOTURNOVER;VATURNOVER;TCAP;MCAP";
//    QString baseUrl = "http://qt.gtimg.cn/q=sz000750";
    QString strUnicode = StockUtils::QueryFromURL(baseUrl);
    qDebug() << strUnicode;
    CStock testclass;
    testclass.convertgtImgHTTPtxtToStruct(strUnicode);
    testclass.ShowStockStruct();
    QStringList list = strUnicode.split("\r\n");
    return a.exec();
}

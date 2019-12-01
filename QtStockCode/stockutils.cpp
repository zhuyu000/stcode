#include <stockutils.h>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <fstream>
using namespace std;
QString StockUtils::QueryFromURL(QString &baseUrl)
{
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

//    //printf(bytes);
    QTextCodec *gbk = QTextCodec::codecForName("gbk");
    QTextCodec::setCodecForLocale(gbk);
    QString strUnicode= gbk->toUnicode(bytes);
    return strUnicode;
}

void StockUtils::ParseURLCode(QString &strURLCode)
{
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("192.168.0.110");
    dataBase.setPort(3306);
    dataBase.setUserName("Yu");
    dataBase.setPassword("1234");
    dataBase.setDatabaseName("stock");
    QStringList drivers = QSqlDatabase::drivers();  //获取现在可用的数据库驱动
    foreach(QString driver, drivers)
        qDebug() << driver;
    if(!dataBase.open()){
            QSqlError err =  dataBase.lastError();
            return;
    }
    QStringList list = strURLCode.split("\r\n");
    if(list.size()<2) return;
    QString item;
    CStock stockitem;
    QSqlQuery query(dataBase);
    QString sql=QString("select *from stock.stockhistory");
    query.exec(sql);
    for(int i = 1;i<10;i++)
    {
        item= list[i];
        stockitem.convert163dayKItermToStruct(item);
        structStock ss = stockitem.getstockstruct();
        QString insertsql = QString("INSERT INTO stock.stockhistory ("
                                    "STOCKID, "
                                    "STOCKCODE, "
                                    "STOCKNAME, "
                                    "TRADEDATE, "
                                    "TRADETIME, "
                                    "YESCLOSE, "
                                    "TODOPEN, "
                                    "CURPRICE, "
                                    "MAXPRICE, "
                                    "MINPRICE, "
                                    "TRADENUM, "
                                    "TRADETOTAL, "
                                    "BUY1, "
                                    "BUY1TOTAL, "
                                    "BUY2, "
                                    "BUY2TOTAL, "
                                    "BUY3, "
                                    "BUY3TOTAL, "
                                    "BUY4, "
                                    "BUY4TOTAL, "
                                    "BUY5, "
                                    "BUY5TOTAL, "
                                    "SELL1, "
                                    "SELL1TOTAL, "
                                    "SELL2, "
                                    "SELL2TOTAL, "
                                    "SELL3, "
                                    "SELL3TOTAL, "
                                    "SELL4, "
                                    "SELL4TOTAL, "
                                    "SELL5, "
                                    "SELL5TOTAL, "
                                    "INMARKET, "
                                    "OUTMARKET, "
                                    "UPDOWN, "
                                    "UDPERCENT, "
                                    "EXCHANGERATIO, "
                                    "PERATIO, "
                                    "AMP, "
                                    "MARKETVALUE, "
                                    "TOTALMARKETVALUE, "
                                    "PBRATIO, "
                                    "LIMITUPPRICE, "
                                    "LIMITDOWNPRICE) "
                                    "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', "
                                    "'%11', '%12', '%13', '%14', '%15', '%16', '%17', '%18', '%19', '%20', "
                                    "'%21', '%22', '%23', '%24', '%25', '%26', '%27', '%28', '%29', '%30', "
                                    "'%31', '%32', '%33', '%34', '%35', '%36', '%37', '%38', '%39', '%40',"
                                    " '%41', '%42', '%43', '%44'); ")
                .arg(QString(ss.s_StockName.c_str())+" "+QString(ss.t_date.c_str())+" "+QString(ss.t_time.c_str()))
                .arg(QString(ss.s_StockCode.c_str()))
                .arg(QString(ss.s_StockName.c_str()))
                .arg(QString(ss.t_date.c_str()))
                .arg(QString(ss.t_time.c_str()))
                .arg(ss.d_yesterday_closed_price)
                .arg(ss.d_today_open_price)
                .arg(ss.d_current_price)
                .arg(ss.d_today_max_price)
                .arg(ss.d_today_min_price)
                .arg(ss.d_totalnum)
                .arg(ss.d_totalcurrency)
                .arg(ss.d_buy_1_price)
                .arg(ss.d_buy_1_total)
                .arg(ss.d_buy_2_price)
                .arg(ss.d_buy_2_total)
                .arg(ss.d_buy_3_price)
                .arg(ss.d_buy_3_total)
                .arg(ss.d_buy_4_price)
                .arg(ss.d_buy_4_total)
                .arg(ss.d_buy_5_price)
                .arg(ss.d_buy_5_total)
                .arg(ss.d_sell_1_price)
                .arg(ss.d_sell_1_total)
                .arg(ss.d_sell_2_price)
                .arg(ss.d_sell_2_total)
                .arg(ss.d_sell_3_price)
                .arg(ss.d_sell_3_total)
                .arg(ss.d_sell_4_price)
                .arg(ss.d_sell_4_total)
                .arg(ss.d_sell_5_price)
                .arg(ss.d_sell_5_total)
                .arg(ss.d_inmarket)
                .arg(ss.d_outmarket)
                .arg(ss.d_increase)
                .arg(ss.d_increasepercent)
                .arg(ss.d_exchangeratio)
                .arg(ss.d_peratio)
                .arg(ss.d_amp)
                .arg(ss.d_maketvalue)
                .arg(ss.d_totalmaketvalue)
                .arg(ss.d_pbratio)
                .arg(ss.d_limitupprice)
                .arg(ss.d_limitdownprice);
        bool ok = query.exec(insertsql);
        QSqlError err =  query.lastError();
        int a= 0;
    }
    dataBase.close();
}

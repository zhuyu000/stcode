#include <stockutils.h>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTextCodec>
#include <QSqlError>
#include <QSqlQuery>
#include <QRegExp>
#include <QFile>

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

	//printf(bytes);
    QTextCodec *gbk = QTextCodec::codecForName("gbk");
    QTextCodec::setCodecForLocale(gbk);
    QString strUnicode= gbk->toUnicode(bytes);
    delete manager;
    return strUnicode;
}

void StockUtils::ParseURLCode(QString &strURLCode,QString &szorsh)
{
    QStringList list = strURLCode.split("\r\n");
    if(list.size()<2) return;
    QString item;
    QSqlQuery query(dataBase);
    QString insertsql = QString("INSERT INTO stock.stockhistory ("
                                "STOCKID, SHORSZ, STOCKCODE, STOCKNAME, "
                                "TRADEDATE, TRADETIME, YESCLOSE, TODOPEN, CURPRICE, MAXPRICE, MINPRICE, TRADENUM, TRADETOTAL, "
                                "BUY1, BUY1TOTAL, BUY2, BUY2TOTAL, BUY3, BUY3TOTAL, BUY4, BUY4TOTAL, BUY5, BUY5TOTAL,"
                                "SELL1, SELL1TOTAL, SELL2, SELL2TOTAL, SELL3, SELL3TOTAL, SELL4, SELL4TOTAL, SELL5, SELL5TOTAL, "
                                "INMARKET, OUTMARKET, UPDOWN, UDPERCENT, EXCHANGERATIO, PERATIO, AMP, MARKETVALUE, "
                                "TOTALMARKETVALUE, PBRATIO, LIMITUPPRICE, LIMITDOWNPRICE) VALUES");
    QString PrimaryID;
    QString stockname;
    StockStruct ss;
    for(int i = 1;i<list.size()-1;i++)
    {
        item= list[i];
        if(item.isEmpty()){
            qDebug()<<"没有检索到数据，无法入库！！!";
            return;
        }
        ss = convert163dayKItermToStruct(item);
        PrimaryID = ss.s_StockName+" "+ss.t_date+" "+ss.t_time;
        query.exec(QString("select * from stock.stockhistory where STOCKID=\'")+PrimaryID+"\'");
        if(query.first())
            continue;
        QString partsql= QString(" ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', "
                                 "'%11', '%12', '%13', '%14', '%15', '%16', '%17', '%18', '%19', '%20', "
                                 "'%21', '%22', '%23', '%24', '%25', '%26', '%27', '%28', '%29', '%30', "
                                 "'%31', '%32', '%33', '%34', '%35', '%36', '%37', '%38', '%39', '%40',"
                                 " '%41', '%42', '%43', '%44','%45')")
                .arg(PrimaryID).arg(szorsh).arg(ss.s_StockCode).arg(ss.s_StockName)
                .arg(ss.t_date).arg(ss.t_time).arg(ss.d_yesterday_closed_price).arg(ss.d_today_open_price)
                .arg(ss.d_current_price).arg(ss.d_today_max_price).arg(ss.d_today_min_price).arg(ss.d_totalnum).arg(ss.d_totalcurrency)
                .arg(ss.d_buy_1_price).arg(ss.d_buy_1_total).arg(ss.d_buy_2_price).arg(ss.d_buy_2_total).arg(ss.d_buy_3_price)
                .arg(ss.d_buy_3_total).arg(ss.d_buy_4_price).arg(ss.d_buy_4_total).arg(ss.d_buy_5_price).arg(ss.d_buy_5_total)
                .arg(ss.d_sell_1_price).arg(ss.d_sell_1_total).arg(ss.d_sell_2_price).arg(ss.d_sell_2_total).arg(ss.d_sell_3_price)
                .arg(ss.d_sell_3_total).arg(ss.d_sell_4_price).arg(ss.d_sell_4_total).arg(ss.d_sell_5_price).arg(ss.d_sell_5_total)
                .arg(ss.d_inmarket).arg(ss.d_outmarket).arg(ss.d_increase).arg(ss.d_increasepercent).arg(ss.d_exchangeratio)
                .arg(ss.d_peratio).arg(ss.d_amp).arg(ss.d_maketvalue).arg(ss.d_totalmaketvalue).arg(ss.d_pbratio).arg(ss.d_limitupprice).arg(ss.d_limitdownprice);
        insertsql = insertsql+partsql;
        if(i!=list.size()-2) insertsql = insertsql+", ";
    }
    bool ok = query.exec(insertsql);
//    qDebug()<<insertsql;
    if(ok) qDebug()<<"检索到数据"<<ss.s_StockName<<" "<<list.size()-2<<"条";
    QSqlError err =  query.lastError();
}

StockStruct StockUtils::convert163dayKItermToStruct(QString &item)
{
    StockStruct outstruct;
    QStringList list = item.split(",");
    if(list.size()<15) return outstruct;
    outstruct.t_date = list[0];
    outstruct.s_StockCode = list[1].mid(1,list[1].size()-1);
    outstruct.s_StockName = list[2].remove(QRegExp("\\s"));
    outstruct.d_current_price = list[3].toFloat();
    outstruct.d_today_max_price = list[4].toFloat();
    outstruct.d_today_min_price = list[5].toFloat();
    outstruct.d_today_open_price = list[6].toFloat();
    outstruct.d_yesterday_closed_price = list[7].toFloat();
    outstruct.d_increase = list[8].toFloat();
    outstruct.d_increasepercent = list[9].toFloat();
    outstruct.d_exchangeratio = list[10].toFloat();
    outstruct.d_totalnum = list[11].toFloat();
    outstruct.d_totalcurrency = list[12].toFloat();
    outstruct.d_totalmaketvalue = list[13].toFloat();
    outstruct.d_maketvalue = list[14].toFloat();
    outstruct.t_time = "15:00:00";
    return outstruct;
}
void StockUtils::ShowStockStruct(StockStruct &ss)
{
    qDebug()<<"名称:\t\t"<<ss.s_StockName;
    qDebug()<<"代码:\t\t"<<ss.s_StockCode;
    qDebug()<<"日期:\t\t"<<ss.t_date;
    qDebug()<<"时间:\t\t"<<ss.t_time;
    qDebug()<<"昨收:\t\t"<<ss.d_yesterday_closed_price;
    qDebug()<<"今开:\t\t"<<ss.d_today_open_price;
    qDebug()<<"现价:\t\t"<<ss.d_current_price;
    qDebug()<<"最低:\t\t"<<ss.d_today_min_price;
    qDebug()<<"最高:\t\t"<<ss.d_today_max_price;
    qDebug()<<"成交量:\t\t"<<ss.d_totalnum;
    qDebug()<<"成交额:\t\t"<<ss.d_totalcurrency;
    qDebug()<<"买一:\t\t"<<ss.d_buy_1_price;
    qDebug()<<"买一量:\t\t"<<ss.d_buy_1_total;
    qDebug()<<"买二:\t\t"<<ss.d_buy_2_price;
    qDebug()<<"买二量:\t\t"<<ss.d_buy_2_total;
    qDebug()<<"买三:\t\t"<<ss.d_buy_3_price;
    qDebug()<<"买三量:\t\t"<<ss.d_buy_3_total;
    qDebug()<<"买四:\t\t"<<ss.d_buy_4_price;
    qDebug()<<"买四量:\t\t"<<ss.d_buy_4_total;
    qDebug()<<"买五:\t\t"<<ss.d_buy_5_price;
    qDebug()<<"买五量:\t\t"<<ss.d_buy_5_total;
    qDebug()<<"卖一:\t\t"<<ss.d_sell_1_price;
    qDebug()<<"卖一量:\t\t"<<ss.d_sell_1_total;
    qDebug()<<"卖二:\t\t"<<ss.d_sell_2_price;
    qDebug()<<"卖二量:\t\t"<<ss.d_sell_2_total;
    qDebug()<<"卖三:\t\t"<<ss.d_sell_3_price;
    qDebug()<<"卖三量:\t\t"<<ss.d_sell_3_total;
    qDebug()<<"卖四:\t\t"<<ss.d_sell_4_price;
    qDebug()<<"卖四量:\t\t"<<ss.d_sell_4_total;
    qDebug()<<"卖五:\t\t"<<ss.d_sell_5_price;
    qDebug()<<"卖五量:\t\t"<<ss.d_sell_5_total;
    qDebug()<<"外盘:\t\t"<<ss.d_outmarket;
    qDebug()<<"内盘:\t\t"<<ss.d_inmarket;
    qDebug()<<"涨跌:\t\t"<<ss.d_increase;
    qDebug()<<"涨跌%:\t\t"<<ss.d_increasepercent;
    qDebug()<<"换手率:\t\t"<<ss.d_exchangeratio;
    qDebug()<<"市盈率:\t\t"<<ss.d_peratio;
    qDebug()<<"振幅:\t\t"<<ss.d_amp;
    qDebug()<<"流通市值:\t"<<ss.d_maketvalue;
    qDebug()<<"总市值:\t\t"<<ss.d_totalmaketvalue;
    qDebug()<<"市净率:\t\t"<<ss.d_pbratio;
    qDebug()<<"涨停价:\t\t"<<ss.d_limitupprice;
    qDebug()<<"跌停价:\t\t"<<ss.d_limitdownprice;
}
StockStruct StockUtils::convertSinaHTTPtxtToStruct(QString &item)
{
    //    QString baseUrl = "http://hq.sinajs.cn/list=sh600547";
    StockStruct outstruct;
    QStringList list = item.split("\"");
    QString corestr = list[1];
    if(list.size()<2) return outstruct;
    QStringList corelist = corestr.split(",");
    if(corelist.size()<32) return outstruct;
    outstruct.s_StockName = corelist[0] ;
    outstruct.d_today_open_price = corelist[1].toFloat();
    outstruct.d_yesterday_closed_price = corelist[2].toFloat();
    outstruct.d_current_price = corelist[3].toFloat();
    outstruct.d_today_max_price = corelist[4].toFloat();
    outstruct.d_today_min_price = corelist[5].toFloat();
    outstruct.d_buy_1_price = corelist[6].toFloat();
    outstruct.d_sell_1_price = corelist[7].toFloat();
    outstruct.d_totalnum = corelist[8].toFloat()/100;
    outstruct.d_totalcurrency = corelist[9].toFloat()/10000;
    outstruct.d_buy_1_total = corelist[10].toFloat()/100;
    outstruct.d_buy_1_price = corelist[11].toFloat();
    outstruct.d_buy_2_total = corelist[12].toFloat()/100;
    outstruct.d_buy_2_price = corelist[13].toFloat();
    outstruct.d_buy_3_total = corelist[14].toFloat()/100;
    outstruct.d_buy_3_price = corelist[15].toFloat();
    outstruct.d_buy_4_total = corelist[16].toFloat()/100;
    outstruct.d_buy_4_price = corelist[17].toFloat();
    outstruct.d_buy_5_total = corelist[18].toFloat()/100;
    outstruct.d_buy_5_price = corelist[19].toFloat();
    outstruct.d_sell_1_total = corelist[20].toFloat()/100;
    outstruct.d_sell_1_price = corelist[21].toFloat();
    outstruct.d_sell_2_total = corelist[22].toFloat()/100;
    outstruct.d_sell_2_price = corelist[23].toFloat();
    outstruct.d_sell_3_total = corelist[24].toFloat()/100;
    outstruct.d_sell_3_price = corelist[25].toFloat();
    outstruct.d_sell_4_total = corelist[26].toFloat()/100;
    outstruct.d_sell_4_price = corelist[27].toFloat();
    outstruct.d_sell_5_total = corelist[28].toFloat()/100;
    outstruct.d_sell_5_price = corelist[29].toFloat();
    outstruct.t_date = corelist[30];
    outstruct.t_time = corelist[31];
    return outstruct;
}

StockStruct StockUtils::convertgtImgHTTPtxtToStruct(QString &item)
{
    StockStruct outstruct;
    QStringList list = item.split("\"");
    if(list.size()<2) return outstruct;
    QString corestr = list[1];
    QStringList corelist = corestr.split("~");
    if(corelist.size()<49) return outstruct;
    outstruct.s_StockName = corelist[1];
    outstruct.s_StockCode = corelist[2];
    outstruct.t_date = corelist[30].mid(0,8);
    outstruct.t_time = corelist[30].mid(8,6);
    outstruct.d_totalnum = corelist[36].toFloat();
    outstruct.d_totalcurrency = corelist[37].toFloat();
    outstruct.d_yesterday_closed_price = corelist[4].toFloat();
    outstruct.d_today_open_price = corelist[5].toFloat();
    outstruct.d_current_price = corelist[3].toFloat();
    outstruct.d_today_max_price = corelist[33].toFloat();
    outstruct.d_today_min_price = corelist[34].toFloat();
    outstruct.d_sell_1_price = corelist[19].toFloat();
    outstruct.d_sell_1_total = corelist[20].toFloat();
    outstruct.d_sell_2_price = corelist[21].toFloat();
    outstruct.d_sell_2_total = corelist[22].toFloat();
    outstruct.d_sell_3_price = corelist[23].toFloat();
    outstruct.d_sell_3_total = corelist[24].toFloat();
    outstruct.d_sell_4_price = corelist[25].toFloat();
    outstruct.d_sell_4_total = corelist[26].toFloat();
    outstruct.d_sell_5_price = corelist[27].toFloat();
    outstruct.d_sell_5_total = corelist[28].toFloat();
    outstruct.d_buy_1_price = corelist[9].toFloat();
    outstruct.d_buy_1_total = corelist[10].toFloat();
    outstruct.d_buy_2_price = corelist[11].toFloat();
    outstruct.d_buy_2_total = corelist[12].toFloat();
    outstruct.d_buy_3_price = corelist[13].toFloat();
    outstruct.d_buy_3_total = corelist[14].toFloat();
    outstruct.d_buy_4_price = corelist[15].toFloat();
    outstruct.d_buy_4_total = corelist[16].toFloat();
    outstruct.d_buy_5_price = corelist[17].toFloat();
    outstruct.d_buy_5_total = corelist[18].toFloat();
    outstruct.d_outmarket = corelist[7].toFloat();
    outstruct.d_inmarket = corelist[8].toFloat();
    outstruct.d_increase = corelist[31].toFloat();
    outstruct.d_increasepercent = corelist[32].toFloat();
    outstruct.d_exchangeratio = corelist[38].toFloat();
    outstruct.d_peratio = corelist[39].toFloat();
    outstruct.d_amp = corelist[43].toFloat();
    outstruct.d_maketvalue = corelist[44].toFloat();
    outstruct.d_totalmaketvalue = corelist[45].toFloat();
    outstruct.d_pbratio = corelist[46].toFloat();
    outstruct.d_limitupprice = corelist[47].toFloat();
    outstruct.d_limitdownprice = corelist[48].toFloat();
    return outstruct;
}

void StockUtils::ConnectDB(QSqlDatabase &dataBase)
{
    dataBase=QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("192.168.0.105");
    dataBase.setPort(3306);
    dataBase.setUserName("root");
    dataBase.setPassword("1234");
    dataBase.setDatabaseName("stock");
    QStringList drivers = QSqlDatabase::drivers();  //获取现在可用的数据库驱动
    //要安装32位的数据库驱动因为qt只提供32位数据库接口
    if(!dataBase.open()){
            QSqlError err =  dataBase.lastError();
            return;
    }
}

void StockUtils::QueryAndSaveAllStockList(QStringList &stringlist, const QString &strFrom,const QString &strTo)
{
    QString szorsh;
    QString stockcode;
    QSqlQuery query(dataBase);
    QString insertsql;
    int nGroup = 0;
    QString Groupsql;
    for(int i = 0;i<stringlist.size()/2;i+=2)
    {
        szorsh = stringlist[i];
        stockcode = stringlist[i+1];
//        query.exec(QString("select stockname from stock.stocktable%1 where stockcode=\'").arg(stockcode.right(2))+stockcode+"\' limit 1");
//        if(query.first()){
//            qDebug()<<"已存在信息:"<<query.value(0).toString();
//            continue;
//        }
        QString shsz = szorsh=="sh"?"0":"1";
        //    QString baseUrl = "http://quotes.money.163.com/service/chddata.html?code=0600756&start=20160101&end=20191231&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;TURNOVER;VOTURNOVER;VATURNOVER;TCAP;MCAP";
        QString baseUrl = QString("http://quotes.money.163.com/service/chddata.html?code=%1%2&start=%3&end=%4&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;TURNOVER;VOTURNOVER;VATURNOVER;TCAP;MCAP")
                .arg(shsz)
                .arg(stockcode)
                .arg(strFrom)
                .arg(strTo);
        QString strUnicode = StockUtils::QueryFromURL(baseUrl);
        QString strQuerypartSql = StockUtils::ParsesingleURLCode(strUnicode,szorsh);
        insertsql = QString("INSERT INTO stock.stocktable%1 ("
                                        "STOCKID, SHORSZ, STOCKCODE, STOCKNAME, "
                                        "TRADEDATE, TRADETIME, YESCLOSE, TODOPEN, CURPRICE, MAXPRICE, MINPRICE, TRADENUM, TRADETOTAL, "
                                        "UPDOWN, UDPERCENT, EXCHANGERATIO, MARKETVALUE, "
                                        "TOTALMARKETVALUE) VALUES").arg(stockcode.right(2));
//        Groupsql = Groupsql+strQuerypartSql;
//        nGroup++;
//        if(nGroup==10){
            strQuerypartSql = strQuerypartSql.left(strQuerypartSql.size()-2);
            bool ok = query.exec(insertsql+strQuerypartSql);
            nGroup = 0;
//            Groupsql.clear();
//            }
    }
    bool ok = query.exec(insertsql+Groupsql);
    //    qDebug()<<insertsql;

        QSqlError err =  query.lastError();
}

QString StockUtils::ParsesingleURLCode(QString &strURLCode, QString &szorsh)
{
    QStringList list = strURLCode.split("\r\n");
    if(list.size()<2) return QString();
    QString item;
    QSqlQuery query(dataBase);
    QString insertsql;
    QString PrimaryID;
    QString stockname;
    StockStruct ss;
    int ncount = 0;
    ss = convert163dayKItermToStruct(list[1]);
    PrimaryID = ss.s_StockName+" "+ss.t_date+" "+ss.t_time;
    for(int i = 1;i<list.size()-1;i++)
    {
        item= list[i];
        if(item.isEmpty()){
            qDebug()<<"没有检索到数据，无法入库！！!";
            return QString();
        }
        ss = convert163dayKItermToStruct(item);
        PrimaryID = ss.s_StockName+" "+ss.t_date+" "+ss.t_time;
        query.exec(QString("select STOCKID from stock.stocktable"+ss.s_StockCode.right(2)+" where STOCKID=\'")+PrimaryID+"\' limit 1");
        if(query.first())
            break;
        //int test = query.value(0).toInt();
//qDebug()<<QString("select STOCKID from stock.stocktable"+ss.s_StockCode.right(2)+" where STOCKID=\'")+PrimaryID+"\' limit 1";
        QString partsql= QString(" ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', "
                                 "'%11', '%12', '%13', '%14', '%15', '%16', '%17', '%18')")
                .arg(PrimaryID).arg(szorsh).arg(ss.s_StockCode).arg(ss.s_StockName)
                .arg(ss.t_date).arg(ss.t_time).arg(ss.d_yesterday_closed_price).arg(ss.d_today_open_price)
                .arg(ss.d_current_price).arg(ss.d_today_max_price).arg(ss.d_today_min_price).arg(ss.d_totalnum).arg(ss.d_totalcurrency)
                .arg(ss.d_increase).arg(ss.d_increasepercent).arg(ss.d_exchangeratio)
                .arg(ss.d_maketvalue).arg(ss.d_totalmaketvalue);
        insertsql = insertsql+partsql+", ";
        //if(i!=list.size()-2) insertsql = insertsql+", ";
        ncount++;
    }
//    bool ok = query.exec(insertsql);
////    qDebug()<<insertsql;
    qDebug()<<"检索到数据"<<ss.s_StockName.toStdString().c_str()<<" "<<ncount<<"条";
//    QSqlError err =  query.lastError();
    return insertsql;
}

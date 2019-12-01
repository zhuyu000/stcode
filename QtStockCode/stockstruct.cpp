#include "stockstruct.h"
#include <QStringList>
#include <QDebug>
CStock::CStock()
{

}

void CStock::convertSinaHTTPtxtToStruct(QString &txt)
{
    //    QString baseUrl = "http://hq.sinajs.cn/list=sh600547";
    StockStruct &outstruct = m_stockstruct;
    QStringList list = txt.split("\"");
    QString corestr = list[1];
    if(list.size()<2) return;
    QStringList corelist = corestr.split(",");
    if(corelist.size()<32) return;
    outstruct.s_StockName = corelist[0].toStdString() ;
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
    outstruct.t_date = corelist[30].toStdString() ;
    outstruct.t_time = corelist[31].toStdString() ;
}

void CStock::convertgtImgHTTPtxtToStruct(QString &txt)
{
    StockStruct &outstruct = m_stockstruct;
    QStringList list = txt.split("\"");
    if(list.size()<2) return;
    QString corestr = list[1];
    QStringList corelist = corestr.split("~");
    if(corelist.size()<49) return;
    outstruct.s_StockName = corelist[1].toStdString();
    outstruct.s_StockCode = corelist[2].toStdString();
    outstruct.t_date = corelist[30].mid(0,8).toStdString();
    outstruct.t_time = corelist[30].mid(8,6).toStdString();
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
}

void CStock::convert163dayKItermToStruct(QString &txt)
{
    StockStruct &outstruct = m_stockstruct;
    QStringList list = txt.split(",");
    if(list.size()<15) return;
    outstruct.t_date = list[0].toStdString();
    outstruct.s_StockCode = list[1].mid(1,list[1].size()-1).toStdString();
    outstruct.s_StockName = list[2].toStdString();
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
}

void CStock::ShowStockStruct()
{
    structStock &ss = m_stockstruct;
    qDebug()<<"名称:\t\t"<<QString(ss.s_StockName.c_str());
    qDebug()<<"代码:\t\t"<<QString(ss.s_StockCode.c_str());
    qDebug()<<"日期:\t\t"<<QString(ss.t_date.c_str());
    qDebug()<<"时间:\t\t"<<QString(ss.t_time.c_str());
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

StockStruct CStock::getstockstruct() const
{
    return m_stockstruct;
}

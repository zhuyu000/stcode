#include "stockstruct.h"
#include <QStringList>
#include <QDebug>
#include "stockutils.h"
#include <QSqlQuery>

void CStock::getDataFromTo(const QString strFrom, const QString strTo)
{
    //    QString baseUrl = "http://quotes.money.163.com/service/chddata.html?code=0600756&start=20160101&end=20191231&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;TURNOVER;VOTURNOVER;VATURNOVER;TCAP;MCAP";
    QString shsz = m_strSzOrSh=="sh"?"0":"1";
    QString baseUrl = QString("http://quotes.money.163.com/service/chddata.html?code=%1%2&start=%3&end=%4&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;TURNOVER;VOTURNOVER;VATURNOVER;TCAP;MCAP")
            .arg(shsz)
            .arg(m_strStockID)
            .arg(strFrom)
            .arg(strTo);

    QString strUnicode = StockUtils::QueryFromURL(baseUrl);
    StockUtils::ParseURLCode(strUnicode,m_strSzOrSh);
}

void CStock::ShowCurrentData()
{
    //    QString baseUrl = "http://qt.gtimg.cn/q=sz000750";
    QString baseUrl = QString("http://qt.gtimg.cn/q=")+ this->m_strSzOrSh + this->m_strStockID;
    QString strUnicode = StockUtils::QueryFromURL(baseUrl);
    StockStruct ss = StockUtils::convertgtImgHTTPtxtToStruct(strUnicode);
    StockUtils::ShowStockStruct(ss);
}

QString CStock::getStockName()
{
    StockStruct ss = getStockStruct();
    return ss.s_StockName;
}

StockStruct CStock::getStockStruct()
{
    QString baseUrl = QString("http://qt.gtimg.cn/q=")+ this->m_strSzOrSh + this->m_strStockID;
    QString strUnicode = StockUtils::QueryFromURL(baseUrl);
    StockStruct ss = StockUtils::convertgtImgHTTPtxtToStruct(strUnicode);
    return ss;
}

float CStock::getCurrentPrice()
{
    StockStruct ss = getStockStruct();
    return ss.d_current_price;
}

QString CStock::getStockID()
{
    return m_strStockID;
}

float CStock::getNdayline(int N)
{
//    #SELECT CURPRICE FROM stockhistory WHERE SHORSZ='sz2' AND STOCKCODE='000858' ORDER BY TRADEDATE DESC LIMIT 5;
    QSqlQuery query(StockUtils::dataBase);
    QString qsql=QString("SELECT CURPRICE, UDPERCENT FROM stocktable%4 WHERE SHORSZ='%1' AND STOCKCODE='%2' ORDER BY TRADEDATE DESC LIMIT %3;").arg(m_strSzOrSh).arg(m_strStockID).arg(N).arg(m_strStockID.right(2));
    query.exec(qsql);
    if(query.size()<N) return 0;
    query.first();
    float dayline = 0;
    for(int i = 0;i<query.size();i++)
    {
        dayline+=query.value(0).toFloat();
        if(i==0) {
            m_curPrice = query.value(0).toFloat();
            m_udpercent = query.value(1).toFloat();
        }
        if(i==1){
            m_precurprice = query.value(0).toFloat();
            m_preudpercent = query.value(1).toFloat();
        }
        query.next();
    }
    dayline = dayline/N;
    return dayline;
}

float CStock::getpreNdayline(int N)
{
    QSqlQuery query(StockUtils::dataBase);
    QString qsql=QString("SELECT CURPRICE FROM stocktable%4 WHERE SHORSZ='%1' AND STOCKCODE='%2' ORDER BY TRADEDATE DESC LIMIT %3;").arg(m_strSzOrSh).arg(m_strStockID).arg(N+1).arg(m_strStockID.right(2));
    query.exec(qsql);
    if(query.size()<N+1) return 0;
    query.first();
    query.next();
    float dayline = 0;
    for(int i = 1;i<query.size();i++)
    {
        dayline+=query.value(0).toFloat();
        query.next();
    }
    dayline = dayline/N;
    return dayline;
}

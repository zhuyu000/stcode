#ifndef STOCKSTRUCT_H
#define STOCKSTRUCT_H
#include <QString>
using namespace std;
typedef struct structStockCurrent{
    QString s_StockName;
    QString s_StockCode;
    QString t_date;
    QString t_time;
    long long d_totalnum;
    long long d_totalcurrency;
    float d_yesterday_closed_price;
    float d_today_open_price;
    float d_current_price;
    float d_today_max_price;
    float d_today_min_price;
    float d_sell_1_price;
    float d_sell_1_total;
    float d_sell_2_price;
    float d_sell_2_total;
    float d_sell_3_price;
    float d_sell_3_total;
    float d_sell_4_price;
    float d_sell_4_total;
    float d_sell_5_price;
    float d_sell_5_total;
    float d_buy_1_price;
    float d_buy_1_total;
    float d_buy_2_price;
    float d_buy_2_total;
    float d_buy_3_price;
    float d_buy_3_total;
    float d_buy_4_price;
    float d_buy_4_total;
    float d_buy_5_price;
    float d_buy_5_total;
    float d_outmarket;
    float d_inmarket;
    float d_increase;
    float d_increasepercent;
    float d_exchangeratio;
    float d_peratio;
    float d_amp;
    long long d_maketvalue;
    long long d_totalmaketvalue;
    float d_pbratio;
    float d_limitupprice;
    float d_limitdownprice;
    structStockCurrent(): d_totalnum(0),d_totalcurrency(0),
        d_yesterday_closed_price(0),d_today_open_price(0),d_current_price(0),d_today_max_price(0),d_today_min_price(0),
        d_sell_1_price(0),d_sell_1_total(0),d_sell_2_price(0),d_sell_2_total(0),d_sell_3_price(0),d_sell_3_total(0),d_sell_4_price(0),d_sell_4_total(0),d_sell_5_price(0),d_sell_5_total(0),
        d_buy_1_price(0),d_buy_1_total(0),d_buy_2_price(0),d_buy_2_total(0),d_buy_3_price(0),d_buy_3_total(0),d_buy_4_price(0),d_buy_4_total(0),d_buy_5_price(0),d_buy_5_total(0),
        d_outmarket(0),d_inmarket(0),d_increase(0),d_increasepercent(0),d_exchangeratio(0),d_peratio(0),
        d_amp(0),d_maketvalue(0),d_totalmaketvalue(0),d_pbratio(0),d_limitupprice(0),d_limitdownprice(0){}
}StockStruct;
class CStock
{
public:
    explicit CStock( QString szorsh, QString storckID):m_strSzOrSh(szorsh),m_strStockID(storckID){}
public:
    QString m_strStockID;
    QString m_strSzOrSh;
    float m_curPrice;
    float m_precurprice;
    float m_udpercent;
    float m_preudpercent;
public:
    void getDataFromTo(const QString strFrom, const QString strTo);
    void ShowCurrentData();
    QString getStockName();
    StockStruct getStockStruct();
    float getCurrentPrice();
    QString getStockID();

public:
    void convertSinaHTTPtxtToStruct(QString &txt);
    void convertgtImgHTTPtxtToStruct(QString &txt);
    float getNdayline(int N);
    float getpreNdayline(int N);
};
#endif // STOCKSTRUCT_H

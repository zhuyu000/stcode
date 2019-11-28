#ifndef STOCKSTRUCT_H
#define STOCKSTRUCT_H
#include <string>
#include <string.h>
#include <QString>
using namespace std;
typedef struct structStock{
    string s_StockName;
    string s_StockCode;
    string t_date;
    string t_time;
    float d_totalnum;
    float d_totalcurrency;
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
    float d_maketvalue;
    float d_totalmaketvalue;
    float d_pbratio;
    float d_limitupprice;
    float d_limitdownprice;
    structStock(){
        memset(this,0,sizeof(structStock));
    }
}StockStruct;
class CStock
{
public:
    CStock();
public:
    void convertSinaHTTPtxtToStruct(QString &txt);
    void convertgtImgHTTPtxtToStruct(QString &txt);
    void convert163dayKItermToStruct(QString &txt);
    void ShowStockStruct();
private:
    StockStruct m_stockstruct;
};
#endif // STOCKSTRUCT_H

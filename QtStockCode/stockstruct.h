#ifndef STOCKSTRUCT_H
#define STOCKSTRUCT_H
#include <string>
#include <iostream>
using namespace std;
typedef struct structStock{
    string s_StockName;
    string s_StockCode;
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
    string t_date;
    string t_time;
//     7: 外盘
//     8: 内盘
//    29: 最近逐笔成交
//    30: 时间
//    31: 涨跌
//    32: 涨跌%
//    33: 最高
//    34: 最低
//    35: 价格/成交量（手）/成交额
//    36: 成交量（手）
//    37: 成交额（万）
//    38: 换手率
//    39: 市盈率
//    40:
//    41: 最高
//    42: 最低
//    43: 振幅
//    44: 流通市值
//    45: 总市值
//    46: 市净率
//    47: 涨停价
//    48: 跌停价
}StockStruct;

#endif // STOCKSTRUCT_H

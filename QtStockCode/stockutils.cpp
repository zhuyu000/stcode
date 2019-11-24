#include <stockutils.h>
#include <QStringList>

    StockStruct StockUtils::convertSinaHTTPtxtToStruct(QString &txt)
    {
        //    QString baseUrl = "http://hq.sinajs.cn/list=sh600547";
        StockStruct outstruct;
        QStringList list = txt.split("\"");
        QString corestr = list[1];
        QStringList corelist = corestr.split(",");
        outstruct.s_StockName = corelist[0].toStdString();
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
        outstruct.t_date = corelist[30].toStdString();
        outstruct.t_time = corelist[31].toStdString();
        return outstruct;
    }
    void StockUtils::ShowStockStruct(StockStruct &ss)
    {
        cout<<"名称:\t"<<ss.s_StockName<<endl;
        cout<<"代码:\t"<<ss.s_StockCode<<endl;
        cout<<"昨收:\t"<<ss.d_yesterday_closed_price<<endl;
        cout<<"今开:\t"<<ss.d_today_open_price<<endl;
        cout<<"最低:\t"<<ss.d_today_min_price<<endl;
        cout<<"最高:\t"<<ss.d_today_max_price<<endl;
        cout<<"成交量:\t"<<ss.d_totalnum<<endl;
        cout<<"成交额:\t"<<ss.d_totalcurrency<<endl;
        cout<<"买一:\t"<<ss.d_buy_1_price<<endl;
        cout<<"买一量:\t"<<ss.d_buy_1_total<<endl;
        cout<<"买二:\t"<<ss.d_buy_2_price<<endl;
        cout<<"买二量:\t"<<ss.d_buy_2_total<<endl;
        cout<<"买三:\t"<<ss.d_buy_3_price<<endl;
        cout<<"买三量:\t"<<ss.d_buy_3_total<<endl;
        cout<<"买四:\t"<<ss.d_buy_4_price<<endl;
        cout<<"买四量:\t"<<ss.d_buy_4_total<<endl;
        cout<<"买五:\t"<<ss.d_buy_5_price<<endl;
        cout<<"买五量:\t"<<ss.d_buy_5_total<<endl;
        cout<<"卖一:\t"<<ss.d_sell_1_price<<endl;
        cout<<"卖一量:\t"<<ss.d_sell_1_total<<endl;
        cout<<"卖二:\t"<<ss.d_sell_2_price<<endl;
        cout<<"卖二量:\t"<<ss.d_sell_2_total<<endl;
        cout<<"卖三:\t"<<ss.d_sell_3_price<<endl;
        cout<<"卖三量:\t"<<ss.d_sell_3_total<<endl;
        cout<<"卖四:\t"<<ss.d_sell_4_price<<endl;
        cout<<"卖四量:\t"<<ss.d_sell_4_total<<endl;
        cout<<"卖五:\t"<<ss.d_sell_5_price<<endl;
        cout<<"卖五量:\t"<<ss.d_sell_5_total<<endl;
        cout<<"日期:\t"<<ss.t_date<<endl;
        cout<<"时间:\t"<<ss.t_time<<endl;
    }

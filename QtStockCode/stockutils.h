#ifndef UTILS_H
#define UTILS_H
#include <stockstruct.h>
#include <QString>
namespace StockUtils {
    StockStruct convertSinaHTTPtxtToStruct(QString &txt);
    void ShowStockStruct(StockStruct &ss);
}
#endif // UTILS_H

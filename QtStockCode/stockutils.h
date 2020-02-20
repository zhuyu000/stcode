#ifndef UTILS_H
#define UTILS_H
#include <stockstruct.h>
#include <QString>
#include <QStringList>
#include <QSqlDatabase>
namespace StockUtils {
    void QueryAndSaveAllStockList(QStringList &stringlist,const QString &strFrom,const QString &strTo);
    void ParseURLCode(QString &strURLCode,QString &szorsh);
    QString ParsesingleURLCode(QString &strURLCode,QString &szorsh);
    void ShowStockStruct(StockStruct &ss);
    QString QueryFromURL(QString &URL);
    StockStruct convert163dayKItermToStruct(QString &item);
    StockStruct convertgtImgHTTPtxtToStruct(QString &item);
    StockStruct convertSinaHTTPtxtToStruct(QString &item);
    void ConnectDB(QSqlDatabase &dataBase);
    static QSqlDatabase dataBase;
}
#endif // UTILS_H

#ifndef UTILS_H
#define UTILS_H
#include <stockstruct.h>
#include <QString>
#include <QStringList>
namespace StockUtils {
    QString QueryFromURL(QString &URL);
    void ParseURLCode(QString &strURLCode);
}
#endif // UTILS_H

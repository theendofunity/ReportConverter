#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include <QList>
#include <QMap>
#include <QJsonArray>

struct Turnover
{
    int turnover;
    QJsonArray coordinatePoints;
};

//ключ - сквок
using Report = QMap<QString, QList<Turnover>>;
#endif // REPORTMODEL_H

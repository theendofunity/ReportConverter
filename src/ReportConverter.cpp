#include "ReportConverter.h"

#include <QDebug>

ReportConverter::ReportConverter(QObject *parent)
    : QObject(parent)
    , fileManager(new FileManager(this))
{
    connect(fileManager, &FileManager::newObject, this, &ReportConverter::addJsonObject);

    fileManager->readFile();
}

ReportConverter::~ReportConverter()
{

}

void ReportConverter::addJsonObject(const QJsonObject &object)
{
    qDebug() << "Adding Json Object";

    if (not object.contains("CPs"))
        return;

    int turnoverNum = object["turnover"].toInt();
    auto points = object["CPs"].toArray();

    for (auto const cp : points)
    {
        auto cpObject = cp.toObject();

        QString squawk/* = "-"*/;   //Добавить возможность отсутствия сквока (-)
        if (cpObject.contains("Impl General"))
        {
            if (cpObject["Impl General"].toObject().contains("Squawk"))     //Добавить ЕСГРЛО
            {
                squawk = cpObject["Impl General"].toObject()["Squawk"].toString();
            }
        }
        if (report.contains(squawk) and (not squawk.isEmpty()))
        {
            for (auto cell : report[squawk].toArray())
            {
                auto singleTurnoverData = cell.toObject();
                if (singleTurnoverData["Turnover"] == turnoverNum)
                {
                    auto newField = singleTurnoverData["CPs"].toArray();
                    newField.append(cpObject);
                    singleTurnoverData["CPs"] = newField;
                    report[squawk] = singleTurnoverData;
                }
                else
                {
                    QJsonObject singleTurnover;
                    singleTurnover["Turnover"] = turnoverNum;

                    QJsonArray coordinatePoints;
                    coordinatePoints.push_back(cpObject);
                    singleTurnover["CPs"] = coordinatePoints;

                    //Копирование и перезапись элемента массива,
                    //т.к. возможности прямого изменения нет

                    auto newField = report[squawk].toArray();

                    newField.append(singleTurnover);
                    report[squawk] = newField;
                }
            }
        }
        else
        {   //вынести в отдельный метод
            QJsonObject singleTurnover;
            singleTurnover["Turnover"] = turnoverNum;

            QJsonArray coordinatePoints;
            coordinatePoints.push_back(cpObject);
            singleTurnover["CPs"] = coordinatePoints;

            QJsonArray turnovers;
            turnovers.push_back(singleTurnover);

            report[squawk] = turnovers;
        }
    }

    fileManager->writeFile(report);
}

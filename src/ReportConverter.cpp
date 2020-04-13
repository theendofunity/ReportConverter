#include "ReportConverter.h"

#include <QDebug>

#include <algorithm>

ReportConverter::ReportConverter(std::shared_ptr<FileManager> fileManager, QObject *parent)
    : QObject(parent)
    , fileManager(fileManager)
{
    connect(fileManager.get(), &FileManager::newObject, this, &ReportConverter::addJsonObjectToReport);
    connect(fileManager.get(), &FileManager::reportEnded, this, &ReportConverter::formAndWriteJson);

    fileManager->readFile();
}

ReportConverter::~ReportConverter()
{

}

void ReportConverter::addJsonObjectToReport(const QJsonObject &object)
{
    qDebug() << "Adding Json Object to Report";

    if (not object.contains("CPs"))
        return;

    int turnoverNum = object["turnover"].toInt();
    auto points = object["CPs"].toArray();

    for (auto const cp : points)
    {
        auto cpObject = cp.toObject();

        QString squawk = "-";

        if (cpObject.contains("Impl General"))
        {
            if (cpObject["Impl General"].toObject().contains("Squawk"))
            {
                squawk = cpObject["Impl General"].toObject()["Squawk"].toString();
            }
        }

        auto aircraft = newReport.find(squawk);
        if(aircraft != newReport.end())
        {
            //update
            auto findedTurnover = std::find_if(aircraft.value().begin(), aircraft.value().end(),[turnoverNum](Turnover &turn)
            {
                return turn.turnover == turnoverNum;
            });

            if (findedTurnover != aircraft.value().end())
                findedTurnover->coordinatePoints.push_back(cpObject);
            else
            {
                Turnover turnover{turnoverNum, {cpObject}};
                aircraft.value().push_back(turnover);
            }
        }
        else
        {
            //add
            Turnover turnover{turnoverNum, {cpObject}};
            newReport.insert(squawk, {turnover});
        }
    }
}

void ReportConverter::formAndWriteJson()
{
    QJsonObject obj;

    QMapIterator<QString, QList<Turnover>> it (newReport);

    while (it.hasNext())
    {
        it.next();

        QJsonArray aircraft;

        for (auto &currentTurnover : it.value())
        {
            QJsonObject turnover;

            turnover["Turnover"] = currentTurnover.turnover;
            turnover["CPs"] = currentTurnover.coordinatePoints;
            aircraft.push_back(turnover);
        }

        obj[it.key()] = aircraft;
    }

    fileManager->writeFile(obj);
}







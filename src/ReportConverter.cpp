#include "ReportConverter.h"

#include <QDebug>

#include <algorithm>

ReportConverter::ReportConverter(QObject *parent)
    : QObject(parent)
    , fileManager(new FileManager(this))
{
    connect(fileManager, &FileManager::newObject, this, &ReportConverter::addJsonObjectToReport);
    connect(fileManager, &FileManager::reportEnded, this, &ReportConverter::formAndWriteJson);
//    connect(fileManager, &FileManager::reportEnded, [this]()
//    {
//        fileManager->writeFile(report);
//    });

    fileManager->readFile();
}

ReportConverter::~ReportConverter()
{

}

void ReportConverter::addJsonObject(const QJsonObject &object)
{
//    qDebug() << "Adding Json Object";

//    if (not object.contains("CPs"))
//        return;

//    int turnoverNum = object["turnover"].toInt();
//    auto points = object["CPs"].toArray();

//    for (auto const cp : points)
//    {
//        auto cpObject = cp.toObject();

//        QString squawk/* = "-"*/;   //Добавить возможность отсутствия сквока (-)
//        if (cpObject.contains("Impl General"))
//        {
//            if (cpObject["Impl General"].toObject().contains("Squawk"))     //Добавить ЕСГРЛО
//            {
//                squawk = cpObject["Impl General"].toObject()["Squawk"].toString();
//            }
//        }
//        if (report.contains(squawk) and (not squawk.isEmpty()))
//        {
//            for (auto cell : report[squawk].toArray())
//            {
//                auto singleTurnoverData = cell.toObject();
//                if (singleTurnoverData["Turnover"] == turnoverNum)
//                {
//                    auto newField = singleTurnoverData["CPs"].toArray();
//                    newField.append(cpObject);
//                    singleTurnoverData["CPs"] = newField;
//                    report[squawk] = singleTurnoverData;
//                }
//                else
//                {
//                    QJsonObject singleTurnover;
//                    singleTurnover["Turnover"] = turnoverNum;

//                    QJsonArray coordinatePoints;
//                    coordinatePoints.push_back(cpObject);
//                    singleTurnover["CPs"] = coordinatePoints;

//                    //Копирование и перезапись элемента массива,
//                    //т.к. возможности прямого изменения нет (Переход на внутренние структуры?)

//                    auto newField = report[squawk].toArray();

//                    newField.append(singleTurnover);
//                    report[squawk] = newField;
//                }
//            }
//        }
//        else
//        {   //вынести в отдельный метод
//            QJsonObject singleTurnover;
//            singleTurnover["Turnover"] = turnoverNum;

//            QJsonArray coordinatePoints;
//            coordinatePoints.push_back(cpObject);
//            singleTurnover["CPs"] = coordinatePoints;

//            QJsonArray turnovers;
//            turnovers.push_back(singleTurnover);

//            report[squawk] = turnovers;
//        }
//    }
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

        QString squawk/* = "-"*/;

        if (cpObject.contains("Impl General"))
        {
            if (cpObject["Impl General"].toObject().contains("Squawk"))     //Добавить ЕСГРЛО
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

}







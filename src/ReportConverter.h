#ifndef REPORTCONVERTER_H
#define REPORTCONVERTER_H

#include "FileManager.h"

#include <QObject>

#include <QJsonArray>
#include <QJsonObject>

#include "ReportModel.h"

class ReportConverter : public QObject
{
public:
    ReportConverter(QObject *parent = nullptr);
    ~ReportConverter();

private:
    void addJsonObject(const QJsonObject &object);

    void addJsonObjectToReport(const QJsonObject &object);
    void formAndWriteJson();

private:
    FileManager *fileManager = nullptr;

    QJsonObject report;

    Report newReport;
};

#endif // REPORTCONVERTER_H

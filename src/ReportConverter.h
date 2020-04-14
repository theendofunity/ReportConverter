#ifndef REPORTCONVERTER_H
#define REPORTCONVERTER_H

#include "FileManager.h"

#include <memory>
#include <QObject>

#include <QJsonArray>
#include <QJsonObject>

#include "ReportModel.h"

class ReportConverter : public QObject
{
public:
    ReportConverter(std::shared_ptr<FileManager> fileManager, QObject *parent = nullptr);
    ~ReportConverter();

private:
    void addJsonObjectToReport(const QJsonObject &object);
    void formAndWriteJson();

private:
    std::shared_ptr<FileManager> fileManager;

    Report report;
};

#endif // REPORTCONVERTER_H

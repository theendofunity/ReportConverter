#ifndef REPORTCONVERTER_H
#define REPORTCONVERTER_H

#include "FileManager.h"

#include <QObject>

#include <QJsonArray>
#include <QJsonObject>

class ReportConverter : public QObject
{
public:
    ReportConverter(QObject *parent = nullptr);
    ~ReportConverter();

private:
    void addJsonObject(const QJsonObject &object);
private:
    FileManager *fileManager = nullptr;

    QJsonObject report;
};

#endif // REPORTCONVERTER_H

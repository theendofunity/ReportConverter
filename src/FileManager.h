#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

#include <QJsonDocument>
#include <QStandardPaths>
#include <QTime>

class FileManager : public QObject
{
    Q_OBJECT
public:
    FileManager(QObject *parent = nullptr);

    void readFile();
    void writeFile(QList<QJsonObject> &objects);

    void setSourcePath(QString path);
    void setTargetPath(QString path);
signals:
    void newObject(const QJsonObject &object);
    void reportEnded();

private:
    QTime startTime;

    QString sourcePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/Report.json";
    QString targetPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/AircraftReport.json";
};

#endif // FILEMANAGER_H

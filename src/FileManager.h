#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

#include <QJsonDocument>
#include <QTime>

class FileManager : public QObject
{
    Q_OBJECT
public:
    FileManager(QObject *parent = nullptr);

    void readFile();
    void writeFile(QJsonObject &obj);

signals:
    void newObject(const QJsonObject &object);
    void reportEnded();

private:
    QTime startTime;
};

#endif // FILEMANAGER_H

#include "FileManager.h"

#include <QFile>
#include <QString>
#include <QStandardPaths>
#include <QJsonObject>

#include <QDebug>

const QString pathToRead = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/Report.json";
const QString pathToWrite = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/SingleObject.json";

FileManager::FileManager(QObject *parent)
    : QObject(parent)
{

}

void FileManager::readFile()
{
    startTime.start();

    QFile file(pathToRead);

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "********************** Reading file **********************";


        QByteArray data;
        while (not file.atEnd())
        {
            auto str = file.readLine();

            data.push_back(str);

            if (str.contains("turnover"))
            {
                str = file.readLine();
                if (str.endsWith(", \n"))
                    str.remove(str.size() - 3, 3);
                else
                    file.readLine();

                data.push_back(str);

                QJsonDocument doc(QJsonDocument::fromJson(data));

                emit newObject(doc.object());

                data.clear();
            }
        }
        emit reportEnded();
    }
    else
        qDebug() << "Error! Can not read file";

    file.close();
}

void FileManager::writeFile(QJsonObject &obj)
{
    qDebug() << "********************** Writing File **********************";

    QFile file (pathToWrite);
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
        QJsonDocument doc;
        doc.setObject(obj);

        file.write(doc.toJson());
        file.close();

        qDebug() << "********************** Writing Complited **********************";

        qDebug() << "Commlited in " << startTime.elapsed() << "ms";
    }
    else
        qDebug() << "Error! Can not write to file";
}












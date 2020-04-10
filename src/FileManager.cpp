#include "FileManager.h"

#include <QFile>
#include <QString>
#include <QStandardPaths>

#include <QDebug>

const QString pathToRead = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/Report.json";
const QString pathToWrite = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/SingleObject.json";

FileManager::FileManager()
{

}

void FileManager::readFile()
{
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
                data.push_back(str);
                QJsonDocument doc(QJsonDocument::fromJson(data));

                writeFile(doc);
                break;
            }

        }
    }
    else
        qDebug() << "Error! Can not read file";

    file.close();
}

void FileManager::writeFile(QJsonDocument &doc)
{
    qDebug() << "********************** Writing File **********************";

    QFile file (pathToWrite);
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
        file.write(doc.toJson());
        file.close();
    }
}












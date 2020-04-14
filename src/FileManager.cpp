#include "FileManager.h"

#include <QFile>
#include <QString>
#include <QJsonObject>

#include <QDebug>

FileManager::FileManager(QObject *parent)
    : QObject(parent)
{

}

void FileManager::readFile()
{
    startTime.start();

    QFile file(sourcePath);

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

void FileManager::writeFile(QList<QJsonObject> &objects)
{
    qDebug() << "********************** Writing File **********************";

    QFile file (targetPath);
    if (file.open(QFile::Append | QFile::Text))
    {
        for (auto &obj : objects)
        {
            QJsonDocument doc;
            doc.setObject(obj);

            file.write(doc.toJson());
        }
        file.close();

        qDebug() << "******************** Writing Complited *******************";

        qDebug() << "Commlited in " << startTime.elapsed() << "ms";
    }
    else
        qDebug() << "Error! Can not write to file";
}

void FileManager::setSourcePath(QString path)
{
    sourcePath = path;
}

void FileManager::setTargetPath(QString path)
{
    targetPath = path;
}












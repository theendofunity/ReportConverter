#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QJsonDocument>

class FileManager
{
public:
    FileManager();

    void readFile();
    void writeFile(QJsonDocument &doc);

};

#endif // FILEMANAGER_H

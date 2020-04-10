#include <QCoreApplication>

#include <FileManager.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileManager manager;
    manager.readFile();

    return a.exec();
}

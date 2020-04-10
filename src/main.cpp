#include <QCoreApplication>

#include <memory>
#include "ReportConverter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::unique_ptr<ReportConverter> converter = std::make_unique<ReportConverter>();

    return a.exec();
}

#include <QCoreApplication>

#include <memory>
#include <QDebug>
#include <QCommandLineParser>

#include "ReportConverter.h"
#include "FileManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addPositionalArgument("Source report", QCoreApplication::translate("main", "Source report"));
    parser.addPositionalArgument("Target report", QCoreApplication::translate("main", "Target report"));
    parser.process(a);

    auto args = parser.positionalArguments();

    std::shared_ptr<FileManager> fileManager = std::make_shared<FileManager>();
    if (not args.isEmpty())
        fileManager->setSourcePath(args.at(0));
    if (args.size() > 1)
        fileManager->setTargetPath(args.at(1));

    std::unique_ptr<ReportConverter> converter = std::make_unique<ReportConverter>(fileManager);

    return a.exec();
}

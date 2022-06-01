#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include "moduleimportextension.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile mainScriptFile("main.js");
    if (!mainScriptFile.open(QIODevice::ReadOnly))
        return -1;

    QTextStream stream(&mainScriptFile);
    QString contents = stream.readAll();
    mainScriptFile.close();

    QJSEngine engine;
    engine.installExtensions(QJSEngine::ConsoleExtension);
    ModuleImportExtension::installExtension(&engine, "importModule");

    engine.evaluate(contents, "main.js").toString();

    return a.exec();
}

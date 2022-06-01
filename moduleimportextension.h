#ifndef MODULEIMPORTEXTENSION_H
#define MODULEIMPORTEXTENSION_H

#include <QJSEngine>
#include <QDir>
#include <QDebug>

class ModuleImportExtension : public QObject
{
    Q_OBJECT

public:
    static bool installExtension(QJSEngine* engine, const QString& jsFunctionName, const QDir& baseDir) {
        if (!engine) return false;

        auto extObj = engine->newQObject(new ModuleImportExtension(engine, baseDir, engine));
        if (!extObj.hasProperty("import")) return false;

        engine->globalObject().setProperty(jsFunctionName, extObj.property("import"));
        if (!engine->globalObject().hasProperty(jsFunctionName)) return false;

        return true;
    }

    inline static bool installExtension(QJSEngine* engine, const QString& jsFunctionName) {
        return installExtension(engine, jsFunctionName, QDir::current());
    }

protected:
    ModuleImportExtension(QJSEngine* engine, const QDir& baseDir, QObject* parent)
        : QObject(parent), m_engine(engine), m_baseDir(baseDir) {}

    Q_INVOKABLE bool import(const QString& relativePath, const QString& jsIdentifier)
    {
        if (!m_engine) {
            logError("ModuleImportExtension: QJSEngine object is null");
            return false;
        }

        if (!QFile::exists(m_baseDir.absoluteFilePath(relativePath))) {
            logError("ModuleImportExtension: Invalid module path (" + relativePath + ")");
            return false;
        }

        if (!QRegExp(m_jsIdentifierRegex).exactMatch(jsIdentifier)) {
            logError("ModuleImportExtension: Invalid module JS identifier (" + jsIdentifier + ")");
            return false;
        }

        auto moduleJsVal = m_engine->importModule(m_baseDir.absoluteFilePath(relativePath));

        if (moduleJsVal.isError()) {
            logError(QString("ModuleImportExtension: Module %1 evaluation error (lineNumber: %2, message: %3)")
                     .arg(jsIdentifier)
                     .arg(QString::number(moduleJsVal.property("lineNumber").toInt()))
                     .arg(moduleJsVal.property("message").toString()));
            return false;
        }

        m_engine->globalObject().setProperty(jsIdentifier, moduleJsVal);

        if (!m_engine->globalObject().hasProperty(jsIdentifier)) {
            logError("ModuleImportExtension: Can't find module " + jsIdentifier + " in JS engine global object");
            return false;
        }

        return true;
    }

    virtual void logError(const QString& msg) const {
        qWarning() << msg;
    }

private:
    QJSEngine* m_engine;
    QDir m_baseDir;

    static constexpr const char* m_jsIdentifierRegex = "[a-zA-Z_][0-9a-zA-Z_]*";
};


#endif // MODULEIMPORTEXTENSION_H

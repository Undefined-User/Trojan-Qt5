#include "modehelper.h"
#include "utils.h"

#include <QDir>
#include <QStringBuilder>
#include <QJsonArray>
#include <QJsonDocument>

ModeHelper::ModeHelper()
{

}

QStringList ModeHelper::listAllModes()
{
    QString path = QDir::toNativeSeparators(Utils::getConfigPath() + "/mode");
    QDir dir(path);
    QStringList filters;
    filters << "*.json";
    QStringList result = dir.entryList(filters, QDir::Files|QDir::Readable, QDir::Name).replaceInStrings(".json", "");
    return result;
}

QString ModeHelper::readProcess(QString name)
{
    QString path = QDir::toNativeSeparators(Utils::getConfigPath() + "/mode");
    QString fileName = QDir::toNativeSeparators(path % "/" % name % ".json");
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly | QFile::Text);
    QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
    QJsonObject object = doc.object();
    QJsonArray array = object["process"].toArray();
    QString process;
    for (QJsonValue value : array) {
        QString data = value.toString();
        process = process % data % ",";
    }
    process = process % "NatTypeTester.exe";
    return process;
}

QStringList ModeHelper::readProcessToList(QString name)
{
    QString path = QDir::toNativeSeparators(Utils::getConfigPath() + "/mode");
    QString fileName = QDir::toNativeSeparators(path % "/" % name % ".json");
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly | QFile::Text);
    QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
    QJsonObject object = doc.object();
    QJsonArray array = object["process"].toArray();
    QStringList process;

    for (QJsonValue val : array) {
        QString data = val.toString();
        process.append(data);
    }

    return process;
}

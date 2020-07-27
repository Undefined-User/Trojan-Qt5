#include "resourcehelper.h"
#include "utils.h"

#include <QProcess>
#include <QDir>
#include <QFile>
#include <QStandardPaths>

ResourceHelper::ResourceHelper()
{}

bool ResourceHelper::isSystemProxyHelperExist()
{
    QFile file("/Library/Application Support/Trojan-Qt5/proxy_conf_helper");
    return file.exists();
}

void ResourceHelper::installSystemProxyHelper()
{
    QDir fileDir = QDir::toNativeSeparators(Utils::getConfigPath() + "/temp");
    if (!fileDir.exists()) {
        fileDir.mkpath(".");
    }

    QFile::copy(":/bin/proxy_conf_helper", fileDir.path() + "/proxy_conf_helper");
    QFile::copy(":/scripts/install_helper.sh", fileDir.path() + "/install_helper.sh");

    QProcess *task = new QProcess;
    QStringList param;
    QString script = QString("do shell script \"bash %1 \" with administrator privileges").arg(fileDir.path() + "/install_helper.sh");
    param << "-l" << "AppleScript";
    task->start("/usr/bin/osascript", param);
    task->write(script.toUtf8());
    task->closeWriteChannel();
    task->waitForFinished();
}


void ResourceHelper::copyNatTypeTester()
{
    QDir fileDir = QDir::toNativeSeparators(Utils::getConfigPath() + "/bin");
    if (!fileDir.exists()) {
        fileDir.mkpath(".");
    }

    QFile nttFile = fileDir.path() + "/NatTypeTester.exe";

    if (!nttFile.exists()) {
        QFile::copy(":/bin/NatTypeTester.exe", fileDir.path() + "/NatTypeTester.exe");
    }
}

void ResourceHelper::copyNfsdk2()
{
    QDir fileDir = QDir::toNativeSeparators(Utils::getConfigPath() + "/bin");
    if (!fileDir.exists()) {
        fileDir.mkpath(".");
    }

    QFile redirectorFile = fileDir.path() + "/Redirector.exe";
    QFile nfapiDll = fileDir.path() + "/nfapi.dll";
    QFile win7Sys = fileDir.path() + "/win7.sys";
    QFile win8Sys = fileDir.path() + "/win8.sys";
    QFile win10Sys = fileDir.path() + "/win10.sys";


    if (!redirectorFile.exists())
        QFile::copy(":/bin/Redirector.exe", fileDir.path() + "/Redirector.exe");

    if (!nfapiDll.exists())
        QFile::copy(":/bin/nfapi.dll", fileDir.path() + "/nfapi.dll");

    if (!win7Sys.exists())
        QFile::copy(":/bin/win7.sys", fileDir.path() + "/win7.sys");

    if (!win8Sys.exists())
        QFile::copy(":/bin/win8.sys", fileDir.path() + "/win8.sys");

    if (!win10Sys.exists())
        QFile::copy(":/bin/win10.sys", fileDir.path() + "/win10.sys");

    QDir tempModeDir(":/mode/");
    QDir modeDir = QDir::toNativeSeparators(Utils::getConfigPath() + "/mode");
    if (!modeDir.exists()) {
        modeDir.mkpath(".");

        QStringList filters;
        filters << "*.json";
        QStringList list = tempModeDir.entryList(filters, QDir::Files);

        foreach(QString file, list) {
            QFile::copy(QString(":/mode/%1").arg(file), QDir::toNativeSeparators(modeDir.path() + "/" + file));
        }
    }
}

void ResourceHelper::installTAPDriver()
{
    QDir configDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/Trojan-Qt5";
    if (!configDir.exists()) {
        configDir.mkpath(".");
    }

    QString tapInstallerPath = configDir.path() + "/tap-windows-9.21.2.exe";

    if (!QFile::exists(tapInstallerPath))
        QFile::copy(":/bin/tap-windows-9.21.2.exe", tapInstallerPath);

    QStringList param;
    param << "/S";
    QProcess::startDetached(tapInstallerPath, param);
}

void ResourceHelper::openEnableUWPLoopback()
{
    QDir configDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/Trojan-Qt5";
    if (!configDir.exists()) {
        configDir.mkpath(".");
    }

    QString enableUWPLoopbackPath = configDir.path() + "/EnableLoopback.exe";

    if (!QFile::exists(enableUWPLoopbackPath))
        QFile::copy(":/bin/EnableLoopback.exe", enableUWPLoopbackPath);

    QProcess::startDetached(enableUWPLoopbackPath);
}

void ResourceHelper::copyDatFiles()
{
    QDir fileDir = QDir::toNativeSeparators(Utils::getConfigPath() + "/dat");
    if (!fileDir.exists()) {
        fileDir.mkpath(".");
    }

    QFile geoipFile = QDir::toNativeSeparators(fileDir.path() + "/geoip.dat");
    QFile geositeFile = QDir::toNativeSeparators(fileDir.path() + "/geosite.dat");

    if (!geoipFile.exists()) {
        QFile::copy(":/dat/geoip.dat", fileDir.path() + "/geoip.dat");
    }

    if (!geositeFile.exists()) {
        QFile::copy(":/dat/geosite.dat", fileDir.path() + "/geosite.dat");
    }

}

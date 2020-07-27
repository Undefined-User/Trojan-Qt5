#include "nfsdk2controller.h"
#include "nfsdk2helper.h"
#include "utils.h"
#include "logger.h"
#include "modehelper.h"

#include <QFile>

NFSDK2Controller::NFSDK2Controller()
{}

NFSDK2Controller::~NFSDK2Controller()
{}

void NFSDK2Controller::start()
{
#if defined (Q_OS_WIN)
    ConfigHelper *helper = Utils::getConfigHelper();

    QString _driverPath = Utils::getSystemDirectory() + "\\drivers\\netfilter2.sys";
    QString systemDriverVersion = Utils::getFileVersion(_driverPath);
    QString version = Utils::getSystemVersion();
    if (version == "10.00")
        version = "win10.sys";
    else if (version == "6.3" || version == "6.2")
        version = "win8.sys";
    else if (version == "6.1" || version == "6.0")
        version = "win7.sys";
    QString binDriverVersion = Utils::getFileVersion(QDir::toNativeSeparators(Utils::getConfigPath() + QString("/bin/%1").arg(version)));

    Logger::info(QString("[NFSDK2] Internal driver version: %1").arg(binDriverVersion));

    if (systemDriverVersion != binDriverVersion) {
        if (QFile::exists(_driverPath)) {
            Logger::info(QString("[NFSDK2] System driver version: %1").arg(systemDriverVersion));
            Logger::info("[NFSDK2] Updating driver...");
            NFSDK2Helper::uninstallDriver();
        }

        NFSDK2Helper::installDriver();
    }

    QString path = QDir::toNativeSeparators(Utils::getConfigPath() + "/bin/Redirector.exe");
    QString process = ModeHelper::readProcess(helper->getModeSettings().redirectorMode);
    QString param = QString("-r 127.0.0.1:%1 -p %2 -t %3").arg(QString::number(helper->getInboundSettings().socks5LocalPort)).arg(process).arg(QString::number(helper->getInboundSettings().redirectorPort));

    delete helper;
    helper = nullptr;

    piProcessInfo = Utils::createProcessWithoutWindow(path, param);
#endif
}

void NFSDK2Controller::stop()
{
#if defined (Q_OS_WIN)
    TerminateProcess(piProcessInfo.hProcess, 0);
#endif
}

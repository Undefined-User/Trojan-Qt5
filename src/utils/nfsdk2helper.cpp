#if defined (Q_OS_WIN)
#include <Windows.h>
#include "ServiceController.h"
#include "nfapi.h"
#include "nfevents.h"
#endif

#include "nfsdk2helper.h"
#include "utils.h"
#include "logger.h"

NFSDK2Helper::NFSDK2Helper()
{}

bool NFSDK2Helper::installDriver()
{
#if defined (Q_OS_WIN)
    QString _driverPath = Utils::getSystemDirectory() + "\\drivers\\netfilter2.sys";

    QString version = Utils::getSystemVersion();
    if (version == "10.00")
        QFile::copy(":/bin/win10.sys", _driverPath);
    else if (version == "6.3" || version == "6.2")
        QFile::copy(":/bin/win8.sys", _driverPath);
    else if (version == "6.1" || version == "6.0")
        QFile::copy(":/bin/win7.sys", _driverPath);
    else {
        Logger::error(QString("[NFSDK2] Unsupported system version: %1").arg(version));
        return false;
    }

    int status = nfapi::nf_registerDriver("netfilter2");
    if (status != NF_STATUS::NF_STATUS_SUCCESS) {
        Logger::error(QString("[NFSDK2] Failed to register device, code %1").arg(status));
        return false;
    }

    return true;
#else
    return false;
#endif
}

bool NFSDK2Helper::uninstallDriver()
{
#if defined (Q_OS_WIN)
    QString _driverPath = Utils::getSystemDirectory() + "\\drivers\\netfilter2.sys";

    QString version = Utils::getSystemVersion();
    if (version == "10.00")
        QFile::copy(QDir::toNativeSeparators(Utils::getConfigPath() + "/bin/win10.sys"), _driverPath);
    else if (version == "6.3" || version == "6.2")
        QFile::copy(QDir::toNativeSeparators(Utils::getConfigPath() + "/bin/win8.sys"), _driverPath);
    else if (version == "6.1" || version == "6.0")
        QFile::copy(QDir::toNativeSeparators(Utils::getConfigPath() + "/bin/win7.sys"), _driverPath);
    else {
        Logger::error(QString("[NFSDK2] Unsupported system version: %1").arg(version));
        return false;
    }

    auto service = ServiceController{L"netfilter2"};
    if (service.GetStatus() == ServiceStatus::Running) {
        service.Stop();
        service.WaitForStatus(ServiceStatus::Stopped);
    }

    if (!QFile::exists(_driverPath))
        return true;

    nfapi::nf_unRegisterDriver("netfilter2");

    QFile::remove(_driverPath);

    return true;
#else
    return false;
#endif
}

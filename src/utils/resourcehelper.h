#ifndef RESOURCEHELPER_H
#define RESOURCEHELPER_H

#include <QSettings>

class ResourceHelper
{
public:
    ResourceHelper();

    static bool isSystemProxyHelperExist();
    static void installSystemProxyHelper();

    static void copyNatTypeTester();
    static void copyNfsdk2();

    static void installTAPDriver();
    static void openEnableUWPLoopback();

    static void copyDatFiles();
};

#endif // RESOURCEHELPER_H

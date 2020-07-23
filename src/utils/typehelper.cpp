#include "typehelper.h"

#include <QDir>

TypeHelper::TypeHelper()
{

}

QString TypeHelper::queryShadowsocksPluginName(QString name)
{
    if (name.isEmpty()) {
        return "NONE";
    }

    QFileInfo fileInfo(name);
    QString fileName = fileInfo.fileName();
    int index = fileName.lastIndexOf(".");
    fileName.truncate(index);

    return fileName.toUpper();
}

QString TypeHelper::queryTrojanType(TrojanGoSettings trojanGoSettings)
{
    if (trojanGoSettings.mux.enable || trojanGoSettings.websocket.enable || trojanGoSettings.shadowsocks.enable || trojanGoSettings.transportPlugin.enable) {
        return "GO";
    } else {
        return "GFW";
    }
}

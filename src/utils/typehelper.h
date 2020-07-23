#ifndef TYPEHELPER_H
#define TYPEHELPER_H

#include "trojangostruct.h"

#include <QObject>

class TypeHelper : public QObject
{
    Q_OBJECT
public:
    TypeHelper();

    static QString queryShadowsocksPluginName(QString name);
    static QString queryTrojanType(TrojanGoSettings trojanGoSettings);

};

#endif // TYPEHELPER_H

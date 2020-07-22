#ifndef MODEHELPER_H
#define MODEHELPER_H

#include <QObject>

class ModeHelper: public QObject
{
    Q_OBJECT
public:
    ModeHelper();

    static QStringList listAllModes();
    static QString readProcess(QString name);
    static QStringList readProcessToList(QString name);
};

#endif // MODEHELPER_H

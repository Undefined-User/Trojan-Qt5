#ifndef NATTYPETESTERCONTROLLER_H
#define NATTYPETESTERCONTROLLER_H

#include <QObject>
#include <QProcess>

class NatTypeTesterController : public QObject
{
    Q_OBJECT

public:
    NatTypeTesterController();
    ~NatTypeTesterController();

public slots:
    void startTesting();
    void onDataReady();

signals:
    void natTypeFinished(const QString&);

private:
    QProcess *m_process;
};

#endif // NATTYPETESTERCONTROLLER_H

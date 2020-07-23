#ifndef NFSDK2CONTROLLER_H
#define NFSDK2CONTROLLER_H

#include <QThread>
#include <QProcess>

#if defined (Q_OS_WIN)
#include <Windows.h>
#include <memory>
#endif

class NFSDK2Controller : public QThread
{
public:
    NFSDK2Controller();
    ~NFSDK2Controller();

public:
    void start();
    void stop();

private:
    PROCESS_INFORMATION piProcessInfo;

};

#endif // NFSDK2CONTROLLER_H

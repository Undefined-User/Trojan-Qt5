#include "nattypetestercontroller.h"
#include "utils.h"

NatTypeTesterController::NatTypeTesterController()
{}

NatTypeTesterController::~NatTypeTesterController()
{}

void NatTypeTesterController::startTesting()
{
    ConfigHelper *helper = Utils::getConfigHelper();

    m_process = new QProcess(this);
    connect(m_process,
            SIGNAL(readyReadStandardOutput()),
            this,
            SLOT(onDataReady()));
    m_process->setReadChannel(QProcess::StandardOutput);
    QString path = QDir::toNativeSeparators(Utils::getConfigPath() + "/bin/NatTypeTester.exe");
    QStringList param;
    param << helper->getSTUNSettings().address << QString::number(helper->getSTUNSettings().port);

    delete helper;
    helper = nullptr;

    m_process->start(path, param);
}

void NatTypeTesterController::onDataReady()
{
    QStringList data = QString(m_process->readAllStandardOutput()).split("#");
    QString natType = data[0];
    emit natTypeFinished(natType);
    m_process->kill();
}

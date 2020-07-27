#include "utils.h"
#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QStyle>
#include <QJsonObject>
#include <QJsonDocument>
#if defined (Q_OS_WIN)
#include <Windows.h>
#endif

Utils::Utils()
{}

QString Utils::Base64UrlEncode(QString plainText)
{
    QString encodedText = plainText.toUtf8().toBase64();
    encodedText = encodedText.replace(QChar('+'), QChar('-')).replace(QChar('/'), QChar('_')).replace(QChar('='), "");
    return encodedText;
}

QString Utils::Base64UrlDecode(QString encodedText)
{
    QByteArray encodedArray = encodedText.replace(QChar('-'), QChar('+')).replace(QChar('_'), QChar('/')).toUtf8();
    QString plainText = QByteArray::fromBase64(encodedArray, QByteArray::Base64Option::OmitTrailingEquals);
    return plainText;
}

QStringList Utils::splitLines(const QString &string)
{
    return string.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
}

QString Utils::toCamelCase(const QString& s)
{
    QStringList parts = s.split(' ', QString::SkipEmptyParts);
    for (int i = 0; i < parts.size(); ++i)
        parts[i].replace(0, 1, parts[i][0].toUpper());

    return parts.join(" ");
}

QString Utils::toQString(const QJsonObject &object)
{
    return QJsonDocument(object).toJson(QJsonDocument::Compact).toStdString().c_str();
}

QString Utils::getLogDir()
{
#if defined (Q_OS_WIN)
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#elif defined(Q_OS_MAC)
    return QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/Library/Logs/Trojan-Qt5";
#elif defined (Q_OS_LINUX)
    return QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation) + "/trojan-qt5";
#endif
}

void Utils::setPermisison(QString &file)
{
    QFile::setPermissions(file, QFile::ReadOwner | QFile::WriteOwner | QFile::ReadGroup | QFile::WriteGroup);
}

QSize Utils::smallIconSize(const QWidget *widget)
{
    // Get DPI scaled icon size (device-dependent), see QT source
    // under a 1080p screen is usually 16x16
    const int s = QApplication::style()->pixelMetric(QStyle::PM_SmallIconSize, nullptr, widget);
    return {s, s};
}

QSize Utils::mediumIconSize(const QWidget *widget)
{
    // under a 1080p screen is usually 24x24
    return ((smallIconSize(widget) + largeIconSize(widget)) / 2);
}

QSize Utils::largeIconSize(const QWidget *widget)
{
    // Get DPI scaled icon size (device-dependent), see QT source
    // under a 1080p screen is usually 32x32
    const int s = QApplication::style()->pixelMetric(QStyle::PM_LargeIconSize, nullptr, widget);
    return {s, s};
}

QString Utils::bytesConvertor(const quint64 &t)
{
    if (t >= (double)1024L * (double)1024L * (double)1024L * (double)1024L)
        return QString::number(t / (double)1024 / (double)1024 / (double)1024 / (double)1024, 'f', 2) + " TB";
    else if (t >= (double)1024L * (double)1024L * (double)1024L)
        return QString::number(t / (double)1024 / (double)1024 / (double)1024, 'f', 2) + " GB";
    else if (t >= (double)1024 * (double)1024)
        return QString::number(t / (double)1024 / (double)1024, 'f', 2) + " MB";
    else if (t >= (double)1024)
        return QString::number(t / (double)1024, 'f', 2) + " KB";
    else
        return QString::number(t, 'f', 2) + " B";
}

QString Utils::getConfigPath()
{
#ifdef Q_OS_WIN
    QString configPath = qApp->applicationDirPath();
#else
    QDir configDir = QDir::homePath() + "/.config/trojan-qt5";
    QString configPath = configDir.absolutePath();
#endif

    return configPath;
}

ConfigHelper* Utils::getConfigHelper()
{
    QString configFile = getConfigPath() + "/config.ini";
    ConfigHelper *helper = new ConfigHelper(configFile);
    return helper;
}

QJsonObject Utils::convertWsHeader(QList<WsHeader> headers)
{
    QJsonObject object;
    for (WsHeader header : headers)
        object[header.key] = header.value;
    return object;
}

QList<WsHeader> Utils::convertQJsonObject(const QJsonObject &object)
{
    QList<WsHeader> wsHeaders;
    for (const QString &key : object.keys()) {
        QJsonValue val = object.value(key);
        WsHeader header;
        header.key = key;
        header.value = val.toString();
        wsHeaders.append(header);
    }
    return wsHeaders;
}

#if defined (Q_OS_WIN)
PROCESS_INFORMATION Utils::createProcessWithoutWindow(QString application, QString arg)
{
    QString path = application + " " + arg;
    LPTSTR ARG = (LPTSTR) path.utf16();

    STARTUPINFO siStartupInfo;
    PROCESS_INFORMATION piProcessInfo;
    memset(&siStartupInfo, 0, sizeof(siStartupInfo));
    memset(&piProcessInfo, 0, sizeof(piProcessInfo));

    siStartupInfo.cb = sizeof(siStartupInfo);
    siStartupInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_FORCEOFFFEEDBACK | STARTF_USESTDHANDLES;
    siStartupInfo.wShowWindow = SW_HIDE;

    if(CreateProcess(NULL, ARG, 0, 0, FALSE, 0, 0, 0, &siStartupInfo, &piProcessInfo) == FALSE)
    {
        CloseHandle(piProcessInfo.hThread);
        CloseHandle(piProcessInfo.hProcess);
    }

    return piProcessInfo;
}
#endif

QString Utils::getSystemDirectory()
{
#if defined (Q_OS_WIN)
    char buffer[MAX_PATH];
    DWORD n = GetSystemDirectoryA(buffer, sizeof(buffer));
    std::string result(buffer, n);
    return QString::fromStdString(result);
#else
    return "";
#endif
}

QString Utils::getSystemVersion()
{
#if defined (Q_OS_WIN)
    DWORD dwVersion = 0;
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0;
    dwVersion = GetVersion();

    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    return QString("%1.%2").arg(dwMajorVersion).arg(dwMinorVersion);
#else
    return "";
#endif
}

QString Utils::getFileVersion(QString fName)
{
#if defined (Q_OS_WIN)
    // first of all, GetFileVersionInfoSize
    DWORD dwHandle;
    DWORD dwLen = GetFileVersionInfoSize(fName.toStdWString().c_str(), &dwHandle);

    // GetFileVersionInfo
    LPVOID lpData = new BYTE[dwLen];
    if (!GetFileVersionInfo(fName.toStdWString().c_str(), dwHandle, dwLen, lpData)) {
        delete[] lpData;
        return "";
    }

    // VerQueryValue
    VS_FIXEDFILEINFO* lpBuffer = NULL;
    UINT uLen;

    if (!VerQueryValue(lpData,
        QString("\\").toStdWString().c_str(),
        (LPVOID*)& lpBuffer,
        &uLen)) {
        delete[] lpData;
        return "";
    } else {
        return QString::number((lpBuffer->dwFileVersionMS >> 16) & 0xffff) + "." +
               QString::number((lpBuffer->dwFileVersionMS) & 0xffff) + "." +
               QString::number((lpBuffer->dwFileVersionLS >> 16) & 0xffff) + "." +
               QString::number((lpBuffer->dwFileVersionLS) & 0xffff);
    }
#else
    return "";
#endif
}

/*
QString Utils::getLocalAddr()
{
#ifdef Q_OS_WIN
    QString configFile = qApp->applicationDirPath() + "/config.ini";
#else
    QDir configDir = QDir::homePath() + "/.config/trojan-qt5";
    QString configFile = configDir.absolutePath() + "/config.ini";
#endif

    ConfigHelper *conf = new ConfigHelper(configFile);
    return
}*/

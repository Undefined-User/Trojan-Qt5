#ifndef CONFIGSTRUCT_H
#define CONFIGSTRUCT_H

#include <QObject>
#include <QColor>
#include <QVariant>

struct GeneralSettings {
    QString theme = "Fusion";
    int systemTheme = 2;
    int toolBarStyle = 3;
    QString language = "Follow System";
    int logLevel = 1;
    int systemTrayMaximumServer = 0;
    bool startAtLogin = false;
    bool hideWindowOnStartup = false;
    bool onlyOneInstace = true;
    bool checkPortAvailability = true;
    bool checkTimeOnStartup = true;
    bool enableNotification = true;
    bool hideDockIcon = false;
    bool showToolbar = true;
    bool showFilterBar = true;
    bool nativeMenuBar = false;
    bool showAirportAndDonation = true;
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(GeneralSettings)

struct InboundSettings {
    bool enableHttpMode = true;
    bool shareOverLan = false;
    bool enableIpv6Support = false;
    bool inboundSniffing = false;
    int socks5LocalPort = 51837;
    int httpLocalPort = 58591;
    int pacLocalPort = 54400;
    int redirectorPort = 56872;
    int haproxyStatusPort = 2080;
    int haproxyPort = 7777;
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(InboundSettings)

struct OutboundSettings {
    bool bypassBittorrent = false;
    bool bypassPrivateAddress = false;
    bool bypassChinaMainland = false;
    bool forwardProxy = false;
    int forwardProxyType = 0;
    QString forwardProxyAddress = "127.0.0.1";
    int forwardProxyPort = 1086;
    bool forwardProxyAuthentication = false;
    QString forwardProxyUsername;
    QString forwardProxyPassword;
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(OutboundSettings)

struct TestSettings {
    int method = 0;
    QString latencyTestUrl = "https://www.google.com/generate_204";
    QString speedTestUrl = "http://speedtest-sgp1.digitalocean.com/10mb.test";
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(TestSettings)

struct SubscribeSettings {
    int gfwListUrl = 2;
    QString updateUserAgent = QString("Trojan-Qt5/%1").arg(APP_VERSION);
    QString filterKeyword;
    int maximumSubscribe = 0;
    bool autoFetchGroupName = true;
    bool overwriteAllowInsecure = false;
    bool overwriteAllowInsecureCiphers = false;
    bool overwriteTcpFastOpen = false;
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(SubscribeSettings)

struct GraphSettings {
    bool detailOutboundProxy = false;
    bool detailOutboundDirect = false;
    QString proxyDownloadSpeedColor = QColor::fromRgb(235, 220, 42).name();
    QString proxyUploadSpeedColor = QColor::fromRgb(20, 210, 240).name();
    QString directDownloadSpeedColor = QColor::fromRgb(50, 153, 255).name();
    QString directUploadSpeedColor = QColor::fromRgb(134, 196, 63).name();
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(GraphSettings)

struct RouterSettings {
    QString domainStrategy = "AsIs";
    QStringList domainDirect;
    QStringList domainProxy;
    QStringList domainBlock;
    QStringList ipDirect;
    QStringList ipProxy;
    QStringList ipBlock;
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(RouterSettings)

struct CoreSettings {
    int fingerprint = 1;
    bool enableAPI = true;
    bool enableRouter = false;
    bool countOutboundTraffic = false;
    QString geoPath;
    int apiPort = 57721;
    QString trojanCertPath;
    QString trojanCipher = "";
    int bufferSize = 32;
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(CoreSettings)

struct TUNTAPSettings {
    QString address = "240.0.0.2";
    QString netmask = "255.255.255.0";
    QString gateway = "240.0.0.1";
    QString dns = "1.1.1.1";
    bool customDNS = false;
    bool fakeDNS = false;
    QStringList bypassIPs;
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(TUNTAPSettings)

struct STUNSettings {
    QString address = "stun.stunprotocol.org";
    int port = 3478;
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(STUNSettings)

struct ModeSettings {
    int mode = 0;
    QString redirectorMode;
    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(ModeSettings)

QDataStream& operator << (QDataStream &out, const GeneralSettings &g);
QDataStream& operator >> (QDataStream &in, GeneralSettings &g);

QDataStream& operator << (QDataStream &out, const InboundSettings &i);
QDataStream& operator >> (QDataStream &in, InboundSettings &i);

QDataStream& operator << (QDataStream &out, const OutboundSettings &o);
QDataStream& operator >> (QDataStream &in, OutboundSettings &o);

QDataStream& operator << (QDataStream &out, const TestSettings &t);
QDataStream& operator >> (QDataStream &in, TestSettings &t);

QDataStream& operator << (QDataStream &out, const SubscribeSettings &s);
QDataStream& operator >> (QDataStream &in, SubscribeSettings &s);

QDataStream& operator << (QDataStream &out, const GraphSettings &g);
QDataStream& operator >> (QDataStream &in, GraphSettings &g);

QDataStream& operator << (QDataStream &out, const RouterSettings &r);
QDataStream& operator >> (QDataStream &in, RouterSettings &r);

QDataStream& operator << (QDataStream &out, const CoreSettings &c);
QDataStream& operator >> (QDataStream &in, CoreSettings &c);

QDataStream& operator << (QDataStream &out, const CoreSettings &c);
QDataStream& operator >> (QDataStream &in, CoreSettings &c);

QDataStream& operator << (QDataStream &out, const TUNTAPSettings &t);
QDataStream& operator >> (QDataStream &in, TUNTAPSettings &t);

QDataStream& operator << (QDataStream &out, const STUNSettings &s);
QDataStream& operator >> (QDataStream &in, STUNSettings &s);

QDataStream& operator << (QDataStream &out, const ModeSettings &m);
QDataStream& operator >> (QDataStream &in, ModeSettings &m);

#endif // CONFIGSTRUCT_H

#ifndef RIOTAPI_H
#define RIOTAPI_H

#include <QObject>
#include <QNetworkAccessManager>

class RiotApi : public QObject {
    Q_OBJECT
public:
    explicit RiotApi(QObject *parent = nullptr);

    Q_INVOKABLE void search_summoner(
        const QString &sname,
        const QString &tag,
        const QString &apikey);
signals:
    void error_occurred(QString message);
    void found_puuid(QString puuid);
    void received_mastery(QString json_mastery);

private:
    QNetworkAccessManager *m_manager;
    void fetch_puuid(const QString &sname,
                     const QString &tag,
                     const QString &apikey);
    void fetch_mastery(const QString &puuid, const QString &apikey);
};

#endif // RIOTAPI_H

#ifndef RIOTAPI_H
#define RIOTAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtQml/qqml.h>

typedef std::map<int,std::pair<QString,QString>> Champions;

class RiotApi : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QList<QObject*> champions READ champions  NOTIFY championsChanged)

public:
    explicit RiotApi(QObject *parent = nullptr);
    Q_INVOKABLE void search_summoner(const QString &sname, const QString &tag, const QString &apikey);
    QList<QObject*> champions() const;
signals:
    void error_occurred(QString message);
    void found_puuid(QString puuid);
    void received_mastery(QVariantList champions);
    void championsChanged();
private:
    QNetworkAccessManager *m_manager;
    Champions championsMap;
    QList<QObject*> m_champions;
    void fetch_puuid(const QString &sname, const QString &tag, const QString &apikey);
    void fetch_mastery(const QString &puuid, const QString &apikey);
    void fetch_champion_data();
};

#endif // RIOTAPI_H

#include "riotapi.h"
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

RiotApi::RiotApi(QObject *parent) : QObject{parent} {
    m_manager = new QNetworkAccessManager(this);
}

void RiotApi::search_summoner(const QString &sname, const QString &tag, const QString &apikey) {
    qDebug() << "Suche nach " << sname << "#" << tag;
    fetch_puuid(sname, tag, apikey);
}

void RiotApi::fetch_puuid(const QString &sname, const QString &tag, const QString &apiKey) {
    QString urlStr = QString("https://europe.api.riotgames.com/riot/account/v1/accounts/by-riot-id/%1/%2")
    .arg(sname, tag);
    QUrl url(urlStr);
    QUrlQuery query;
    query.addQueryItem("api_key", apiKey);
    url.setQuery(query);

    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, apiKey]() {
        if (reply->error() != QNetworkReply::NoError) {
            emit error_occurred("PUUID Error: " + reply->errorString());
            reply->deleteLater();
            return;
        }

        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();
        QString puuid = obj["puuid"].toString();

        if (puuid.isEmpty()) {
            emit error_occurred("Keine PUUID gefunden!");
        } else {
            emit found_puuid(puuid);
            fetch_mastery(puuid, apiKey);
        }
        reply->deleteLater();
    });
}

void RiotApi::fetch_mastery(const QString &puuid, const QString &apiKey) {
    QString urlStr = QString("https://euw1.api.riotgames.com/lol/champion-mastery/v4/champion-masteries/by-puuid/%1")
    .arg(puuid);
    QUrl url(urlStr);
    QUrlQuery query;
    query.addQueryItem("api_key", apiKey);
    url.setQuery(query);

    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            emit error_occurred("Mastery Error: " + reply->errorString());
            reply->deleteLater();
            return;
        }
        emit received_mastery(QString::fromUtf8(reply->readAll()));
        reply->deleteLater();
    });
}

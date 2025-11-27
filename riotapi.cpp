#include "riotapi.h"
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

RiotApi::RiotApi(QObject *parent) : QObject{parent} {
    m_manager = new QNetworkAccessManager(this);
    fetch_champion_data();
}
QVariantList RiotApi::championsMap() const {
    return m_championsMap;
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

void RiotApi::fetch_champion_data(){
    QString urlStr = QString("https://ddragon.leagueoflegends.com/cdn/15.23.1/data/en_US/champion.json");
    QUrl url(urlStr);
    QUrlQuery query;
    url.setQuery(query);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            emit error_occurred("Champion data Error: " + reply->errorString());
            reply->deleteLater();
            return;
        }
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();
        QJsonObject cdata = obj["data"].toObject();
        for(QJsonValueRef champdata: cdata){
            QJsonObject champ = champdata.toObject();
            int key = champ["key"].toString().toInt();
            QString image = champ["image"].toObject()["full"].toString();
            QString name = champ["name"].toString();
            champions[key] = {name,image};
        }
        reply->deleteLater();
    });
}


void RiotApi::fetch_mastery(const QString &puuid, const QString &apiKey) {
    m_championsMap.clear();
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


        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray masteries = doc.array();

        QVariantMap entry;

        for(QJsonValueRef champ: masteries){
            QVariantMap entry;
            entry["name"] = champions[champ.toObject()["championId"].toInt()].first;
            entry["icon"] = champions[champ.toObject()["championId"].toInt()].second;
            m_championsMap.append(entry);
        }
        emit championsMapChanged();
        reply->deleteLater();
    });
}

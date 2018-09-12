/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016-2017 george99g
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QDISCORDREST_HPP
#define QDISCORDREST_HPP

#include "qdiscord.d/qdiscordbucket.hpp"
#include "qdiscord.d/qdiscordroute.hpp"
#include "qdiscord.d/qdiscordtoken.hpp"
#include "qdiscord.d/qdiscorduseragent.hpp"
#include <QBuffer>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QTimer>

class QDiscordRest : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDiscordToken token READ token WRITE setToken)
    Q_PROPERTY(
        QDiscordToken lastAckToken READ lastAckToken WRITE setLastAckToken)
    Q_PROPERTY(QDiscordUserAgent userAgent READ userAgent WRITE setUserAgent)
    Q_PROPERTY(QString discordBase READ discordBase WRITE setDiscordBase)

public:
    explicit QDiscordRest(QObject* parent = nullptr);
    ~QDiscordRest();

    QDiscordToken token() const { return _token; }
    void setToken(QDiscordToken token) { _token = token; }
    QDiscordToken lastAckToken() const { return _token; }
    void setLastAckToken(const QDiscordToken& lastAckToken);
    QDiscordUserAgent userAgent() const { return _userAgent; }
    void setUserAgent(const QDiscordUserAgent& userAgent)
    {
        _userAgent = userAgent;
    }
    QString discordBase() const { return _discordBase; }
    void setDiscordBase(const QString& discordBase)
    {
        _discordBase = discordBase;
    }

    template<class T>
    struct DataType
    {
        static constexpr bool isDataType = false;
        static QString type() { return ""; }
        static QByteArray extractData(const T& data)
        {
            static_assert(DataType<T>::isDataType,
                          "extractData called for non-data type");
            return "";
        }
    };

    template<class Functor>
    void
    request(const QNetworkRequest& request,
            const QDiscordRoute& route,
            Functor callback,
            typename std::enable_if<!DataType<Functor>::isDataType>::type* =
                nullptr)
    {
        QDiscordRest::request(request, route, QByteArray(), callback);
    }

    template<class Data, class Functor>
    void request(
        const QNetworkRequest& request,
        const QDiscordRoute& route,
        const Data& data,
        Functor callback,
        typename std::enable_if<DataType<Data>::isDataType>::type* = nullptr)
    {
        auto recallLambda = [request, route, data, callback, this]() {
            QDiscordRest::request(request, route, data, callback);
        };

        QSharedPointer<QDiscordBucket> bucket = getBucket(route.bucketUrl());

        if(bucket->remaining() <= 0)
        {
            bucket->enqueue(recallLambda);

            return;
        }

        bucket->setRemaining(bucket->remaining() - 1);
        bucket->setActiveRequests(bucket->activeRequests() + 1);

        qCDebug(REST, ) << "making request to" << route.fullUrl()
                        << "remaining requests:" << bucket->remaining()
                        << "active requests:" << bucket->activeRequests();

        QNetworkRequest r = request;
        r.setUrl(QUrl(_discordBase + route.fullUrl()));
        if(!_token.isEmpty())
            r.setRawHeader("Authorization", _token.fullToken().toUtf8());
        r.setHeader(QNetworkRequest::UserAgentHeader, _userAgent.toString());

        QNetworkReply* reply;
        switch(route.method())
        {
        case QDiscordRoute::Method::DELETE:
            reply = _manager.deleteResource(r);
            break;
        case QDiscordRoute::Method::GET:
            reply = _manager.get(r);
            break;
        case QDiscordRoute::Method::PATCH:
        {
            if(!DataType<Data>::type().isEmpty())
            {
                r.setHeader(QNetworkRequest::ContentTypeHeader,
                            DataType<Data>::type());
            }
            reply = _manager.sendCustomRequest(
                r, "PATCH", DataType<Data>::extractData(data));
        }
        break;
        case QDiscordRoute::Method::POST:
            if(!DataType<Data>::type().isEmpty())
            {
                r.setHeader(QNetworkRequest::ContentTypeHeader,
                            DataType<Data>::type());
            }
            reply = _manager.post(r, DataType<Data>::extractData(data));
            break;
        case QDiscordRoute::Method::PUT:
            if(!DataType<Data>::type().isEmpty())
            {
                r.setHeader(QNetworkRequest::ContentTypeHeader,
                            DataType<Data>::type());
            }
            reply = _manager.put(r, DataType<Data>::extractData(data));
            break;
        default:
            return;
        }
        connect(reply,
                &QNetworkReply::finished,
                this,
                [data, callback, reply, bucket, recallLambda, this]() {
                    bucket->setActiveRequests(bucket->activeRequests() - 1);

                    if(reply->rawHeader("X-RateLimit-Global").toLower()
                       == "true")
                    {
                        quint32 waitTime =
                            reply->rawHeader("Retry-After").toULong();

                        qCInfo(REST, ) << "global ratelimit hit, retrying in"
                                       << waitTime << "seconds";

                        QTimer::singleShot(waitTime * 1000, recallLambda);
                    }
                    else if(!bucket->processHeaders(reply))
                        bucket->enqueue(recallLambda);
                    else
                    {
                        processBuckets();
                        callback(reply);
                    }

                    reply->deleteLater();
                });
    }

    template<class Data>
    void request(
        const QNetworkRequest& request,
        const QDiscordRoute& route,
        Data data,
        typename std::enable_if<DataType<Data>::isDataType>::type* = nullptr)
    {
        QDiscordRest::request(request, route, data, [](QNetworkReply*) {});
    }

    void request(const QNetworkRequest& request, const QDiscordRoute& route);

private:
    QSharedPointer<QDiscordBucket> getBucket(const QString& route);

    void processBuckets();

    QTimer _bucketTimer;

    QMap<QString, QSharedPointer<QDiscordBucket>> _buckets;
    QNetworkAccessManager _manager;
    QDiscordToken _token;
    QDiscordToken _lastAckToken;
    QString _discordBase = "https://discordapp.com";
    QDiscordUserAgent _userAgent;
};

template<>
struct QDiscordRest::DataType<QJsonObject>
{
    static const bool isDataType = true;
    static QString type() { return "application/json"; }
    static QByteArray extractData(const QJsonObject& data)
    {
        return QJsonDocument(data).toJson(QJsonDocument::Compact);
    }
};

template<>
struct QDiscordRest::DataType<QJsonArray>
{
    static const bool isDataType = true;
    static QString type() { return "application/json"; };
    static QByteArray extractData(const QJsonArray& data)
    {
        return QJsonDocument(data).toJson(QJsonDocument::Compact);
    }
};

template<>
struct QDiscordRest::DataType<QByteArray>
{
    static const bool isDataType = true;
    static QString type() { return ""; };
    static QByteArray extractData(const QByteArray& data) { return data; }
};

template<>
struct QDiscordRest::DataType<QHttpMultiPart*>
{
    static const bool isDataType = true;
    static QString type() { return ""; };
    static QHttpMultiPart* extractData(QHttpMultiPart* data) { return data; }
};

#endif // QDISCORDREST_HPP

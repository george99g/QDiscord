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
public:
    explicit QDiscordRest(QObject* parent = nullptr);
    ~QDiscordRest();

    QDiscordToken token() const { return _token; }
    void setToken(QDiscordToken token) { _token = token; }
    QDiscordToken lastAckToken() const { return _token; }
    void setLastAckToken(QDiscordToken lastAckToken);
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

    // <spaghetti>

    template<class Functor>
    void request(const QNetworkRequest& request,
                 const QDiscordRoute& route,
                 Functor&& callback)
    {
        auto recallLambda = [request, route, callback, this]() {
            QDiscordRest::request(request, route, callback);
        };

        QSharedPointer<QDiscordBucket> bucket = getBucket(route.bucketUrl());

        if(bucket->remaining() <= 0)
        {
            bucket->enqueue(recallLambda);

            return;
        }

        bucket->setRemaining(bucket->remaining() - 1);
        bucket->setActiveRequests(bucket->activeRequests() + 1);

#ifdef QDISCORD_PRINT_DEBUG
        qDebug() << this << "making request to" << route.fullUrl();
        qDebug() << this << "remaining requests:" << bucket->remaining();
        qDebug() << this << "active requests:" << bucket->activeRequests();
#endif

        QNetworkRequest r = request;
        if(r.url().isEmpty())
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
            r.setHeader(QNetworkRequest::ContentLengthHeader, 0);
            reply = _manager.sendCustomRequest(r, "PATCH", QByteArray());
        }
        break;
        case QDiscordRoute::Method::POST:
            r.setHeader(QNetworkRequest::ContentLengthHeader, 0);
            reply = _manager.post(r, QByteArray());
            break;
        case QDiscordRoute::Method::PUT:
            r.setHeader(QNetworkRequest::ContentLengthHeader, 0);
            reply = _manager.put(r, QByteArray());
            break;
        default:
            return;
        }

        connect(reply,
                &QNetworkReply::finished,
                this,
                [callback, reply, bucket, recallLambda, this]() {
                    bucket->setActiveRequests(bucket->activeRequests() - 1);

                    if(reply->rawHeader("X-RateLimit-Global").toLower()
                       == "true")
                    {
                        quint32 waitTime =
                            reply->rawHeader("Retry-After").toULong();

#ifdef QDISCORD_PRINT_DEBUG
                        qDebug() << this << "global ratelimit hit, retrying in"
                                 << waitTime << "seconds";
#endif

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

    template<class Data, class Functor>
    void request(const QNetworkRequest& request,
                 const QDiscordRoute& route,
                 const Data& data,
                 Functor callback)
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

#ifdef QDISCORD_PRINT_DEBUG
        qDebug() << this << "making request to" << route.fullUrl();
        qDebug() << this << "remaining requests:" << bucket->remaining();
        qDebug() << this << "active requests:" << bucket->activeRequests();
#endif

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
            if(!contentType<Data>().type.isEmpty())
            {
                r.setHeader(QNetworkRequest::ContentTypeHeader,
                            contentType<Data>().type);
            }
            reply = _manager.sendCustomRequest(r, "PATCH", extractData(data));
        }
        break;
        case QDiscordRoute::Method::POST:
            if(!contentType<Data>().type.isEmpty())
            {
                r.setHeader(QNetworkRequest::ContentTypeHeader,
                            contentType<Data>().type);
            }
            reply = _manager.post(r, extractData(data));
            break;
        case QDiscordRoute::Method::PUT:
            if(!contentType<Data>().type.isEmpty())
            {
                r.setHeader(QNetworkRequest::ContentTypeHeader,
                            contentType<Data>().type);
            }
            reply = _manager.put(r, extractData(data));
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

#ifdef QDISCORD_PRINT_DEBUG
                        qDebug() << this << "global ratelimit hit, retrying in"
                                 << waitTime << "seconds";
#endif

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

    template<class Functor>
    void request(const QNetworkRequest& request,
                 const QDiscordRoute& route,
                 QHttpMultiPart* data,
                 Functor&& callback)
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

#ifdef QDISCORD_PRINT_DEBUG
        qDebug() << this << "making request to" << route.fullUrl();
        qDebug() << this << "remaining requests:" << bucket->remaining();
        qDebug() << this << "active requests:" << bucket->activeRequests();
#endif

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
            reply = _manager.sendCustomRequest(r, "PATCH", data);
        }
        break;
        case QDiscordRoute::Method::POST:
            reply = _manager.post(r, data);
            break;
        case QDiscordRoute::Method::PUT:
            reply = _manager.put(r, data);
            break;
        default:
            return;
        }
        connect(reply,
                &QNetworkReply::finished,
                this,
                [callback, reply, bucket, recallLambda, this]() {
                    bucket->setActiveRequests(bucket->activeRequests() - 1);

                    if(reply->rawHeader("X-RateLimit-Global").toLower()
                       == "true")
                    {
                        quint32 waitTime =
                            reply->rawHeader("Retry-After").toULong();

#ifdef QDISCORD_PRINT_DEBUG
                        qDebug() << this << "global ratelimit hit, retrying in"
                                 << waitTime << "seconds";
#endif

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

    void request(const QNetworkRequest& request,
                 const QDiscordRoute& route,
                 QHttpMultiPart* data);
    void request(const QNetworkRequest& request, const QDiscordRoute& route);

    // </spaghetti>

private:
    template<class T>
    struct contentType;

    QByteArray extractData(const QJsonObject& object) const;
    QByteArray extractData(const QJsonArray& array) const;
    QByteArray extractData(const QByteArray& array) const;

    QSharedPointer<QDiscordBucket> getBucket(QString route);

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
struct QDiscordRest::contentType<QJsonObject>
{
    const QString type = QStringLiteral("application/json");
};

template<>
struct QDiscordRest::contentType<QJsonArray>
{
    const QString type = QStringLiteral("application/json");
};

template<>
struct QDiscordRest::contentType<QByteArray>
{
    const QString type;
};

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           const QJsonObject& data);

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           const QJsonObject&& data);

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           QJsonObject& data);

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           QJsonObject&& data);

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           const QJsonArray& data);

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           const QJsonArray&& data);

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           QJsonArray& data);

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           QJsonArray&& data);

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           const QByteArray& data);

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           const QByteArray&& data);

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           QByteArray& data);

template<>
void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route,
                           QByteArray&& data);

#endif // QDISCORDREST_HPP

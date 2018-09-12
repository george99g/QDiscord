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

#include "qdiscord.d/qdiscordrest.hpp"

#define DEFAULT_TIMER_INTERVAL 60

QDiscordRest::QDiscordRest(QObject* parent)
    : QObject(parent)
    , _userAgent(QDiscordUserAgent::global())
{
    _bucketTimer.setInterval(DEFAULT_TIMER_INTERVAL * 1000);
    _bucketTimer.setSingleShot(false);
    connect(
        &_bucketTimer, &QTimer::timeout, this, &QDiscordRest::processBuckets);
    _bucketTimer.start();
}

QDiscordRest::~QDiscordRest()
{
    _bucketTimer.stop();
}

void QDiscordRest::setLastAckToken(const QDiscordToken& lastAckToken)
{
    qCDebug(REST, ) << "setting lastAckToken to" << lastAckToken.rawToken();
    _lastAckToken = lastAckToken;
}

void QDiscordRest::request(const QNetworkRequest& request,
                           const QDiscordRoute& route)
{
    QDiscordRest::request(request, route, [](QNetworkReply*) {});
}

QSharedPointer<QDiscordBucket> QDiscordRest::getBucket(const QString& route)
{
    if(!_buckets.contains(route))
    {
        _buckets.insert(route,
                        QSharedPointer<QDiscordBucket>(new QDiscordBucket()));

        qCDebug(REST, ) << "created bucket" << _buckets[route].data() << "for"
                        << route;
    }

    return _buckets[route];
}

void QDiscordRest::processBuckets()
{
    qCDebug(REST, ) << "processing buckets";

    // Process the buckets
    for(const QSharedPointer<QDiscordBucket>& bucket : _buckets)
        bucket->process();

    qCDebug(REST, ) << "finished processing buckets";

    // Set the timer interval for the next tick
    quint64 minResetTime = std::numeric_limits<quint64>::max();
    for(const QSharedPointer<QDiscordBucket>& bucket : _buckets)
    {
        if(bucket->reset() < minResetTime)
            minResetTime = bucket->reset();
    }

    quint64 currentTime = QDateTime::currentSecsSinceEpoch();
    quint64 resetInterval;
    if(minResetTime < currentTime)
        resetInterval = 0;
    else if(minResetTime - currentTime > DEFAULT_TIMER_INTERVAL)
        resetInterval = DEFAULT_TIMER_INTERVAL;
    else
        resetInterval = minResetTime - currentTime;
    _bucketTimer.start(resetInterval * 1000);

    qCDebug(REST, ) << "ticking again in" << _bucketTimer.interval() / 1000.
                    << "seconds";
}

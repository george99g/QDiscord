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

#include "qdiscordbucket.hpp"
#include <QDateTime>
#include <QNetworkReply>

QDiscordBucket::QDiscordBucket()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordBucket(" << this << ") constructed";
#endif
}

void QDiscordBucket::setActiveRequests(qint8 activeRequests)
{
    _activeRequests = activeRequests < 0 ? 0 : activeRequests;

#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "ac:" << _activeRequests;
#endif
}

void QDiscordBucket::process()
{
    processLimits();
    processQueue();
}

void QDiscordBucket::processLimits()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "handling limits: "
             << "rst:" << _reset << "c:"
             << static_cast<quint64>(QDateTime::currentSecsSinceEpoch());
#endif

    if(_reset <= static_cast<quint64>(QDateTime::currentSecsSinceEpoch()))
    {
        _remaining = _limit;
        _reset = std::numeric_limits<decltype(_reset)>::max();

#ifdef QDISCORD_LIBRARY_DEBUG
        qDebug() << this << "limits reset: "
                 << "l:" << _limit << "r:" << _remaining << "rst:" << _reset;
#endif
    }
}

void QDiscordBucket::processQueue()
{
    for(quint16 i = _remaining; i > 0; i--)
    {
        if(_queue.isEmpty())
            break;
        _queue.dequeue()();

#ifdef QDISCORD_LIBRARY_DEBUG
        qDebug() << this
                 << "request dequeued, remaining in queue:" << _queue.length();
#endif
    }
}

bool QDiscordBucket::processHeaders(QNetworkReply* reply)
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this << "parsing headers:" << reply->rawHeaderPairs();
#endif

    if(_activeRequests == 0)
    {
        if(reply->hasRawHeader("X-RateLimit-Limit"))
        {
            _limit = reply->rawHeader("X-RateLimit-Limit").toUInt();
            _remaining = reply->rawHeader("X-RateLimit-Remaining").toUInt();
            _reset = reply->rawHeader("X-RateLimit-Reset").toULongLong();
        }
        else
        {
            // Create a bucket that will basically allow you to send without
            // limits.
            _limit = std::numeric_limits<decltype(_limit)>::max();
            _remaining = std::numeric_limits<decltype(_remaining)>::max();
            _reset = static_cast<quint64>(QDateTime::currentSecsSinceEpoch());
        }

#ifdef QDISCORD_LIBRARY_DEBUG
        qDebug() << this << "limits reset:"
                 << "l:" << _limit << "r:" << _remaining << "rst:" << _reset;
#endif
    }

    processQueue();

#ifdef QDISCORD_LIBRARY_DEBUG
    if(reply->error() == 439)
        qDebug() << this << "RATELIMITED";
#endif

    return reply->error() != 439;
}

void QDiscordBucket::enqueue(const std::function<void()>& func)
{
    _queue.enqueue(func);

#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << this
             << "request enqueued, remaining in queue:" << _queue.length();
#endif
}

bool QDiscordBucket::hasQueued()
{
    return !_queue.isEmpty();
}

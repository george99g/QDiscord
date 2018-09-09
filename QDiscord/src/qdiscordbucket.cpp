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

#include "qdiscord.d/qdiscordbucket.hpp"
#include "qdiscord.d/qdiscordlogging.hpp"
#include <QDateTime>
#include <QNetworkReply>

void QDiscordBucket::setActiveRequests(qint8 activeRequests)
{
    _activeRequests = activeRequests < 0 ? 0 : activeRequests;

    qCDebug(REST, ) << this << "active requests:" << _activeRequests;
}

void QDiscordBucket::process()
{
    processLimits();
    processQueue();
}

void QDiscordBucket::processLimits()
{
    qCDebug(REST, ) << this << "handling limits:\n"
                    << "reset:" << _reset << "current:"
                    << static_cast<quint64>(QDateTime::currentSecsSinceEpoch());

    if(_reset <= static_cast<quint64>(QDateTime::currentSecsSinceEpoch()))
    {
        _remaining = _limit;
        _reset = std::numeric_limits<decltype(_reset)>::max();

        qCDebug(REST, ) << this << "limits reset:\n"
                        << "limit:" << _limit << "remaining:" << _remaining
                        << "reset:" << _reset;
    }
}

void QDiscordBucket::processQueue()
{
    for(quint16 i = _remaining; i > 0; i--)
    {
        if(_queue.isEmpty())
            break;
        _queue.dequeue()();

        qCDebug(REST, ) << this << "request dequeued, remaining in queue:"
                        << _queue.length();
    }
}

bool QDiscordBucket::processHeaders(QNetworkReply* reply)
{
    qCDebug(REST, ) << this << "parsing headers:" << reply->rawHeaderPairs();

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

        qCDebug(REST, ) << this << "limits reset:\n"
                        << "limit:" << _limit << "remaining:" << _remaining
                        << "reset:" << _reset;
    }

    processQueue();

    if(reply->error() == 439)
        qCWarning(REST, ) << this << "RATELIMITED";

    return reply->error() != 439;
}

void QDiscordBucket::enqueue(const std::function<void()>& func)
{
    _queue.enqueue(func);

    qCDebug(REST, ) << this << "request dequeued, remaining in queue:"
                    << _queue.length();
}

bool QDiscordBucket::hasQueued()
{
    return !_queue.isEmpty();
}

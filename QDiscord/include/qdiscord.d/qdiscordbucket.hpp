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

#ifndef QDISCORDBUCKET_HPP
#define QDISCORDBUCKET_HPP

#include <QMetaType>
#include <QQueue>
#include <functional>
#include <numeric>

class QNetworkReply;

class QDiscordBucket
{
public:
    QDiscordBucket();
    quint16 limit() const { return _limit; }
    void setLimit(quint16 limit) { _limit = limit; }
    quint16 remaining() const { return _remaining; }
    void setRemaining(quint16 remaining) { _remaining = remaining; }
    quint64 reset() const { return _reset; }
    void setReset(quint64 reset) { _reset = reset; }
    qint8 activeRequests() const { return _activeRequests; }
    void setActiveRequests(qint8 activeRequests);
    void process();
    void processLimits();
    void processQueue();
    bool processHeaders(QNetworkReply* reply);
    void enqueue(const std::function<void()>& func);
    bool hasQueued();

private:
    quint16 _limit = 1;
    quint16 _remaining = 1;
    quint64 _reset = std::numeric_limits<quint64>::max();
    qint8 _activeRequests = 0;
    QQueue<std::function<void()>> _queue;
};

Q_DECLARE_METATYPE(QDiscordBucket)

#endif // QDISCORDBUCKET_HPP

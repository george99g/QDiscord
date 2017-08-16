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

#include "qdiscordrest.hpp"

#define DEFAULT_TIMER_INTERVAL 60

QDiscordRest::QDiscordRest(QObject* parent)
: QObject(parent)
{
	_bucketTimer.setInterval(DEFAULT_TIMER_INTERVAL * 1000);
	_bucketTimer.setSingleShot(false);
	connect(&_bucketTimer, &QTimer::timeout,
			this, &QDiscordRest::processBuckets);
	_bucketTimer.start();
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"constructed";
#endif
}

QDiscordRest::~QDiscordRest()
{
	_bucketTimer.stop();
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"destroyed";
#endif
}

void QDiscordRest::request(const QNetworkRequest& request,
						   const QDiscordRoute& route,
						   const QJsonObject& data)
{
	QDiscordRest::request(request, route, data, [](QNetworkReply*){});
}

void QDiscordRest::request(const QNetworkRequest& request,
						   const QDiscordRoute& route,
						   const QJsonArray& data)
{
	QDiscordRest::request(request, route, data, [](QNetworkReply*){});
}

void QDiscordRest::request(const QNetworkRequest& request,
						   const QDiscordRoute& route,
						   const QByteArray& data)
{
	QDiscordRest::request(request, route, data, [](QNetworkReply*){});
}

void QDiscordRest::request(const QNetworkRequest& request,
						   const QDiscordRoute& route,
						   QHttpMultiPart* data)
{
	QDiscordRest::request(request, route, data, [](QNetworkReply*){});
}

void QDiscordRest::request(const QNetworkRequest& request,
						   const QDiscordRoute& route)
{
	QDiscordRest::request(request, route, [](QNetworkReply*){});
}

QByteArray QDiscordRest::extractData(const QJsonObject& object) const
{
	return QJsonDocument(object).toJson(QJsonDocument::Compact);
}

QByteArray QDiscordRest::extractData(const QJsonArray& array) const
{
	return QJsonDocument(array).toJson(QJsonDocument::Compact);
}

QByteArray QDiscordRest::extractData(const QByteArray& array) const
{
	return array;
}

QSharedPointer<QDiscordBucket> QDiscordRest::getBucket(QString route)
{
	if(!_buckets.keys().contains(route))
	{
		_buckets.insert(
					route,
					QSharedPointer<QDiscordBucket>(new QDiscordBucket())
				);

#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this<<"created bucket"<<_buckets[route].data()
				  <<"for"<<route;
#endif
	}

	return _buckets[route];
}

void QDiscordRest::processBuckets()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"processing buckets";
#endif

	// Process the buckets
	for(const QSharedPointer<QDiscordBucket>& bucket : _buckets.values())
		bucket->process();
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"finished processing buckets";
#endif

	// Set the timer interval for the next tick
	quint64 minResetTime = std::numeric_limits<quint64>::max();
	for(const QSharedPointer<QDiscordBucket>& bucket : _buckets.values())
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
	_bucketTimer.start(resetInterval*1000);
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"ticking again in"
		   <<_bucketTimer.interval()/1000.<<"seconds";
#endif
}

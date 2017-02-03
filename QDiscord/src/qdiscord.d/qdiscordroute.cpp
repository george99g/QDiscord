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

#include "qdiscordroute.hpp"

QDiscordRoute::QDiscordRoute(Method method, QString url)
{
	route(method, url);
}

QDiscordRoute::Method QDiscordRoute::method()
{
	return _method;
}

QString QDiscordRoute::bucketUrl()
{
	return _bucketUrl;
}

QString QDiscordRoute::fullUrl()
{
	return _fullUrl;
}

QString QDiscordRoute::routeString(QString url)
{
	return url;
}

void QDiscordRoute::route(QDiscordRoute::Method method, QString url)
{
	_method = method;
	_fullUrl = url;
	_bucketUrl = url;
}

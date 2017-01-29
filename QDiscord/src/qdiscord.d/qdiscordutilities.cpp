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

#include "qdiscordutilities.hpp"

const qlonglong QDiscordUtilities::discordEpoch = 1420070400000;

#ifdef QDISCORD_BOT_NAME
const QString QDiscordUtilities::botName = QDISCORD_BOT_NAME;
#else
const QString QDiscordUtilities::botName = "QDiscordBot";
#endif
#ifdef QDISCORD_LIBRARY_NAME
const QString QDiscordUtilities::libName = QDISCORD_LIBRARY_NAME;
#else
const QString QDiscordUtilities::libName = "QDiscord";
#endif
#ifdef QDISCORD_LIBRARY_LINK
const QString QDiscordUtilities::libLink = QDISCORD_LIBRARY_LINK;
#else
const QString QDiscordUtilities::libLink = "https://github.com/george99g/QDiscord";
#endif
#ifdef QDISCORD_LIBRARY_MAJOR
const QString QDiscordUtilities::libMajor = QDISCORD_LIBRARY_MAJOR;
#else
const QString QDiscordUtilities::libMajor = "0";
#endif
#ifdef QDISCORD_LIBRARY_MINOR
const QString QDiscordUtilities::libMinor = QDISCORD_LIBRARY_MINOR;
#else
const QString QDiscordUtilities::libMinor = "8";
#endif
#ifdef QDISCORD_DISCORD_API_VERSION
const QString QDiscordUtilities::apiVersion = QDISCORD_DISCORD_API_VERSION;
#else
const QString QDiscordUtilities::apiVersion = "6";
#endif

const QDiscordUtilities::EndPoints QDiscordUtilities::endPoints =
[]() -> QDiscordUtilities::EndPoints {
	QDiscordUtilities::EndPoints init;
	init.base = "https://discordapp.com";
	init.apiBase = init.base + "/api/v" + QDiscordUtilities::apiVersion;
	init.gateway =
		init.apiBase +
		"/gateway?encoding=json&v=" +
		QDiscordUtilities::apiVersion;
	init.users = init.apiBase + "/users";
	init.me = init.users + "/@me";
	init.auth = init.apiBase + "/auth";
	init.register_ = init.auth + "/register";
	init.login = init.auth + "/login";
	init.logout = init.auth + "/logout";
	init.servers = init.apiBase + "/guilds";
	init.channels = init.apiBase + "/channels";
	return init;
}();

QString QDiscordUtilities::networkErrorToString(QNetworkReply::NetworkError error)
{
	switch((int)error)
	{
	case 200:
		return "200 (OK): The response completed sucessfully.";
	case 201:
		return "200 (CREATED): The entity was created successfully.";
	case 304:
		return "304 (NOT MODIFIED): The entity was not modified (no action was taken).";
	case 400:
		return "400 (BAD REQUEST): The request was improperly formatted, or the server couldn't understand it.";
	case 401:
		return "401 (UNAUTHORIZED): The Authorization header was missing or invalid.";
	case 403:
		return "403 (FORBIDDEN): The Authorization token you passed did not have permission to the resource";
	case 404:
		return "404 (NOT FOUND): The resource at the location specified doesn't exist.";
	case 405:
		return "405 (METHOD NOT ALLOWED): The HTTP method used is not valid for the location specified.";
	case 429:
		return "429 (TOO MANY REQUESTS): You've made too many requests.";
	case 502:
		return "502 (GATEWAY UNAVAILABLE): There was not a gateway available to process your request. Wait a bit and retry.";
	default:
		if((int)error > 499 && (int)error < 600)
			return "5xx (SERVER ERROR): The server had an error processing your request.";
		else return "xxx (UNKNOWN): Unknown error.";
	}
}

QDateTime QDiscordUtilities::snowflakeTime(QString snowflake)
{
#if QT_VERSION_MAJOR >= 5 && QT_VERSION_MINOR >= 8
	return QDateTime::fromSecsSinceEpoch(
					((snowflake.toLongLong() >> 22) + discordEpoch) / 1000
				);
#else
	return QDateTime::fromTime_t(
					((snowflake.toLongLong() >> 22) + discordEpoch) / 1000
				);
#endif
}

QString QDiscordUtilities::convertTokenToType(QString token,
											  QDiscordTokenType tokenType)
{
	switch(tokenType)
	{
	case QDiscordTokenType::Bot:
		return "Bot " + token;
	case QDiscordTokenType::Bearer:
		return "Bearer " + token;
	default:
		return token;
	}
}

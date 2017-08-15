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

#include "qdiscorduseragent.hpp"
#include "qdiscordutilities.hpp"

QDiscordUserAgent::QDiscordUserAgent()
{

}

const QDiscordUserAgent& QDiscordUserAgent::global()
{
	static QDiscordUserAgent instance = makeGlobalInstance();
	return instance;
}

QString QDiscordUserAgent::toString() const
{
	return QString("DiscordBot (%1, v%2:%3); %4")
			.arg(_libraryLink)
			.arg(_libraryVersion.majorVersion)
			.arg(_libraryVersion.minorVersion)
			.arg(_botName);
}

QDiscordUserAgent QDiscordUserAgent::makeGlobalInstance()
{
	QDiscordUserAgent instance;
	instance._libraryLink = QDiscordUtilities::libLink;
	QDiscordLibraryVersion version;
	version.majorVersion = QDiscordUtilities::libMajor.toUInt();
	version.minorVersion = QDiscordUtilities::libMinor.toUInt();
	instance._libraryVersion = version;
	instance._botName = QDiscordUtilities::botName;
	instance._libraryName = QDiscordUtilities::libName;
	return instance;
}

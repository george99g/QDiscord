/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016 george99g
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

#include "qdiscordmessage.hpp"

QDiscordMessage::QDiscordMessage(const QJsonObject& object, QDiscordChannel* channel)
{
	_id = object["id"].toString("");
	_mentionEveryone = object["mention_everyone"].toBool(false);
	_content = object["content"].toString("");
	_author = nullptr;
	_channel = channel;
	_channelId = object["channel_id"].toString("");
	if(object.contains("author"))
		_author = new QDiscordUser(object["author"].toObject());
	_tts = object["tts"].toBool(false);
	_timestamp = QDateTime::fromString(object["timestamp"].toString(""), Qt::ISODate);;

	for(auto mention : object["mentions"].toArray())
		_mentions << new QDiscordUser(mention.toObject());

	if(QDiscordUtilities::debugMode)
		qDebug()<<"QDiscordMessage("<<this<<") constructed";
}

QDiscordMessage::QDiscordMessage()
{
	_id = "";
	_mentionEveryone = false;
	_content = "";
	_author = nullptr;
	_channel = nullptr;
	_channelId = "";
	_tts = false;
	_timestamp = QDateTime();

	if(QDiscordUtilities::debugMode)
		qDebug()<<"QDiscordMessage("<<this<<") constructed";
}

QDiscordMessage::QDiscordMessage(const QDiscordMessage& other)
{
	_id = other.id();
	_mentionEveryone = other.mentionEveryone();
	_content = other.content();
	if(other.author())
		_author = new QDiscordUser(*other.author());
	else
		_author = nullptr;
	_channel = other.channel();
	_channelId = other.channelId();
	_tts = other.tts();
	_timestamp = other.timestamp();
	_mentions = other.mentions();
}

QDiscordMessage::~QDiscordMessage()
{
	if(_author)
		delete _author;
}

QDiscordGuild*QDiscordMessage::guild() const
{
	if(_channel)
		return _channel->guild();
	else
		return nullptr;
}

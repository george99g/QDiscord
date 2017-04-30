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

#include "qdiscordmessage.hpp"

QSharedPointer<QDiscordMessage> QDiscordMessage::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordMessage> message(new QDiscordMessage());
	message->deserialize(object);
	return message;
}

QDiscordMessage::QDiscordMessage(const QJsonObject& object)
{
	deserialize(object);

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordMessage("<<this<<") constructed";
#endif
}

QDiscordMessage::QDiscordMessage()
{
	_mentionEveryone = false;
	_tts = false;
	_pinned = false;

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordMessage("<<this<<") constructed";
#endif
}

QDiscordMessage::~QDiscordMessage()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordMessage("<<this<<") destroyed";
#endif
}

void QDiscordMessage::deserialize(const QJsonObject& object)
{
	_id = QDiscordID(object["id"].toString());
	_channelId = QDiscordID(object["channel_id"].toString());
	_author = QDiscordUser(object["author"].toObject());
	_content = object["content"].toString();
	_timestamp = QDateTime::fromString(object["timestamp"].toString(),
			Qt::ISODateWithMs);
	if(!object["edited_timestamp"].isNull())
	{
		_editedTimestamp =
				QDateTime::fromString(object["edited_timestamp"].toString(),
										Qt::ISODateWithMs);
	}
	_tts = object["tts"].toBool(false);
	_mentionEveryone = object["mention_everyone"].toBool(false);
	_nonce = QDiscordID(object["nonce"].toString());
	QJsonArray mentionsArray = object["mentions"].toArray();
	for(const QJsonValue item : mentionsArray)
	{
		_mentions.append(QDiscordUser(item.toObject()));
	}
	_pinned = object["pinned"].toBool(false);
	/* The channel pointer is handled by the calling class */
}

QJsonObject QDiscordMessage::serialize()
{
	QJsonObject object;

	object["id"] = _id.toString();
	object["channel_id"] = _channelId.toString();
	object["author"] = _author.serialize();
	object["content"] = _content;
	{
		object["timestamp"] = _timestamp.toTimeSpec(Qt::OffsetFromUTC)
										.toString(Qt::ISODateWithMs);
	}
	if(_editedTimestamp.has_value())
	{
		object["edited_timestamp"] =
				_editedTimestamp.value()
								.toTimeSpec(Qt::OffsetFromUTC)
								.toString(Qt::ISODateWithMs);
	}
	else
		object["edited_timestamp"] = QJsonValue();
	object["tts"] = _tts;
	object["mention_everyone"] = _mentionEveryone;
	QJsonArray mentions;
	for(const QDiscordUser& u : _mentions)
	{
		mentions.append(u.serialize());
	}
	object["mentions"] = mentions;
	object["nonce"] = _nonce.toString();
	object["pinned"] = _pinned;

	return object;
}

QSharedPointer<QDiscordGuild> QDiscordMessage::guild() const
{
	return _channel ? _channel->guild() : QSharedPointer<QDiscordGuild>();
}

bool QDiscordMessage::operator ==(const QDiscordMessage& other) const
{
	if(isNull() || other.isNull())
		return false;
	return _id == other._id;
}

bool QDiscordMessage::operator !=(const QDiscordMessage& other) const
{
	return !operator==(other);
}

bool QDiscordMessage::operator >(const QDiscordMessage& other) const
{
	return _id > other._id;
}

bool QDiscordMessage::operator <(const QDiscordMessage& other) const
{
	return _id < other._id;
}

bool QDiscordMessage::operator <=(const QDiscordMessage& other) const
{
	return _id <= other._id;
}

bool QDiscordMessage::operator >=(const QDiscordMessage& other) const
{
	return _id >= other._id;
}

QDiscordMessage::operator bool() const
{
	return _id;
}

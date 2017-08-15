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

#include "qdiscordguild.hpp"
#include "qdiscordchannel.hpp"

QSharedPointer<QDiscordChannel>
QDiscordChannel::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordChannel> channel(new QDiscordChannel());
	channel->deserialize(object);
	return channel;
}

QDiscordChannel::QDiscordChannel(const QJsonObject& object)
{
	deserialize(object);
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordChannel("<<this<<") constructed";
#endif
}

QDiscordChannel::QDiscordChannel()
{
	_isPrivate = false;
	_position = -1;
	_type = ChannelType::UnknownType;
	_bitrate = -1;
	_userLimit = -1;
	_rest = nullptr;

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordChannel("<<this<<") constructed";
#endif
}

QDiscordChannel::~QDiscordChannel()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordChannel("<<this<<") destroyed";
#endif
}

void QDiscordChannel::deserialize(const QJsonObject& object)
{
	_id = QDiscordID(object["id"].toString());
	{
		QString type = object["type"].toString();
		if(type == "text")
			_type = ChannelType::Text;
		else if(type == "voice")
			_type = ChannelType::Voice;
		else
			_type = ChannelType::UnknownType;
	}
	_isPrivate = object["is_private"].toBool(false);
	if(_isPrivate)
	{
		_recipient = QSharedPointer<QDiscordUser>(
					new QDiscordUser(object["recipient"].toObject())
				);
		if(!object["last_message_id"].isNull())
			_lastMessageId = QDiscordID(object["last_message_id"].toString());
		return;
	}
	if(_type == ChannelType::Text || _type == ChannelType::Voice)
	{
		_guildId = QDiscordID(object["guild_id"].toString());
		_name = object["name"].toString();
		_position = object["position"].toInt(-1);
	}
	if(_type == ChannelType::Text)
	{
		_topic = object["topic"].toString();
		if(!object["last_message_id"].isNull())
			_lastMessageId = QDiscordID(object["last_message_id"].toString());
	}
	else if(_type == ChannelType::Voice)
	{
		_bitrate = object["bitrate"].toInt(-1);
		_userLimit = object["user_limit"].toInt(-1);
	}
}

QJsonObject QDiscordChannel::serialize() const
{
	QJsonObject object;

	object["id"] = _id.toString();
	object["is_private"] = _isPrivate;
	if(_isPrivate)
	{
		if(_recipient)
		{
			QJsonObject user = _recipient->serialize();
			if(user["mfa_enabled"].toBool(false) == false)
				user.remove("mfa_enabled");
			if(user["bot"].toBool(false) == false)
				user.remove("bot");
			object["recipient"] = user;
		}
		else
			object["recipient"] = QJsonValue();
		object["last_message_id"] =
				_lastMessageId?_lastMessageId.toString():QJsonValue();
		object["type"] = "text";
	}
	else
	{
		object["name"] = _name;
		object["position"] = _position;
		if(_type == ChannelType::Text)
		{
			object["type"] = QString("text");
			object["topic"] = _topic;
			object["last_message_id"] =
					_lastMessageId?_lastMessageId.toString():QJsonValue();
		}
		else if(_type == ChannelType::Voice)
		{
			object["type"] = QString("voice");
			object["bitrate"] = _bitrate;
			object["user_limit"] = _userLimit;
		}
	}

	return object;
}

bool QDiscordChannel::operator ==(const QDiscordChannel& other) const
{
	return _id == other._id;
}

bool QDiscordChannel::operator !=(const QDiscordChannel& other) const
{
	return !operator ==(other);
}

bool QDiscordChannel::operator >(const QDiscordChannel& other) const
{
	return _id > other._id;
}

bool QDiscordChannel::operator <(const QDiscordChannel& other) const
{
	return _id < other._id;
}

bool QDiscordChannel::operator <=(const QDiscordChannel& other) const
{
	return _id <= other._id;
}

bool QDiscordChannel::operator >=(const QDiscordChannel& other) const
{
	return _id >= other._id;
}

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

QDiscordChannel::QDiscordChannel(const QJsonObject& object,
								 QWeakPointer<QDiscordGuild> guild)
{
	_id = QDiscordID(object["id"].toString(""));
	_isPrivate = object["is_private"].toBool(false);
	_lastMessageId = QDiscordID(object["last_message_id"].toString(""));
	_name = object["name"].toString("");
	_position = object["position"].toInt(-1);
	_topic = object["topic"].toString("");
	QString type = object["type"].toString("");
	_bitrate = -1;
	_userLimit = -1;
	_lastPinTimestamp = QDateTime();
	if(type == "text")
	{
		_type = ChannelType::Text;
		_lastPinTimestamp = QDateTime::fromString(
					object["last_pin_timestamp"].toString(""),
					Qt::ISODate
				);
	}
	else if(type == "voice")
	{
		_type = ChannelType::Voice;
		_bitrate = object["bitrate"].toInt(-1);
		_userLimit = object["user_limit"].toInt(-1);
	}
	else
		_type = ChannelType::UnknownType;
	_guild = guild;
	if(_isPrivate)
	{
		_recipient = QSharedPointer<QDiscordUser>(
					new QDiscordUser(object["recipient"].toObject())
				);
	}
	else
		_recipient = QSharedPointer<QDiscordUser>();

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordChannel("<<this<<") constructed";
#endif
}

QDiscordChannel::QDiscordChannel()
{
	_isPrivate = false;
	_name = "";
	_position = 0;
	_topic = "";
	_type = ChannelType::UnknownType;
	_guild = QWeakPointer<QDiscordGuild>();
	_recipient = QSharedPointer<QDiscordUser>();
	_bitrate = -1;
	_userLimit = -1;

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordChannel("<<this<<") constructed";
#endif
}

QDiscordChannel::QDiscordChannel(const QDiscordChannel& other)
{
	_id = other.id();
	_isPrivate = other.isPrivate();
	_lastMessageId = other.lastMessageId();
	_name = other.name();
	_position = other.position();
	_topic = other.topic();
	_type = other.type();
	_guild = other.guild();
	_recipient = other.recipient();
	_bitrate = other.bitrate();
	_userLimit = other.userLimit();
}

QDiscordChannel::~QDiscordChannel()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordChannel("<<this<<") destroyed";
#endif
	_recipient.clear();
}

bool QDiscordChannel::operator ==(const QDiscordChannel& other) const
{
	return _id == other._id;
}

bool QDiscordChannel::operator !=(const QDiscordChannel& other) const
{
	return !operator ==(other);
}

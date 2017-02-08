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

#include "qdiscordchannel.hpp"
#include "qdiscordguild.hpp"

QDiscordGuild::QDiscordGuild(const QJsonObject& object)
{
	_id = QDiscordID(object["id"].toString(""));
	_unavailable = object["unavailable"].toBool(false);
	_name = object["name"].toString("");
	_verificationLevel = object["verification_level"].toInt(0);
	_afkTimeout = object["afk_timeout"].toInt(0);
	_memberCount = object["member_count"].toInt(1);
	_joinedAt = QDateTime::fromString(object["joined_at"].toString(""),
			Qt::ISODate);
	for(QJsonValue item : object["members"].toArray())
	{
		QSharedPointer<QDiscordMember> member =
				QSharedPointer<QDiscordMember>(
						new QDiscordMember(item.toObject(), sharedFromThis())
					);
		_members.insert(member->user()->id(), member);
	}
	for(QJsonValue item : object["channels"].toArray())
	{
		QSharedPointer<QDiscordChannel> channel =
				QSharedPointer<QDiscordChannel>(
						new QDiscordChannel(item.toObject(), sharedFromThis())
					);
		_channels.insert(channel->id(), channel);
	}

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordGuild("<<this<<") constructed";
#endif
}

QDiscordGuild::QDiscordGuild(const QDiscordGuild& other):
	QEnableSharedFromThis<QDiscordGuild>()
{
	_id = other.id();
	_unavailable = other.unavailable();
	_name = other.name();
	_verificationLevel = other.verificationLevel();
	_afkTimeout = other.afkTimeout();
	_memberCount = other.memberCount();
	_joinedAt = other.joinedAt();
	for(QSharedPointer<QDiscordChannel> item : other.channels())
	{
		QSharedPointer<QDiscordChannel> newChannel =
				QSharedPointer<QDiscordChannel>(
						new QDiscordChannel(*item)
					);
		newChannel->setGuild(sharedFromThis());
		_channels.insert(other.channels().key(item), newChannel);
	}
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordGuild("<<this<<") copy-constructed";
#endif
}

QDiscordGuild::QDiscordGuild()
{
	_unavailable = false;
	_name = "";
	_verificationLevel = 0;
	_afkTimeout = 0;
	_memberCount = 0;
	_joinedAt = QDateTime();

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordGuild("<<this<<") constructed";
#endif
}

QDiscordGuild::~QDiscordGuild()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordGuild("<<this<<") destroyed";
#endif
}

void QDiscordGuild::addChannel(QSharedPointer<QDiscordChannel> channel)
{
	if(!channel)
		return;
	 _channels.insert(channel->id(), channel);
}

bool QDiscordGuild::removeChannel(QSharedPointer<QDiscordChannel> channel)
{
	if(!channel)
		return false;
	if(!_channels.keys().contains(channel->id()))
		return false;
	_channels.remove(channel->id());
	return true;
}

void QDiscordGuild::addMember(QSharedPointer<QDiscordMember> member)
{
	if(!member)
		return;
	_members.insert(member->user()->id(), member);
}

bool QDiscordGuild::removeMember(QSharedPointer<QDiscordMember> member)
{
	if(!member)
		return false;
	if(!_members.keys().contains(member->user()->id()))
		return false;
	_members.remove(member->user()->id());
	return true;
}

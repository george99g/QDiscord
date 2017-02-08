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

#include "qdiscordmember.hpp"
#include "qdiscordguild.hpp"

QDiscordMember::QDiscordMember(const QJsonObject& object,
							   QWeakPointer<QDiscordGuild> guild)
{
	_deaf = object["deaf"].toBool(false);
	_mute = object["mute"].toBool(false);
	_nickname = object["nick"].toString("");
	_joinedAt = QDateTime::fromString(object["joined_at"].toString(""),
			Qt::ISODate);
	_guild = guild;
	if(object["user"].isObject())
	{
		_user = QSharedPointer<QDiscordUser>(
					new QDiscordUser(object["user"].toObject())
				);
	}
	else
		_user = QSharedPointer<QDiscordUser>();

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordMember("<<this<<") constructed";
#endif
}

QDiscordMember::QDiscordMember()
{
	_deaf = false;
	_mute = false;
	_nickname = "";
	_joinedAt = QDateTime();
	_user = QSharedPointer<QDiscordUser>();
	_guild = QWeakPointer<QDiscordGuild>();

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordMember("<<this<<") constructed";
#endif
}

QDiscordMember::QDiscordMember(const QDiscordMember& other)
{
	_deaf = other.deaf();
	_mute = other.mute();
	_joinedAt = other.joinedAt();
	if(other.user())
		_user = QSharedPointer<QDiscordUser>(new QDiscordUser(*other.user()));
	else
		_user = QSharedPointer<QDiscordUser>();
	_guild = other.guild();
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordMember("<<this<<") copy-constructed";
#endif
}

QDiscordMember::~QDiscordMember()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordMember("<<this<<") destroyed";
#endif
}

void QDiscordMember::update(const QJsonObject& object,
							QWeakPointer<QDiscordGuild> guild)
{
	if(object.contains("deaf"))
		_deaf = object["deaf"].toBool(false);
	if(object.contains("mute"))
		_mute = object["mute"].toBool(false);
	if(object.contains("nick"))
		_nickname = object["nick"].toString("");
	if(object.contains("joined_at"))
	{
		_joinedAt = QDateTime::fromString(object["joined_at"].toString(""),
				Qt::ISODate);
	}
	if(guild)
		_guild = guild;
	if(_user)
		_user->update(object["user"].toObject());

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordMember("<<this<<") updated";
#endif
}

QString QDiscordMember::mentionUsername() const
{
	return QString("<@"+(_user?_user->id().toString():"nullptr")+">");
}

QString QDiscordMember::mentionNickname() const
{
	return QString("<@!"+(_user?_user->id().toString():"nullptr")+">");
}

bool QDiscordMember::operator ==(const QDiscordMember& other) const
{
	QSharedPointer<QDiscordGuild> strongGuild = _guild.toStrongRef();
	if(!_user)
		return false;
	if(!other.user())
		return false;
	if(!strongGuild)
		return false;
	if(!other.guild())
		return false;
	if(*_user == *other.user() &&
			strongGuild->id() == other.guild()->id())
	{
		return true;
	}
	return false;
}

bool QDiscordMember::operator !=(const QDiscordMember& other) const
{
	return !operator ==(other);
}

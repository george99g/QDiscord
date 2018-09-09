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

#include "qdiscord.d/models/qdiscordmember.hpp"
#include "qdiscord.d/models/qdiscordguild.hpp"

QSharedPointer<QDiscordMember>
QDiscordMember::fromJson(const QJsonObject& object)
{
    QSharedPointer<QDiscordMember> member(new QDiscordMember());
    member->deserialize(object);
    return member;
}

QDiscordMember::QDiscordMember(const QJsonObject& object)
{
    deserialize(object);
}

void QDiscordMember::deserialize(const QJsonObject& object)
{
    deserializeJson(object);

    /* The guild pointer is managed by the calling class. */
}

QJsonObject QDiscordMember::serialize() const
{
    return serializeJson();
}

void QDiscordMember::update(const QDiscordMember& other)
{
    _user.update(other.constUser());
    _nickname = other.nickname();
    if(other.joinedAt().isValid())
        _joinedAt = other.joinedAt();
    if(other.deaf().has_value())
        _deaf = other.deaf();
    if(other.mute().has_value())
        _mute = other.mute();
}

QString QDiscordMember::mentionUsername() const
{
    return _user.mention();
}

QString QDiscordMember::mentionNickname() const
{
    return QString("<@!%1>").arg(_user.id() ? _user.id().toString() :
                                              "invalid ID");
}

void QDiscordMember::setRest(QDiscordRest* rest)
{
    _user.setRest(rest);
}

bool QDiscordMember::operator==(const QDiscordMember& other) const
{
    QSharedPointer<QDiscordGuild> strongGuild = _guild.toStrongRef();
    if(!strongGuild)
        return false;
    if(!other.guild())
        return false;
    return _user == other._user && strongGuild->id() == other.guild()->id();
}

bool QDiscordMember::operator!=(const QDiscordMember& other) const
{
    return !operator==(other);
}

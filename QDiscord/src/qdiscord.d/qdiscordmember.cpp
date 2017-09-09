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

#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordMember(" << this << ") constructed";
#endif
}

QDiscordMember::QDiscordMember()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordMember(" << this << ") constructed";
#endif
}

QDiscordMember::~QDiscordMember()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordMember(" << this << ") destroyed";
#endif
}

void QDiscordMember::deserialize(const QJsonObject& object)
{
    _user = QDiscordUser(object["user"].toObject());
    if(object.contains("nick"))
    {
        if(!object["nick"].isNull())
            _nickname = object["nick"].toString();
    }
    _joinedAt = QDateTime::fromString(object["joined_at"].toString(),
                                      Qt::ISODateWithMs);
    if(object.contains("deaf"))
        _deaf = object["deaf"].toBool(false);
    if(object.contains("mute"))
        _mute = object["mute"].toBool(false);
    /* The guild pointer is managed by the calling class. */
}

QJsonObject QDiscordMember::serialize() const
{
    QJsonObject object;

    {
        // Apparently the `bot` and `mfa_enabled` fields should be removed if
        // they're false, but only when in a member's `user` field.
        // Why? I have not a clue, but I'll go with it.
        QJsonObject user = _user.serialize();

        if(user["mfa_enabled"].toBool(false) == false)
            user.remove("mfa_enabled");
        if(user["bot"].toBool(false) == false)
            user.remove("bot");

        object["user"] = user;
    }

    object["nick"] = _nickname.has_value() ? _nickname.value() : QJsonValue();
    {
        object["joined_at"] =
            _joinedAt.toTimeSpec(Qt::OffsetFromUTC).toString(Qt::ISODateWithMs);
    }
    if(_deaf.has_value())
        object["deaf"] = _deaf.value();
    if(_mute.has_value())
        object["mute"] = _mute.value();

    return object;
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
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordMember(" << this << ") updated";
#endif
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

QDiscordMember::operator bool() const
{
    return _user;
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

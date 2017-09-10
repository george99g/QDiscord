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

#include "qdiscorduser.hpp"
#include "qdiscordrest.hpp"
#include "qdiscordutilities.hpp"

using std::experimental::optional;

QSharedPointer<QDiscordUser> QDiscordUser::fromJson(const QJsonObject& object)
{
    QSharedPointer<QDiscordUser> user(new QDiscordUser());
    user->deserialize(object);
    return user;
}

QDiscordUser::QDiscordUser(const QJsonObject& object)
{
    deserialize(object);

#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordUser(" << this << ") constructed";
#endif
}

QDiscordUser::QDiscordUser()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordUser(" << this << ") constructed";
#endif
}

QDiscordUser::~QDiscordUser()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordUser(" << this << ") destroyed";
#endif
}

void QDiscordUser::deserialize(const QJsonObject& object)
{
    _id = QDiscordID(object["id"].toString());
    _username = object["username"].toString();
    _discriminator = QDiscordDiscriminator(object["discriminator"].toString());
    _avatar = object["avatar"].toString();
    if(object.contains("bot"))
        _bot = object["bot"].toBool();
    if(object.contains("mfa_enabled"))
        _mfaEnabled = object["mfa_enabled"].toBool();
    if(object.contains("email"))
        _email = object["email"].toString();
    if(object.contains("verified"))
        _verified = object["verified"].toBool();
}

QJsonObject QDiscordUser::serialize() const
{
    QJsonObject object;

    object["id"] = _id.toString();
    object["username"] = _username;
    object["discriminator"] = _discriminator.toString();
    object["avatar"] = _avatar.isEmpty() ? QJsonValue() : _avatar;
    if(_bot.has_value())
        object["bot"] = _bot.value();
    if(_mfaEnabled.has_value())
        object["mfa_enabled"] = _mfaEnabled.value();
    if(_email.has_value())
        object["email"] = _email.value();
    if(_verified.has_value())
        object["verified"] = _verified.value();

    return object;
}

void QDiscordUser::update(const QDiscordUser& other)
{
    if(other.id())
        _id = other.id();
    if(!other.username().isEmpty())
        _username = other.username();
    if(other.discriminator())
        _discriminator = other.discriminator();
    if(!other.avatar().isEmpty())
        _avatar = other.avatar();
    if(other.bot().has_value())
        _bot = other.bot();
    if(other.mfaEnabled().has_value())
        _mfaEnabled = other.mfaEnabled();
    if(other.email().has_value())
        _email = other.email();
    if(other.verified().has_value())
        _verified = other.verified();

#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordUser(" << this << ") updated";
#endif
}

QString QDiscordUser::mention() const
{
    return QString("<@%1>").arg(_id ? _id.toString() : "invalid ID");
}

QDiscordUser::operator bool() const
{
    return _id;
}

bool QDiscordUser::operator==(const QDiscordUser& other) const
{
    return _id == other._id;
}

bool QDiscordUser::operator<(const QDiscordUser& other) const
{
    return _id < other._id;
}

bool QDiscordUser::operator>(const QDiscordUser& other) const
{
    return _id > other._id;
}

bool QDiscordUser::operator<=(const QDiscordUser& other) const
{
    return _id <= other._id;
}

bool QDiscordUser::operator>=(const QDiscordUser& other) const
{
    return _id >= other._id;
}

bool QDiscordUser::operator!=(const QDiscordUser& other) const
{
    return !operator==(other);
}

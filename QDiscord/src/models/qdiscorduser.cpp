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

#include "qdiscord.d/models/qdiscorduser.hpp"
#include "qdiscord.d/qdiscordrest.hpp"
#include "qdiscord.d/qdiscordutilities.hpp"

QSharedPointer<QDiscordUser> QDiscordUser::fromJson(const QJsonObject& object)
{
    QSharedPointer<QDiscordUser> user(new QDiscordUser());
    user->deserialize(object);
    return user;
}

QDiscordUser::QDiscordUser(const QJsonObject& object)
{
    deserialize(object);
}

void QDiscordUser::deserialize(const QJsonObject& object)
{
    deserializeJson(object);
}

QJsonObject QDiscordUser::serialize() const
{
    return serializeJson();
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
}

QString QDiscordUser::mention() const
{
    return QString("<@%1>").arg(_id ? _id.toString() : "invalid ID");
}

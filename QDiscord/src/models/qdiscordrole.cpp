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

#include "qdiscord.d/models/qdiscordrole.hpp"
#include "qdiscord.d/models/qdiscordguild.hpp"
#include "qdiscord.d/qdiscordrest.hpp"

QSharedPointer<QDiscordRole> QDiscordRole::fromJson(const QJsonObject& object)
{
    QSharedPointer<QDiscordRole> role(new QDiscordRole());
    role->deserialize(object);
    return role;
}

QDiscordRole::QDiscordRole(const QJsonObject& object)
{
    deserialize(object);
}

void QDiscordRole::deserialize(const QJsonObject& object)
{
    deserializeJson(object);
}

QJsonObject QDiscordRole::serialize() const
{
    return serializeJson();
}

bool QDiscordRole::isEveryone() const
{
    QSharedPointer<QDiscordGuild> guild = _guild.lock();
    if(!guild)
        return false;
    if(guild->id() == _id)
        return true;
    return false;
}

QString QDiscordRole::mention() const
{
    return "<@&" + _id.toString() + ">";
}

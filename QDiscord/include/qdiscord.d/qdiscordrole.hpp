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

#ifndef QDISCORDROLE_HPP
#define QDISCORDROLE_HPP

#include "qdiscord.d/qdiscordid.hpp"
#include "qdiscord.d/qdiscordpermission.hpp"
#include <QJsonObject>
#include <QSharedPointer>

class QDiscordGuild;
class QDiscordRest;

class QDiscordRole
{
public:
    static QSharedPointer<QDiscordRole> fromJson(const QJsonObject& object);

    QDiscordRole(const QJsonObject& object);
    QDiscordRole();
    ~QDiscordRole();

    void deserialize(const QJsonObject& object);
    QJsonObject serialize() const;

    QDiscordID id() const { return _id; }
    void setId(QDiscordID id) { _id = id; }
    QString name() const { return _name; }
    void setName(const QString& name) { _name = name; }
    quint32 color() const { return _color; }
    quint32 colour() const { return _color; }
    void setColor(quint32 color) { _color = color; }
    void setColour(quint32 colour) { _color = colour; }
    bool hoist() const { return _hoist; }
    void setHoist(bool hoist) { _hoist = hoist; }
    int position() const { return _position; }
    void setPosition(int position) { _position = position; }
    QDiscordPermission permissions() const { return _permissions; }
    void setPermissions(QDiscordPermission permissions)
    {
        _permissions = permissions;
    }
    bool managed() const { return _managed; }
    void setManaged(bool managed) { _managed = managed; }
    bool mentionable() const { return _mentionable; }
    void setMentionable(bool mentionable) { _mentionable = mentionable; }
    QSharedPointer<QDiscordGuild> guild() const { return _guild.lock(); }
    void setGuild(QWeakPointer<QDiscordGuild> guild) { _guild = guild; }

    bool isEveryone() const;

    QString mention() const;

    QDiscordRest* rest() const { return _rest; }
    void setRest(QDiscordRest* rest) { _rest = rest; }

    bool isNull() const { return _id.isNull(); }
    operator bool() const { return _id; }

    bool operator==(const QDiscordRole& other) const;
    bool operator!=(const QDiscordRole& other) const;
    bool operator>(const QDiscordRole& other) const;
    bool operator<(const QDiscordRole& other) const;
    bool operator>=(const QDiscordRole& other) const;
    bool operator<=(const QDiscordRole& other) const;

private:
    QDiscordID _id;
    QString _name;
    quint32 _color;
    bool _hoist = false;
    int _position = -1;
    QDiscordPermission _permissions;
    bool _managed = false;
    bool _mentionable = false;
    QWeakPointer<QDiscordGuild> _guild;
    QDiscordRest* _rest = nullptr;
};

Q_DECLARE_METATYPE(QDiscordRole)

#endif // QDISCORDROLE_HPP

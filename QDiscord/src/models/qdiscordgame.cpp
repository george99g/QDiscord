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

#include "qdiscord.d/models/qdiscordgame.hpp"

QSharedPointer<QDiscordGame> QDiscordGame::fromJson(const QJsonObject& object)
{
    QSharedPointer<QDiscordGame> game(new QDiscordGame());
    game->deserialize(object);
    return game;
}

QDiscordGame::QDiscordGame(QString name,
                           QString url,
                           QDiscordGame::GameType type)
{
    _name = name;
    _url = url;
    _type = type;

#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << "QDiscordGame(" << this << ") constructed";
#endif
}

QDiscordGame::QDiscordGame()
{
    _type = GameType::Unknown;
#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << "QDiscordGame(" << this << ") constructed";
#endif
}

QDiscordGame::QDiscordGame(const QJsonObject& object)
{
    deserialize(object);

#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << "QDiscordGame(" << this << ") constructed";
#endif
}

QDiscordGame::~QDiscordGame()
{
#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << "QDiscordGame(" << this << ") destroyed";
#endif
}

void QDiscordGame::deserialize(const QJsonObject& object)
{
    deserializeJson(object);
}

QJsonObject QDiscordGame::serialize() const
{
    return serializeJson();
}

bool QDiscordGame::isNull() const
{
    return _name.isEmpty();
}

QDiscordGame::operator bool() const
{
    return !_name.isEmpty();
}

bool QDiscordGame::operator==(const QDiscordGame& other) const
{
    return _name == other._name;
}

bool QDiscordGame::operator!=(const QDiscordGame& other) const
{
    return !operator==(other);
}

bool QDiscordGame::operator<(const QDiscordGame& other) const
{
    return _name < other._name;
}

bool QDiscordGame::operator>(const QDiscordGame& other) const
{
    return _name > other._name;
}

bool QDiscordGame::operator<=(const QDiscordGame& other) const
{
    return _name <= other._name;
}

bool QDiscordGame::operator>=(const QDiscordGame& other) const
{
    return _name >= other._name;
}

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action,
                          QDiscordGame::GameType& value,
                          const QString& name)
{
    switch(action.data()[name].toInt(-1))
    {
    case 0:
        value = QDiscordGame::GameType::Default;
        break;
    case 1:
        value = QDiscordGame::GameType::Streaming;
        break;
    default:
        value = QDiscordGame::GameType::Unknown;
    }
}

template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action,
                          const QDiscordGame::GameType& value,
                          const QString& name)
{
    action.data()[name] = static_cast<int>(value);
}

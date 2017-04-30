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

#include "qdiscordgame.hpp"

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

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordGame("<<this<<") constructed";
#endif
}

QDiscordGame::QDiscordGame()
{
	_type = GameType::Unknown;
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordGame("<<this<<") constructed";
#endif
}

QDiscordGame::QDiscordGame(const QJsonObject& object)
{
	deserialize(object);

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordGame("<<this<<") constructed";
#endif
}

QDiscordGame::~QDiscordGame()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordGame("<<this<<") destroyed";
#endif
}

void QDiscordGame::deserialize(const QJsonObject& object)
{
	_name = object["name"].toString();
	_url = object["url"].toString();
	switch(object["type"].toInt(-1))
	{
	case 0:
		_type = GameType::Default;
		break;
	case 1:
		_type = GameType::Streaming;
		break;
	default:
		_type = GameType::Unknown;
	}
}

QJsonObject QDiscordGame::serialize() const
{
	QJsonObject object;

	object["name"] = _name;
	if(!_url.isEmpty())
		object["url"] = _url;
	object["type"] = static_cast<qint8>(_type);

	return object;
}

bool QDiscordGame::isNull() const
{
	return _name.isEmpty();
}

QDiscordGame::operator bool() const
{
	return !_name.isEmpty();
}

bool QDiscordGame::operator ==(const QDiscordGame& other) const
{
	return _name == other._name;
}

bool QDiscordGame::operator !=(const QDiscordGame& other) const
{
	return !operator ==(other);
}

bool QDiscordGame::operator <(const QDiscordGame& other) const
{
	return _name < other._name;
}

bool QDiscordGame::operator >(const QDiscordGame& other) const
{
	return _name > other._name;
}

bool QDiscordGame::operator <=(const QDiscordGame& other) const
{
	return _name <= other._name;
}

bool QDiscordGame::operator >=(const QDiscordGame& other) const
{
	return _name >= other._name;
}

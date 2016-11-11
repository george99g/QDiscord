/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016 george99g
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

#ifndef QDISCORDGAME_HPP
#define QDISCORDGAME_HPP

#include <QJsonObject>
#include <QDebug>
#include "qdiscordutilities.hpp"

///\brief Represents a game. Used in statuses.
class QDISCORD_API QDiscordGame
{
public:
	/*!
	 * \brief An enum holding different game types.
	 *
	 * Usually set when streaming. If an enum is not contained here, UnknownType will be set.
	 */
	enum GameType : int
	{
		None = 0,
		Streaming = 1,
		UnknownType = -1
	};
	/*!
	 * \brief Manual constructor for a game object. Defaults to an empty object.
	 * \param name The game you wish to display for the status.
	 * \param url The game URL for your status. Usually only used when streaming.
	 * \param type The game type. Set this if you wish to show a streaming status.
	 */
	QDiscordGame(QString name = "", QString url = "", GameType type = GameType::None);
	///\brief Creates an instance from the provided JSON object.
	QDiscordGame(const QJsonObject& object);
	///\brief Returns the game name of this object.
	QString name() const {return _name;}
	///\brief Returns the URL of this game object.
	QString url() const {return _url;}
	///\brief Returns the type of this game object.
	GameType type() const {return _type;}
private:
	QString _name;
	QString _url;
	GameType _type;
};

Q_DECLARE_METATYPE(QDiscordGame)

#endif // QDISCORDGAME_HPP

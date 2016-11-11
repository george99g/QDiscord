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

#ifndef QDISCORDUSER_HPP
#define QDISCORDUSER_HPP

#include <QDebug>
#include <QJsonObject>
#include "qdiscord_global.hpp"

///\brief Represents a user in the Discord API.
class QDISCORD_API QDiscordUser
{
public:
	/*!
	 * \brief Creates an instance from the provided parameters.
	 * \param object A JSON object of a Discord user.
	 */
	QDiscordUser(const QJsonObject& object);
	///\brief Default public constructor
	QDiscordUser();
	///\brief Updates the current instance from the provided parameters.
	void update(const QJsonObject& object);
	///\brief Returns the user's ID.
	QString id() const {return _id;}
	///\brief Returns the user's avatar string.
	QString avatar() const {return _avatar;}
	///\brief Returns whether the user is a bot.
	bool bot() const {return _bot;}
	///\brief Returns the user's discriminator.
	QString discriminator() const {return _discriminator;}
	///\brief Returns the user's e-mail, if it can be determined.
	QString email() const {return _email;}
	///\brief Returns the user's username.
	QString username() const {return _username;}
	///\brief Returns whether the user has verified their e-mail.
	bool verified() const {return _verified;}
	///\brief Returns a string which allows you to mention this user using their username.
	QString mention() const {return QString("<@"+_id+">");}
	///\brief Compares two users based on their ID
	bool operator ==(const QDiscordUser& other) const;
	///\brief Compares two users based on their ID
	bool operator !=(const QDiscordUser& other) const;
private:
	QString _id;
	QString _avatar;
	bool _bot;
	QString _discriminator;
	QString _email;
	QString _username;
	bool _verified;
};

Q_DECLARE_METATYPE(QDiscordUser)

#endif // QDISCORDUSER_HPP

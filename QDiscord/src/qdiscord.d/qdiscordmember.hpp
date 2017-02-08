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

#ifndef QDISCORDMEMBER_HPP
#define QDISCORDMEMBER_HPP

#include <QDebug>
#include <QDateTime>
#include <QSharedPointer>
#include <QWeakPointer>
#include "qdiscorduser.hpp"

class QDiscordGuild;

/*!
 * \brief Represents a guild member in the Discord API.
 *
 * This class contains a QDiscordUser object which provides more information
 * about the guild member.\n
 * You may acquire a pointer to it using QDiscordMember::user.
 */
class QDiscordMember
{
public:
	/*!
	 * \brief Creates an instance from the provided parameters.
	 * \param object A JSON object of a Discord guild member.
	 * \param guild A pointer to the member's parent guild.
	 */
	QDiscordMember(const QJsonObject& object, QWeakPointer<QDiscordGuild> guild);
	QDiscordMember();
	QDiscordMember(const QDiscordMember& other);
	~QDiscordMember();
	///\brief Updates the current instance from the provided parameters.
	void update(const QJsonObject& object, QWeakPointer<QDiscordGuild> guild);
	///\brief Returns whether the member has disabled their speakers.
	bool deaf() const {return _deaf;}
	///\brief Returns whether the member has muted their microphone.
	bool mute() const {return _mute;}
	///\brief Returns the date at which the member has joined the guild.
	QDateTime joinedAt() const {return _joinedAt;}
	///\brief Returns a pointer to the user object contained by this object.
	QSharedPointer<QDiscordUser> user() const {return _user;}
	///\brief Returns a pointer to this object's parent guild.
	QSharedPointer<QDiscordGuild> guild() const {return _guild.toStrongRef();}
	///\brief Returns this member's nickname.
	QString nickname() const {return _nickname;}
	///\brief Returns a string which allows you to mention this member using their username.
	QString mentionUsername() const;
	///\brief Returns a string which allows you to mention this member using their nickname.
	QString mentionNickname() const;
	/*!
	 * \brief Compares two members.
	 *
	 * This uses the users' IDs and the guilds' IDs to check if they're the
	 * same member. If a pointer is null, returns false.
	 */
	bool operator ==(const QDiscordMember& other) const;
	/*!
	 * \brief Compares two members.
	 *
	 * This uses the users' IDs and the guilds' IDs to check if they're the
	 * same member. If a pointer is null, returns true.
	 */
	bool operator !=(const QDiscordMember& other) const;
private:
	bool _deaf;
	QDateTime _joinedAt;
	bool _mute;
	QString _nickname;
	QSharedPointer<QDiscordUser> _user;
	QWeakPointer<QDiscordGuild> _guild;
};

Q_DECLARE_METATYPE(QDiscordMember)

#endif // QDISCORDMEMBER_HPP

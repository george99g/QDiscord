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

#ifndef QDISCORDMEMBER_HPP
#define QDISCORDMEMBER_HPP

#include <QDebug>
#include <QDateTime>
#include "qdiscorduser.hpp"

class QDiscordGuild;

/*!
 * \brief Represents a guild member in the Discord API.
 *
 * This class contains a QDiscordUser object which provides more information about the guild member.
 * You may acquire a pointer to it using QDiscordMember::user().
 */
class QDISCORD_API QDiscordMember
{
public:
	/*!
	 * \brief Creates an instance from the provided parameters.
	 * \param object A JSON object of a Discord guild member.
	 * \param guild A pointer to the member's parent guild.
	 */
	QDiscordMember(const QJsonObject& object, QDiscordGuild* guild);
	///\brief Default public constructor.
	QDiscordMember();
	///\brief Deep copies the provided object.
	QDiscordMember(const QDiscordMember& other);
	~QDiscordMember();
	///\brief Updates the current instance from the provided parameters.
	void update(const QJsonObject& object, QDiscordGuild* guild);
	///\brief Returns whether the member has disabled their speakers.
	bool deaf() const {return _deaf;}
	///\brief Returns whether the member has muted their microphone.
	bool mute() const {return _mute;}
	///\brief Returns the date at which the member has joined the guild.
	QDateTime joinedAt() const {return _joinedAt;}
	///\brief Returns a pointer to the user object contained by this object.
	QDiscordUser* user() const {return _user;}
	///\brief Returns a pointer to this object's parent guild.
	QDiscordGuild* guild() const {return _guild;}
	///\brief Returns this member's nickname.
	QString nickname() const {return _nickname;}
	///\brief Returns a string which allows you to mention this member using their username.
	QString mentionUsername() const {return QString("<@"+(_user?_user->id():"nullptr")+">");}
	///\brief Returns a string which allows you to mention this member using their nickname.
	QString mentionNickname() const {return QString("<@!"+(_user?_user->id():"nullptr")+">");}
	/*!
	 * \brief Compares two members.
	 *
	 * This uses the users' IDs and the guild pointers to check if they're the
	 * same member. If a pointer is null, returns false.
	 */
	bool operator ==(const QDiscordMember& other) const;
	/*!
	 * \brief Compares two members.
	 *
	 * This uses the users' IDs and the guild pointers to check if they're the
	 * same member. If a pointer is null, returns true.
	 */
	bool operator !=(const QDiscordMember& other) const;
private:
	bool _deaf;
	QDateTime _joinedAt;
	bool _mute;
	QString _nickname;
	QDiscordUser* _user;
	QDiscordGuild* _guild;
};

Q_DECLARE_METATYPE(QDiscordMember)

#endif // QDISCORDMEMBER_HPP

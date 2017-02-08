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

#ifndef QDISCORDGUILD_HPP
#define QDISCORDGUILD_HPP

#include <QDateTime>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "qdiscordmember.hpp"
#include "qdiscordchannel.hpp"

///\brief Represents a guild in the Discord API.
class QDiscordGuild : public QEnableSharedFromThis<QDiscordGuild>
{
public:
	/*!
	 * \brief Creates an instance from the provided parameters.
	 * \param object A JSON object of a Discord guild.
	 */
	QDiscordGuild(const QJsonObject& object);
	QDiscordGuild(const QDiscordGuild& other);
	QDiscordGuild();
	~QDiscordGuild();
	///\brief Returns the guild's ID.
	QDiscordID id() const {return _id;}
	///\brief Returns the guild's name.
	QString name() const {return _name;}
	/*!
	 * \brief Returns whether the guild is unavailable.
	 *
	 * If this is true, a majority of guild information will not be available.
	 */
	bool unavailable() const {return _unavailable;}
	///\brief Returns the guild's verification level.
	int verificationLevel() const {return _verificationLevel;}
	/*!
	 * \brief Returns the guild's AFK time needed to move a user to the AFK
	 * channel.
	 */
	int afkTimeout() const {return _afkTimeout;}
	///\brief Returns the guild's member count.
	int memberCount() const {return _memberCount;}
	///\brief Returns the date the current user joined this guild.
	QDateTime joinedAt() const {return _joinedAt;}
	///\brief Returns a map of pointers to the guild's channels and their IDs.
	QMap<QDiscordID, QSharedPointer<QDiscordChannel>>
	channels() const {return _channels;}
	///\brief Returns a map of pointers to the guild's members and their IDs.
	QMap<QDiscordID, QSharedPointer<QDiscordMember>>
	members() const {return _members;}
	/*!
	 * \brief Returns a pointer to a guild channel that has the provided ID.
	 *
	 * Returns `nullptr` if the channel was not found.
	 */
	QSharedPointer<QDiscordChannel>
	channel(const QDiscordID& id) const {
		return _channels.value(id, QSharedPointer<QDiscordChannel>());
	}
	/*!
	 * \brief Returns a pointer to a guild member that has the provided ID.
	 *
	 * Returns `nullptr` if the member was not found.
	 */
	QSharedPointer<QDiscordMember>
	member(const QDiscordID& id) const {
		return _members.value(id, QSharedPointer<QDiscordMember>());
	}
	///\brief Adds the provided channel to the guild.
	void addChannel(QSharedPointer<QDiscordChannel> channel);
	/*!
	 * \brief Removes the provided channel from the guild.
	 *
	 * Returns `true` if the channel was successfully removed. `false` if
	 * `nullptr` was passed or the channel was not found.
	 */
	bool removeChannel(QSharedPointer<QDiscordChannel> channel);
	///\brief Adds the provided member to the guild.
	void addMember(QSharedPointer<QDiscordMember> member);
	/*!
	 * \brief Removes the provided member from the guild.
	 *
	 * Returns `true` if the member was successfully removed. `false` if
	 * `nullptr` was passed or the member was not found.
	 */
	bool removeMember(QSharedPointer<QDiscordMember> member);
private:
	QDiscordID _id;
	QString _name;
	bool _unavailable;
	int _verificationLevel;
	int _afkTimeout;
	int _memberCount;
	QDateTime _joinedAt;
	QMap<QDiscordID, QSharedPointer<QDiscordMember>> _members;
	QMap<QDiscordID, QSharedPointer<QDiscordChannel>> _channels;
};

Q_DECLARE_METATYPE(QDiscordGuild)

#endif // QDISCORDGUILD_HPP

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

#ifndef QDISCORDMESSAGE_HPP
#define QDISCORDMESSAGE_HPP

#include "qdiscordmember.hpp"
#include "qdiscordchannel.hpp"
#include "qdiscordguild.hpp"

/*!
 * \brief Represents a message in the Discord API.
 */
class QDiscordMessage
{
public:
	/*!
	 * \brief Creates an instance from the provided parameters.
	 * \param object A JSON object of a Discord message.
	 * \param channel A pointer to the channel the message was sent to.
	 */
	QDiscordMessage(
			const QJsonObject& object,
			QSharedPointer<QDiscordChannel> channel =
				QSharedPointer<QDiscordChannel>()
			);
	QDiscordMessage();
	QDiscordMessage(const QDiscordMessage& other);
	~QDiscordMessage();
	///\brief Returns the message's ID.
	QDiscordID id() const {return _id;}
	///\brief Returns the message's contents.
	QString content() const {return _content;}
	///\brief Returns the date at which the message was created.
	QDateTime timestamp() const {return _timestamp;}
	///\brief Returns whether the message will use text to speech.
	bool tts() const {return _tts;}
	///\brief Returns whether the message successfully mentioned everyone.
	bool mentionEveryone() const {return _mentionEveryone;}
	///\brief Returns the ID of the channel this message was sent in.
	QDiscordID channelId() const {return _channelId;}
	///\brief Returns a pointer to the channel this message was sent in.
	QSharedPointer<QDiscordChannel> channel() const {return _channel;}
	///\brief Returns a pointer to the user that sent this message.
	QSharedPointer<QDiscordUser> author() const {return _author;}
	/*!
	 * \brief Returns a pointer to the guild this message was sent in using
	 * the channel parameter provided in the class' constructor.
	 * \returns `nullptr` if the message was sent in a private channel and thus
	 * the channel has no guild or if a channel was not provided in the class'
	 * constructor.
	 */
	QSharedPointer<QDiscordGuild> guild() const;
	///\brief Returns a list of users mentioned in this message.
	QList<QSharedPointer<QDiscordUser>>
	mentions() const { return _mentions;}
private:
	QDiscordID _id;
	QString _content;
	QDateTime _timestamp;
	bool _tts;
	bool _mentionEveryone;
	QDiscordID _channelId;
	QSharedPointer<QDiscordChannel> _channel;
	QSharedPointer<QDiscordUser> _author;
	QList<QSharedPointer<QDiscordUser>> _mentions;
};

Q_DECLARE_METATYPE(QDiscordMessage)

#endif // QDISCORDMESSAGE_HPP

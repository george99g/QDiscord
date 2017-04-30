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
#include "external/Optional/optional.hpp"

/*!
 * \brief Represents a message in the Discord API.
 */
class QDiscordMessage
{
public:
	static QSharedPointer<QDiscordMessage> fromJson(const QJsonObject& object);
	/*!
	 * \brief Creates an instance from the provided parameters.
	 * \param object A JSON object of a Discord message.
	 * \param channel A pointer to the channel the message was sent to.
	 */
	QDiscordMessage(const QJsonObject& object);
	QDiscordMessage();
	~QDiscordMessage();
	void deserialize(const QJsonObject& object);
	QJsonObject serialize();
	///\brief Returns the message's ID.
	QDiscordID id() const {return _id;}
	void setId(QDiscordID id) {_id = id;}
	///\brief Returns the ID of the channel this message was sent in.
	QDiscordID channelId() const {return _channelId;}
	void setChannelId(QDiscordID id) {_id = id;}
	///\brief Returns a pointer to the user that sent this message.
	QDiscordUser author() const {return _author;}
	void setAuthor(QDiscordUser author) {_author = author;}
	///\brief Returns the message's contents.
	QString content() const {return _content;}
	void setContent(const QString& content) {_content = content;}
	///\brief Returns the date at which the message was created.
	QDateTime timestamp() const {return _timestamp;}
	void setTimestamp(const QDateTime& timestamp) {_timestamp = timestamp;}
	std::experimental::optional<QDateTime> editedTimestamp() const
	{return _editedTimestamp;}
	void setEditedTimestamp(QDateTime editedTimestamp)
	{_editedTimestamp = editedTimestamp;}
	void resetEditedTimestamp() {_editedTimestamp.reset();}
	///\brief Returns whether the message will use text to speech.
	bool tts() const {return _tts;}
	void setTts(bool tts) {_tts = tts;}
	///\brief Returns whether the message successfully mentioned everyone.
	bool mentionEveryone() const {return _mentionEveryone;}
	void setMentionEveryone(bool mentionEveryone)
	{_mentionEveryone = mentionEveryone;}
	///\brief Returns a list of users mentioned in this message.
	QList<QDiscordUser> mentions() const { return _mentions;}
	void setMentions(QList<QDiscordUser> mentions) {_mentions = mentions;}
	QDiscordID nonce() const {return _nonce;}
	void setNonce(QDiscordID nonce) {_nonce = nonce;}
	bool pinned() const {return _pinned;}
	void setPinned(bool pinned) {_pinned = pinned;}
	///\brief Returns a pointer to the channel this message was sent in.
	QSharedPointer<QDiscordChannel> channel() const {return _channel;}
	void setChannel(QSharedPointer<QDiscordChannel> channel)
	{_channel = channel;}
	/*!
	 * \brief Returns a pointer to the guild this message was sent in using
	 * the channel parameter provided in the class' constructor.
	 * \returns `nullptr` if the message was sent in a private channel and thus
	 * the channel has no guild or if a channel was not provided in the class'
	 * constructor.
	 */
	QSharedPointer<QDiscordGuild> guild() const;
	bool isNull() const {return _id.isNull();}
	operator bool() const;
	bool operator ==(const QDiscordMessage& other) const;
	bool operator !=(const QDiscordMessage& other) const;
	bool operator > (const QDiscordMessage& other) const;
	bool operator < (const QDiscordMessage& other) const;
	bool operator <=(const QDiscordMessage& other) const;
	bool operator >=(const QDiscordMessage& other) const;

private:
	QDiscordID _id;
	QDiscordID _channelId;
	QDiscordUser _author;
	QString _content;
	QDateTime _timestamp;
	std::experimental::optional<QDateTime> _editedTimestamp;
	bool _tts;
	bool _mentionEveryone;
	QList<QDiscordUser> _mentions;
	QDiscordID _nonce;
	bool _pinned;
	QSharedPointer<QDiscordChannel> _channel;
};

Q_DECLARE_METATYPE(QDiscordMessage)

#endif // QDISCORDMESSAGE_HPP

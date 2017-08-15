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

#ifndef QDISCORDCHANNEL_HPP
#define QDISCORDCHANNEL_HPP

#include <QSharedPointer>
#include <QJsonObject>
#include <QDateTime>
#include "qdiscorduser.hpp"
#include "external/Optional/optional.hpp"

class QDiscordGuild;
class QDiscordRest;

///\brief Represents either a private or guild channel in the Discord API.
class QDiscordChannel
{
public:
	static QSharedPointer<QDiscordChannel> fromJson(const QJsonObject& object);
	/*!
	 * \brief Creates an instance from the provided parameters.
	 * \param object A JSON object of a Discord channel.
	 * \param guild A pointer to the parent guild of the channel, if any.
	 * \note Some properties may be defaul, not accessible or `nullptr`,
	 * depending on what type() and isPrivate() return.
	 */
	QDiscordChannel(const QJsonObject& object);
	QDiscordChannel();
	~QDiscordChannel();
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;
	/*!
	 * \brief An enumerator holding all possible types of channels.
	 *
	 * If a type is not defined here, `ChannelType::UnknownType` will be set.\n
	 * See https://discordapp.com/developers/docs/resources/channel#guild-channel-structure
	 * for more information.
	 */
	enum class ChannelType : quint8
	{
		Voice, Text, UnknownType
	};
	///\brief Returns the channel's ID.
	QDiscordID id() const {return _id;}
	void setId(QDiscordID id) {_id = id;}
	QDiscordID guildId() const {return _guildId;}
	void setGuildId(QDiscordID guildId) {_guildId = guildId;}
	///\brief Returns the channel's name.
	QString name() const {return _name;}
	void setName(const QString& name) {_name = name;}
	/*!
	 * \brief Returns the channel's type.
	 *
	 * Possible types are specified in QDiscordChannel::ChannelType.
	 */
	ChannelType type() const {return _type;}
	void setType(ChannelType type) {_type = type;}
	///\brief Returns the channel's position in the channel list.
	int position() const {return _position;}
	void setPosition(int position) {_position = position;}
	/*!
	 * \brief Returns whether the channel is a private or a guild channel.
	 *
	 * Some parameters may not be set depending on this value.
	 */
	bool isPrivate() const {return _isPrivate;}
	void setIsPrivate(bool isPrivate) {_isPrivate = isPrivate;}
	///\brief Returns the channel's topic.
	QString topic() const {return _topic;}
	void setTopic(const QString& topic) {_topic = topic;}
	///\brief Returns the ID of the last sent message.
	QDiscordID lastMessageId() const {return _lastMessageId;}
	void setLastMessageId(QDiscordID lastMessageId)
	{_lastMessageId = lastMessageId;}
	/*!
	 * \brief Returns the channel's bitrate
	 *
	 * Returns -1 if the channel's type is not
	 * DiscordChannel::ChannelType::Voice.
	 */
	int bitrate() const {return _bitrate;}
	void setBitrate(int bitrate) {_bitrate = bitrate;}
	/*!
	 * \brief Returns the channel's user limit.
	 *
	 * Returns -1 if the channel's type is not
	 * QDiscordChannel::ChannelType::Voice.
	 */
	int userLimit() const {return _userLimit;}
	void setUserLimit(int userLimit) {_userLimit = userLimit;}
	QDateTime lastPinTimestamp() const {return _lastPinTimestamp;}
	void setLastPinTimestamp(QDateTime lastPinTimestamp)
	{_lastPinTimestamp = lastPinTimestamp;}
	///\brief Returns a pointer to this channel's parent guild.
	QSharedPointer<QDiscordGuild> guild() const {return _guild;}
	/*!
	 * \brief Sets this object's parent guild.
	 * \param guild A pointer to this object's new parent guild.
	 */
	void setGuild(QSharedPointer<QDiscordGuild> guild) {_guild = guild;}
	QDiscordRest* rest() const {return _rest;}
	void setRest(QDiscordRest* rest) {_rest = rest;}
	/*!
	 * \brief Returns a pointer to this channel's recipient, if this is a
	 * private channel.
	 */
	QSharedPointer<QDiscordUser> recipient() const {return _recipient;}
	void setRecipient(QSharedPointer<QDiscordUser> recipient)
	{_recipient = recipient;}
	///\brief Returns a string which allows you to mention this channel.
	QString mention() const {return QString("<#"+_id.toString()+">");}
	bool isNull() const {return _id.isNull();}
	operator bool() const {return _id;}
	///\brief Compares two channels based on their ID.
	bool operator ==(const QDiscordChannel& other) const;
	///\brief Compares two channels based on their ID.
	bool operator !=(const QDiscordChannel& other) const;
	bool operator > (const QDiscordChannel& other) const;
	bool operator < (const QDiscordChannel& other) const;
	bool operator <=(const QDiscordChannel& other) const;
	bool operator >=(const QDiscordChannel& other) const;
private:
	QDiscordID _id;
	QDiscordID _guildId;
	QString _name;
	ChannelType _type;
	int _position;
	bool _isPrivate;
	QString _topic;
	QDiscordID _lastMessageId;
	int _bitrate;
	int _userLimit;
	QDateTime _lastPinTimestamp;
	QSharedPointer<QDiscordUser> _recipient;
	QWeakPointer<QDiscordGuild> _guild;
	QDiscordRest* _rest;
};

Q_DECLARE_METATYPE(QDiscordChannel::ChannelType)
Q_DECLARE_METATYPE(QDiscordChannel)

#endif // QDISCORDCHANNEL_HPP

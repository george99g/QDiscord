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

class QDiscordGuild;

///\brief Represents either a private or guild channel in the Discord API.
class QDiscordChannel
{
public:
	/*!
	 * \brief Creates an instance from the provided parameters.
	 * \param object A JSON object of a Discord channel.
	 * \param guild A pointer to the parent guild of the channel, if any.
	 * \note Some properties may be defaul, not accessible or `nullptr`,
	 * depending on what type() and isPrivate() return.
	 */
	QDiscordChannel(const QJsonObject& object,
			QWeakPointer<QDiscordGuild> guild =
				QWeakPointer<QDiscordGuild>()
			);
	QDiscordChannel();
	QDiscordChannel(const QDiscordChannel& other);
	~QDiscordChannel();
	/*!
	 * \brief An enumerator holding all possible types of channels.
	 *
	 * If a type is not defined here, `ChannelType::UnknownType` will be set.\n
	 * See https://discordapp.com/developers/docs/resources/channel#guild-channel-structure
	 * for more information.
	 */
	enum class ChannelType
	{
		Voice, Text, UnknownType
	};
	///\brief Returns the channel's ID.
	QDiscordID id() const {return _id;}
	///\brief Returns the channel's name.
	QString name() const {return _name;}
	///\brief Returns the channel's position in the channel list.
	int position() const {return _position;}
	///\brief Returns the channel's topic.
	QString topic() const {return _topic;}
	/*!
	 * \brief Returns the channel's type.
	 *
	 * Possible types are specified in QDiscordChannel::ChannelType.
	 */
	ChannelType type() const {return _type;}
	/*!
	 * \brief Returns whether the channel is a private or a guild channel.
	 *
	 * Some parameters may not be set depending on this value.
	 */
	bool isPrivate() const {return _isPrivate;}
	///\brief Returns the ID of the last sent message.
	QDiscordID lastMessageId() const {return _lastMessageId;}
	///\brief Returns a pointer to this channel's parent guild.
	QSharedPointer<QDiscordGuild> guild() const {return _guild;}
	/*!
	 * \brief Returns a pointer to this channel's recipient, if this is a
	 * private channel.
	 */
	QSharedPointer<QDiscordUser> recipient() const {return _recipient;}
	/*!
	 * \brief Returns the channel's bitrate
	 *
	 * Returns -1 if the channel's type is not
	 * DiscordChannel::ChannelType::Voice.
	 */
	int bitrate() const {return _bitrate;}
	/*!
	 * \brief Returns the channel's user limit.
	 *
	 * Returns -1 if the channel's type is not
	 * QDiscordChannel::ChannelType::Voice.
	 */
	int userLimit() const {return _userLimit;}
	QDateTime lastPinTimestamp() const {return _lastPinTimestamp;}
	/*!
	 * \brief Sets this object's parent guild.
	 * \param guild A pointer to this object's new parent guild.
	 */
	void setGuild(QSharedPointer<QDiscordGuild> guild) {_guild = guild;}
	///\brief Returns a string which allows you to mention this channel.
	QString mention() const {return QString("<#"+_id.toString()+">");}
	///\brief Compares two channels based on their ID.
	bool operator ==(const QDiscordChannel& other) const;
	///\brief Compares two channels based on their ID.
	bool operator !=(const QDiscordChannel& other) const;
private:
	QDiscordID _id;
	QString _name;
	int _position;
	QString _topic;
	ChannelType _type;
	bool _isPrivate;
	QDiscordID _lastMessageId;
	int _bitrate;
	int _userLimit;
	QDateTime _lastPinTimestamp;
	QSharedPointer<QDiscordUser> _recipient;
	QSharedPointer<QDiscordGuild> _guild;
};

Q_DECLARE_METATYPE(QDiscordChannel::ChannelType)
Q_DECLARE_METATYPE(QDiscordChannel)

#endif // QDISCORDCHANNEL_HPP

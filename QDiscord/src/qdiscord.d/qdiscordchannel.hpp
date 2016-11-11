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

#ifndef QDISCORDCHANNEL_HPP
#define QDISCORDCHANNEL_HPP

#include <QJsonObject>
#include "qdiscorduser.hpp"

class QDiscordGuild;

///\brief Represents either a private or guild channel in the Discord API.
class QDISCORD_API QDiscordChannel
{
public:
	/*!
	 * \brief Creates an instance from the provided parameters.
	 * \param object A JSON object of a Discord channel.
	 * \param guild A pointer to the parent guild of the channel, if any.
	 * \note Some properties may be defaul, not accessible or `nullptr`, depending on what type() and isPrivate() return.
	 */
	QDiscordChannel(const QJsonObject& object, QDiscordGuild* guild = nullptr);
	///\brief Default public constructor.
	QDiscordChannel();
	///\brief Deep copies the provided object.
	QDiscordChannel(const QDiscordChannel& other);
	~QDiscordChannel();
	/*!
	 * \brief An enumerator holding all possible types of channels.
	 *
	 * If a type is not defined here, `ChannelType::UnknownType` will be set.
	 */
	enum class ChannelType
	{
		Voice, Text, UnknownType
	};
	///\brief Returns the channel's ID.
	QString id() const {return _id;}
	///\brief Returns the channel's name.
	QString name() const {return _name;}
	///\brief Returns the channel's position in the channel list.
	int position() const {return _position;}
	///\brief Returns the channel's topic.
	QString topic() const {return _topic;}
	/*!
	 * \brief Returns the channel's type.
	 *
	 * Possible types specified in `ChannelType`.
	 */
	ChannelType type() const {return _type;}
	/*!
	 * \brief Returns whether the channel is a private or a guild channel.
	 *
	 * Some parameters may not be set depending on this value.
	 */
	bool isPrivate() const {return _isPrivate;}
	///\brief Returns the ID of the last sent message.
	QString lastMessageId() const {return _lastMessageId;}
	///\brief Returns a pointer to this channel's parent guild.
	QDiscordGuild* guild() const {return _guild;}
	/*!
	 * \brief Returns a pointer to this channel's recipient, if this is a private channel.
	 *
	 * The recipient object will be deleted when this object is deleted.
	 */
	QDiscordUser* recipient() const {return _recipient;}
	/*!
	 * \brief Sets this object's parent guild.
	 * \param guild A pointer to this object's new parent guild.
	 */
	void setGuild(QDiscordGuild* guild) {_guild = guild;}
	///\brief Returns a string which allows you to mention this channel.
	QString mention() const {return QString("<#"+_id+">");}
private:
	QString _id;
	QString _name;
	int _position;
	QString _topic;
	ChannelType _type;
	bool _isPrivate;
	QString _lastMessageId;
	QDiscordUser* _recipient;
	QDiscordGuild* _guild;
};

Q_DECLARE_METATYPE(QDiscordChannel)

#endif // QDISCORDCHANNEL_HPP

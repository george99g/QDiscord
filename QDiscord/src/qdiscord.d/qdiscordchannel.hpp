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

#include "external/Optional/optional.hpp"
#include "qdiscorduser.hpp"
#include <QDateTime>
#include <QJsonObject>
#include <QSharedPointer>

class QDiscordGuild;
class QDiscordRest;

///\brief Represents either a private or guild channel in the Discord API.
class QDiscordChannel
{
public:
    static void remove(QDiscordRest& rest, const QDiscordID& channel);

    static void remove(QDiscordRest& rest,
                       const QDiscordID& channel,
                       std::function<void(QDiscordChannel)> callback);

    void remove();
    void remove(std::function<void(QDiscordChannel)> callback);

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
     * See
     * https://discordapp.com/developers/docs/resources/channel#guild-channel-structure
     * for more information.
     */
    enum class Type : quint8
    {
        Text = 0,
        DirectMessage = 1,
        Voice = 2,
        GroupDirectMessage = 3,
        Category = 4,
        UnknownType = 255
    };
    ///\brief Returns the channel's ID.
    QDiscordID id() const { return _id; }
    void setId(QDiscordID id) { _id = id; }
    Type type() const { return _type; }
    void setType(Type type) { _type = type; }
    QDiscordID guildId() const { return _guildId; }
    void setGuildId(QDiscordID guildId) { _guildId = guildId; }
    ///\brief Returns the channel's position in the channel list.
    int position() const { return _position; }
    void setPosition(int position) { _position = position; }
    ///\brief Returns the channel's name.
    QString name() const { return _name; }
    void setName(const QString& name) { _name = name; }
    ///\brief Returns the channel's topic.
    QString topic() const { return _topic; }
    void setTopic(const QString& topic) { _topic = topic; }
    ///\brief Returns the ID of the last sent message.
    QDiscordID lastMessageId() const { return _lastMessageId; }
    void setLastMessageId(QDiscordID lastMessageId)
    {
        _lastMessageId = lastMessageId;
    }
    /*!
     * \brief Returns the channel's bitrate
     *
     * Returns -1 if the channel's type is not
     * DiscordChannel::ChannelType::Voice.
     */
    int bitrate() const { return _bitrate; }
    void setBitrate(int bitrate) { _bitrate = bitrate; }
    /*!
     * \brief Returns the channel's user limit.
     *
     * Returns -1 if the channel's type is not
     * QDiscordChannel::ChannelType::Voice.
     */
    int userLimit() const { return _userLimit; }
    void setUserLimit(int userLimit) { _userLimit = userLimit; }
    QList<QSharedPointer<QDiscordUser>> recipients() const
    {
        return _recipients;
    }
    void setRecipients(QList<QSharedPointer<QDiscordUser>> recipients)
    {
        _recipients = recipients;
    }
    QString icon() const { return _icon; }
    void setIcon(QString icon) { _icon = icon; }
    QDiscordID ownderId() const { return _ownerId; }
    void setOwnerId(QDiscordID ownerId) { _ownerId = ownerId; }
    QDiscordID applicationId() const { return _applicationId; }
    void setApplicationId(QDiscordID applicationId)
    {
        _applicationId = applicationId;
    }
    ///\brief Returns a pointer to this channel's parent guild.
    QSharedPointer<QDiscordGuild> guild() const { return _guild; }
    /*!
     * \brief Sets this object's parent guild.
     * \param guild A pointer to this object's new parent guild.
     */
    void setGuild(QSharedPointer<QDiscordGuild> guild);
    QDiscordRest* rest() const { return _rest; }
    void setRest(QDiscordRest* rest) { _rest = rest; }
    /*!
     * \brief Returns a pointer to this channel's recipient, if this is a
     * private channel.
     */
    ///\brief Returns a string which allows you to mention this channel.
    QString mention() const { return QString("<#" + _id.toString() + ">"); }
    bool isNull() const { return _id.isNull(); }
    operator bool() const { return _id; }
    ///\brief Compares two channels based on their ID.
    bool operator==(const QDiscordChannel& other) const;
    ///\brief Compares two channels based on their ID.
    bool operator!=(const QDiscordChannel& other) const;
    bool operator>(const QDiscordChannel& other) const;
    bool operator<(const QDiscordChannel& other) const;
    bool operator<=(const QDiscordChannel& other) const;
    bool operator>=(const QDiscordChannel& other) const;

private:
    QDiscordID _id;
    Type _type;
    QDiscordID _guildId;
    int _position;
    QString _name;
    QString _topic;
    QDiscordID _lastMessageId;
    int _bitrate;
    int _userLimit;
    QList<QSharedPointer<QDiscordUser>> _recipients;
    QString _icon;
    QDiscordID _ownerId;
    QDiscordID _applicationId;
    QWeakPointer<QDiscordGuild> _guild;
    QDiscordRest* _rest;
};

Q_DECLARE_METATYPE(QDiscordChannel::Type)
Q_DECLARE_METATYPE(QDiscordChannel)

#endif // QDISCORDCHANNEL_HPP

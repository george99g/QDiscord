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

#include "qdiscord.d/external/optional/optional.hpp"
#include "qdiscord.d/qdiscorduser.hpp"
#include <QDateTime>
#include <QJsonObject>
#include <QSharedPointer>

class QDiscordMessage;
class QDiscordGuild;
class QDiscordRest;

///\brief Represents either a private or guild channel in the Discord API.
class QDiscordChannel
{
public:
    static void get(QDiscordRest& rest,
                    const QDiscordID& channel,
                    std::function<void(QDiscordChannel)> callback);

    static void
    getPrivateChannels(QDiscordRest& rest,
                       std::function<void(QList<QDiscordChannel>)> callback);

    static void getMessage(QDiscordRest& rest,
                           const QDiscordID& channel,
                           const QDiscordID& message,
                           std::function<void(QDiscordMessage)> callback);

    void getMessage(const QDiscordID& message,
                    std::function<void(QDiscordMessage)> callback);

    static void
    getMessages(QDiscordRest& rest,
                const QDiscordID& channel,
                int limit,
                std::function<void(QList<QDiscordMessage>)> callback);

    static void
    getMessages(QDiscordRest& rest,
                const QDiscordID& channel,
                std::function<void(QList<QDiscordMessage>)> callback);

    void getMessages(int limit,
                     std::function<void(QList<QDiscordMessage>)> callback);

    void getMessages(std::function<void(QList<QDiscordMessage>)> callback);

    static void
    getMessagesAfter(QDiscordRest& rest,
                     const QDiscordID& channel,
                     const QDiscordID& message,
                     int limit,
                     std::function<void(QList<QDiscordMessage>)> callback);

    static void
    getMessagesAfter(QDiscordRest& rest,
                     const QDiscordID& channel,
                     const QDiscordID& message,
                     std::function<void(QList<QDiscordMessage>)> callback);

    void getMessagesAfter(const QDiscordID& message,
                          int limit,
                          std::function<void(QList<QDiscordMessage>)> callback);

    void getMessagesAfter(const QDiscordID& message,
                          std::function<void(QList<QDiscordMessage>)> callback);

    static void
    getMessagesBefore(QDiscordRest& rest,
                      const QDiscordID& channel,
                      const QDiscordID& message,
                      int limit,
                      std::function<void(QList<QDiscordMessage>)> callback);

    static void
    getMessagesBefore(QDiscordRest& rest,
                      const QDiscordID& channel,
                      const QDiscordID& message,
                      std::function<void(QList<QDiscordMessage>)> callback);

    void
    getMessagesBefore(const QDiscordID& message,
                      int limit,
                      std::function<void(QList<QDiscordMessage>)> callback);

    void
    getMessagesBefore(const QDiscordID& message,
                      std::function<void(QList<QDiscordMessage>)> callback);

    static void
    getMessagesAround(QDiscordRest& rest,
                      const QDiscordID& channel,
                      const QDiscordID& message,
                      int limit,
                      std::function<void(QList<QDiscordMessage>)> callback);

    static void
    getMessagesAround(QDiscordRest& rest,
                      const QDiscordID& channel,
                      const QDiscordID& message,
                      std::function<void(QList<QDiscordMessage>)> callback);

    void
    getMessagesAround(const QDiscordID& message,
                      int limit,
                      std::function<void(QList<QDiscordMessage>)> callback);

    void
    getMessagesAround(const QDiscordID& message,
                      std::function<void(QList<QDiscordMessage>)> callback);

    static void modify(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QJsonObject& data);

    static void modify(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QJsonObject& data,
                       std::function<void(QDiscordChannel)> callback);

    void modify(const QJsonObject& data);

    void modify(const QJsonObject& data,
                std::function<void(QDiscordChannel)> callback);

    static void modifyName(QDiscordRest& rest,
                           const QDiscordID& channel,
                           const QString& name);

    static void modifyName(QDiscordRest& rest,
                           const QDiscordID& channel,
                           const QString& name,
                           std::function<void(QDiscordChannel)> callback);

    void modifyName(const QString& name);

    void modifyName(const QString& name,
                    std::function<void(QDiscordChannel)> callback);

    static void
    modifyPosition(QDiscordRest& rest, const QDiscordID& channel, int position);

    static void modifyPosition(QDiscordRest& rest,
                               const QDiscordID& channel,
                               int position,
                               std::function<void(QDiscordChannel)> callback);

    void modifyPosition(int position);

    void modifyPosition(int position,
                        std::function<void(QDiscordChannel)> callback);

    static void modifyTopic(QDiscordRest& rest,
                            const QDiscordID& channel,
                            const QString& topic);

    static void modifyTopic(QDiscordRest& rest,
                            const QDiscordID& channel,
                            const QString& topic,
                            std::function<void(QDiscordChannel)> callback);

    void modifyTopic(const QString& topic);

    void modifyTopic(const QString& topic,
                     std::function<void(QDiscordChannel)> callback);

    static void
    modifyBitrate(QDiscordRest& rest, const QDiscordID& channel, int bitrate);

    static void modifyBitrate(QDiscordRest& rest,
                              const QDiscordID& channel,
                              int bitrate,
                              std::function<void(QDiscordChannel)> callback);

    void modifyBitrate(int bitrate);

    void modifyBitrate(int bitrate,
                       std::function<void(QDiscordChannel)> callback);

    static void modifyUserLimit(QDiscordRest& rest,
                                const QDiscordID& channel,
                                int userLimit);

    static void modifyUserLimit(QDiscordRest& rest,
                                const QDiscordID& channel,
                                int userLimit,
                                std::function<void(QDiscordChannel)> callback);

    void modifyUserLimit(int userLimit);

    void modifyUserLimit(int userLimit,
                         std::function<void(QDiscordChannel)> callback);

    static void triggerTyping(QDiscordRest& rest, const QDiscordID& channel);

    static void triggerTyping(QDiscordRest& rest,
                              const QDiscordID& channel,
                              std::function<void(bool)> callback);

    void triggerTyping();

    void triggerTyping(std::function<void(bool)> callback);

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
    QDiscordID parentId() const { return _parentId; }
    void setParentId(QDiscordID parentId) { _parentId = parentId; }
    QSharedPointer<QDiscordChannel> parent() const { return _parent; }
    void setParent(QSharedPointer<QDiscordChannel> parent) { _parent = parent; }
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
    Type _type = Type::UnknownType;
    QDiscordID _guildId;
    int _position = -1;
    QString _name;
    QString _topic;
    QDiscordID _lastMessageId;
    int _bitrate = -1;
    int _userLimit = -1;
    QList<QSharedPointer<QDiscordUser>> _recipients;
    QString _icon;
    QDiscordID _ownerId;
    QDiscordID _applicationId;
    QDiscordID _parentId;
    QWeakPointer<QDiscordChannel> _parent;
    QWeakPointer<QDiscordGuild> _guild;
    QDiscordRest* _rest = nullptr;
};

Q_DECLARE_METATYPE(QDiscordChannel::Type)
Q_DECLARE_METATYPE(QDiscordChannel)

#endif // QDISCORDCHANNEL_HPP

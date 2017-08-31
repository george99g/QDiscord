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

#include "qdiscordchannel.hpp"
#include "qdiscordguild.hpp"
#include "qdiscordmessage.hpp"
#include "qdiscordrest.hpp"

void QDiscordChannel::get(QDiscordRest& rest,
                          const QDiscordID& channel,
                          std::function<void(QDiscordChannel)> callback)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Channels::getChannel(channel),
                 [&rest, callback](QNetworkReply* reply) {
                     QDiscordChannel c;
                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(c);
                         return;
                     }
                     c.deserialize(
                         QJsonDocument::fromJson(reply->readAll()).object());
                     c.setRest(&rest);
                     callback(c);
                 });
}

void QDiscordChannel::getMessage(QDiscordRest& rest,
                                 const QDiscordID& channel,
                                 const QDiscordID& message,
                                 std::function<void(QDiscordMessage)> callback)
{
    QDiscordMessage::get(rest, channel, message, callback);
}

void QDiscordChannel::getMessage(const QDiscordID& message,
                                 std::function<void(QDiscordMessage)> callback)
{
    if(!_rest)
    {
        callback(QDiscordMessage());
        return;
    }

    if(!_id)
    {
        callback(QDiscordMessage());
        return;
    }

    QDiscordMessage::get(*_rest, _id, message, callback);
}

void QDiscordChannel::getMessages(
    QDiscordRest& rest,
    const QDiscordID& channel,
    int limit,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::getMessageHistory(channel, limit),
                 [&rest, callback](QNetworkReply* reply) {
                     QList<QDiscordMessage> list;
                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(list);
                         return;
                     }
                     QJsonArray messageArray =
                         QJsonDocument::fromJson(reply->readAll()).array();
                     for(const QJsonValue& value : messageArray)
                     {
                         QDiscordMessage m(value.toObject());
                         m.setRest(&rest);
                         list.append(m);
                     }
                     callback(list);
                 });
}

void QDiscordChannel::getMessages(
    QDiscordRest& rest,
    const QDiscordID& channel,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    getMessages(rest, channel, 50, callback);
}

void QDiscordChannel::getMessages(
    int limit,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    if(!_rest)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    if(!_id)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    QDiscordChannel::getMessages(*_rest, _id, limit, callback);
}

void QDiscordChannel::getMessages(
    std::function<void(QList<QDiscordMessage>)> callback)
{
    getMessages(50, callback);
}

void QDiscordChannel::getMessagesAfter(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QDiscordID& message,
    int limit,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::getMessageHistoryAfter(
                     channel, limit, message),
                 [&rest, callback](QNetworkReply* reply) {
                     QList<QDiscordMessage> list;
                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(list);
                         return;
                     }
                     QJsonArray messageArray =
                         QJsonDocument::fromJson(reply->readAll()).array();
                     for(const QJsonValue& value : messageArray)
                     {
                         QDiscordMessage m(value.toObject());
                         m.setRest(&rest);
                         list.append(m);
                     }
                     callback(list);
                 });
}

void QDiscordChannel::getMessagesAfter(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QDiscordID& message,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    getMessagesAfter(rest, channel, message, 50, callback);
}

void QDiscordChannel::getMessagesAfter(
    const QDiscordID& message,
    int limit,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    if(!_rest)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    if(!_id)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    QDiscordChannel::getMessagesAfter(*_rest, _id, message, limit, callback);
}

void QDiscordChannel::getMessagesAfter(
    const QDiscordID& message,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    getMessagesAfter(message, 50, callback);
}

void QDiscordChannel::getMessagesBefore(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QDiscordID& message,
    int limit,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::getMessageHistoryBefore(
                     channel, limit, message),
                 [&rest, callback](QNetworkReply* reply) {
                     QList<QDiscordMessage> list;
                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(list);
                         return;
                     }
                     QJsonArray messageArray =
                         QJsonDocument::fromJson(reply->readAll()).array();
                     for(const QJsonValue& value : messageArray)
                     {
                         QDiscordMessage m(value.toObject());
                         m.setRest(&rest);
                         list.append(m);
                     }
                     callback(list);
                 });
}

void QDiscordChannel::getMessagesBefore(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QDiscordID& message,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    getMessagesBefore(rest, channel, message, 50, callback);
}

void QDiscordChannel::getMessagesBefore(
    const QDiscordID& message,
    int limit,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    if(!_rest)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    if(!_id)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    QDiscordChannel::getMessagesBefore(*_rest, _id, message, limit, callback);
}

void QDiscordChannel::getMessagesBefore(
    const QDiscordID& message,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    getMessagesBefore(message, 50, callback);
}

void QDiscordChannel::getMessagesAround(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QDiscordID& message,
    int limit,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::getMessageHistoryAround(
                     channel, limit, message),
                 [&rest, callback](QNetworkReply* reply) {
                     QList<QDiscordMessage> list;
                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(list);
                         return;
                     }
                     QJsonArray messageArray =
                         QJsonDocument::fromJson(reply->readAll()).array();
                     for(const QJsonValue& value : messageArray)
                     {
                         QDiscordMessage m(value.toObject());
                         m.setRest(&rest);
                         list.append(m);
                     }
                     callback(list);
                 });
}

void QDiscordChannel::getMessagesAround(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QDiscordID& message,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    getMessagesAround(rest, channel, message, 50, callback);
}

void QDiscordChannel::getMessagesAround(
    const QDiscordID& message,
    int limit,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    if(!_rest)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    if(!_id)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    QDiscordChannel::getMessagesAround(*_rest, _id, message, limit, callback);
}

void QDiscordChannel::getMessagesAround(
    const QDiscordID& message,
    std::function<void(QList<QDiscordMessage>)> callback)
{
    getMessagesAround(message, 50, callback);
}

void QDiscordChannel::modify(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QJsonObject& data)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Channels::modifyChannel(channel),
                 data);
}

void QDiscordChannel::modify(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QJsonObject& data,
                             std::function<void(QDiscordChannel)> callback)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Channels::modifyChannel(channel),
                 data,
                 [&rest, callback](QNetworkReply* reply) {
                     QDiscordChannel c;
                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(c);
                         return;
                     }

                     c.deserialize(
                         QJsonDocument::fromJson(reply->readAll()).object());
                     c.setRest(&rest);
                     callback(c);
                 });
}

void QDiscordChannel::modify(const QJsonObject& data)
{
    if(!_rest)
        return;

    if(!_id)
        return;

    QDiscordChannel::modify(*_rest, _id, data);
}

void QDiscordChannel::modify(const QJsonObject& data,
                             std::function<void(QDiscordChannel)> callback)
{
    if(!_rest)
    {
        callback(QDiscordChannel());
        return;
    }

    if(!_id)
    {
        callback(QDiscordChannel());
        return;
    }

    QDiscordChannel::modify(*_rest, _id, data, callback);
}

void QDiscordChannel::modifyName(QDiscordRest& rest,
                                 const QDiscordID& channel,
                                 const QString& name)
{
    QJsonObject data = {{"name", name}};
    modify(rest, channel, data);
}

void QDiscordChannel::modifyName(QDiscordRest& rest,
                                 const QDiscordID& channel,
                                 const QString& name,
                                 std::function<void(QDiscordChannel)> callback)
{
    QJsonObject data = {{"name", name}};
    modify(rest, channel, data, callback);
}

void QDiscordChannel::modifyName(const QString& name)
{
    if(!_rest)
        return;

    if(!_id)
        return;

    QDiscordChannel::modifyName(*_rest, _id, name);
}

void QDiscordChannel::modifyName(const QString& name,
                                 std::function<void(QDiscordChannel)> callback)
{
    if(!_rest)
    {
        callback(QDiscordChannel());
        return;
    }

    if(!_id)
    {
        callback(QDiscordChannel());
        return;
    }

    QDiscordChannel::modifyName(*_rest, _id, name, callback);
}

void QDiscordChannel::modifyPosition(QDiscordRest& rest,
                                     const QDiscordID& channel,
                                     int position)
{
    QJsonObject data = {{"position", position}};
    modify(rest, channel, data);
}

void QDiscordChannel::modifyPosition(
    QDiscordRest& rest,
    const QDiscordID& channel,
    int position,
    std::function<void(QDiscordChannel)> callback)
{
    QJsonObject data = {{"position", position}};
    modify(rest, channel, data, callback);
}

void QDiscordChannel::modifyPosition(int position)
{
    if(!_rest)
        return;

    if(!_id)
        return;

    QDiscordChannel::modifyPosition(*_rest, _id, position);
}

void QDiscordChannel::modifyPosition(
    int position,
    std::function<void(QDiscordChannel)> callback)
{
    if(!_rest)
    {
        callback(QDiscordChannel());
        return;
    }

    if(!_id)
    {
        callback(QDiscordChannel());
        return;
    }

    QDiscordChannel::modifyPosition(*_rest, _id, position, callback);
}

void QDiscordChannel::modifyTopic(QDiscordRest& rest,
                                  const QDiscordID& channel,
                                  const QString& topic)
{
    QJsonObject data = {{"topic", topic}};
    modify(rest, channel, data);
}

void QDiscordChannel::modifyTopic(QDiscordRest& rest,
                                  const QDiscordID& channel,
                                  const QString& topic,
                                  std::function<void(QDiscordChannel)> callback)
{
    QJsonObject data = {{"topic", topic}};
    modify(rest, channel, data, callback);
}

void QDiscordChannel::modifyTopic(const QString& topic)
{
    if(!_rest)
        return;

    if(!_id)
        return;

    QDiscordChannel::modifyTopic(*_rest, _id, topic);
}

void QDiscordChannel::modifyTopic(const QString& topic,
                                  std::function<void(QDiscordChannel)> callback)
{
    if(!_rest)
    {
        callback(QDiscordChannel());
        return;
    }

    if(!_id)
    {
        callback(QDiscordChannel());
        return;
    }

    QDiscordChannel::modifyTopic(*_rest, _id, topic, callback);
}

void QDiscordChannel::modifyBitrate(QDiscordRest& rest,
                                    const QDiscordID& channel,
                                    int bitrate)
{
    QJsonObject data = {{"bitrate", bitrate}};
    modify(rest, channel, data);
}

void QDiscordChannel::modifyBitrate(
    QDiscordRest& rest,
    const QDiscordID& channel,
    int bitrate,
    std::function<void(QDiscordChannel)> callback)
{
    QJsonObject data = {{"bitrate", bitrate}};
    modify(rest, channel, data, callback);
}

void QDiscordChannel::modifyBitrate(int bitrate)
{
    if(!_rest)
        return;

    if(!_id)
        return;

    QDiscordChannel::modifyBitrate(*_rest, _id, bitrate);
}

void QDiscordChannel::modifyBitrate(
    int bitrate,
    std::function<void(QDiscordChannel)> callback)
{
    if(!_rest)
    {
        callback(QDiscordChannel());
        return;
    }

    if(!_id)
    {
        callback(QDiscordChannel());
        return;
    }

    QDiscordChannel::modifyBitrate(*_rest, _id, bitrate, callback);
}

void QDiscordChannel::modifyUserLimit(QDiscordRest& rest,
                                      const QDiscordID& channel,
                                      int userLimit)
{
    QJsonObject data = {{"user_limit", userLimit}};
    modify(rest, channel, data);
}

void QDiscordChannel::modifyUserLimit(
    QDiscordRest& rest,
    const QDiscordID& channel,
    int userLimit,
    std::function<void(QDiscordChannel)> callback)
{
    QJsonObject data = {{"user_limit", userLimit}};
    modify(rest, channel, data, callback);
}

void QDiscordChannel::modifyUserLimit(int userLimit)
{
    if(!_rest)
        return;

    if(!_id)
        return;

    QDiscordChannel::modifyUserLimit(*_rest, _id, userLimit);
}

void QDiscordChannel::modifyUserLimit(
    int userLimit,
    std::function<void(QDiscordChannel)> callback)
{
    if(!_rest)
    {
        callback(QDiscordChannel());
        return;
    }

    if(!_id)
    {
        callback(QDiscordChannel());
        return;
    }

    QDiscordChannel::modifyUserLimit(*_rest, _id, userLimit, callback);
}

void QDiscordChannel::remove(QDiscordRest& rest, const QDiscordID& channel)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Channels::deleteChannel(channel));
}

void QDiscordChannel::remove(QDiscordRest& rest,
                             const QDiscordID& channel,
                             std::function<void(QDiscordChannel)> callback)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Channels::deleteChannel(channel),
                 [&rest, callback](QNetworkReply* reply) {
                     QDiscordChannel c;
                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(c);
                         return;
                     }

                     c.deserialize(
                         QJsonDocument::fromJson(reply->readAll()).object());
                     c.setRest(&rest);
                     callback(c);
                 });
}

void QDiscordChannel::remove()
{
    if(!_rest)
        return;

    if(!_id)
        return;

    QDiscordChannel::remove(*_rest, _id);
}

void QDiscordChannel::remove(std::function<void(QDiscordChannel)> callback)
{
    if(!_rest)
    {
        callback(QDiscordChannel());
        return;
    }

    if(!_id)
    {
        callback(QDiscordChannel());
        return;
    }

    QDiscordChannel::remove(*_rest, _id, callback);
}

QSharedPointer<QDiscordChannel>
QDiscordChannel::fromJson(const QJsonObject& object)
{
    QSharedPointer<QDiscordChannel> channel(new QDiscordChannel());
    channel->deserialize(object);
    return channel;
}

QDiscordChannel::QDiscordChannel(const QJsonObject& object)
{
    deserialize(object);
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordChannel(" << this << ") constructed";
#endif
}

QDiscordChannel::QDiscordChannel()
{
    _position = -1;
    _type = Type::UnknownType;
    _bitrate = -1;
    _userLimit = -1;
    _rest = nullptr;

#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordChannel(" << this << ") constructed";
#endif
}

QDiscordChannel::~QDiscordChannel()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordChannel(" << this << ") destroyed";
#endif
}

void QDiscordChannel::deserialize(const QJsonObject& object)
{
    _id = QDiscordID(object["id"].toString());
    _type = static_cast<Type>(object["type"].toInt(255));
    _name = object["name"].toString();

    switch(_type)
    {
    case Type::Category:
    case Type::Text:
    case Type::Voice:
        _guildId = QDiscordID(object["guild_id"].toString());
        _position = object["position"].toInt(-1);
        break;
    case Type::DirectMessage:
    case Type::GroupDirectMessage:
    {
        _icon = object["icon"].toString();
        QList<QSharedPointer<QDiscordUser>> users;
        for(QJsonValue recipient : object["recipients"].toArray())
            users.append(QDiscordUser::fromJson(recipient.toObject()));
        _recipients = users;
        _ownerId = QDiscordID(object["owner_id"].toString());
        _applicationId = QDiscordID(object["application_id"].toString());
    }
    default:;
    }

    if(_type == Type::Text)
    {
        _topic = object["topic"].toString();
        _lastMessageId = QDiscordID(object["last_message_id"].toString());
    }
    if(_type == Type::Voice)
    {
        _bitrate = object["bitrate"].toInt(-1);
        _userLimit = object["user_limit"].toInt(-1);
    }
}

QJsonObject QDiscordChannel::serialize() const
{
    QJsonObject object;

    object["id"] = _id.toString();
    object["type"] = static_cast<int>(_type);
    object["name"] = _name;

    switch(_type)
    {
    case Type::Category:
    case Type::Text:
    case Type::Voice:
        object["guild_id"] = _guildId.toString();
        object["position"] = _position;
        break;
    case Type::DirectMessage:
    case Type::GroupDirectMessage:
    {
        if(!_icon.isEmpty())
            object["icon"] = _icon;
        QJsonArray recipientArray;
        QList<QSharedPointer<QDiscordUser>> users = _recipients;
        for(QSharedPointer<QDiscordUser> user : users)
        {
            QJsonObject jsonUser = user->serialize();
            if(jsonUser["mfa_enabled"].toBool(false) == false)
                jsonUser.remove("mfa_enabled");
            if(jsonUser["bot"].toBool(false) == false)
                jsonUser.remove("bot");
            recipientArray.append(jsonUser);
        }
        object["recipients"] = recipientArray;
        object["owner_id"] = _ownerId ? _ownerId.toString() : QJsonValue();
        object["application_id"] =
            _applicationId ? _applicationId.toString() : QJsonValue();
    }
    default:;
    }

    if(_type == Type::Text)
    {
        object["topic"] = _topic;
        object["last_message_id"] =
            _lastMessageId ? _lastMessageId.toString() : QJsonValue();
    }
    if(_type == Type::Voice)
    {
        object["bitrate"] = _bitrate;
        object["user_limit"] = _userLimit;
    }

    return object;
}

void QDiscordChannel::setGuild(QSharedPointer<QDiscordGuild> guild)
{
    _guild = guild;
    if(!_guild)
    {
        _guildId = QDiscordID();
        return;
    }
    _guildId = guild->id();
}

bool QDiscordChannel::operator==(const QDiscordChannel& other) const
{
    return _id == other._id;
}

bool QDiscordChannel::operator!=(const QDiscordChannel& other) const
{
    return !operator==(other);
}

bool QDiscordChannel::operator>(const QDiscordChannel& other) const
{
    return _id > other._id;
}

bool QDiscordChannel::operator<(const QDiscordChannel& other) const
{
    return _id < other._id;
}

bool QDiscordChannel::operator<=(const QDiscordChannel& other) const
{
    return _id <= other._id;
}

bool QDiscordChannel::operator>=(const QDiscordChannel& other) const
{
    return _id >= other._id;
}

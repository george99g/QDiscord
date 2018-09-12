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

#include "qdiscord.d/models/qdiscordchannel.hpp"
#include "qdiscord.d/models/qdiscordguild.hpp"
#include "qdiscord.d/models/qdiscordmessage.hpp"
#include "qdiscord.d/qdiscordrest.hpp"

void QDiscordChannel::get(QDiscordRest& rest,
                          const QDiscordID& channel,
                          const std::function<void(QDiscordChannel)>& callback)
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

void QDiscordChannel::getPrivateChannels(
    QDiscordRest& rest,
    const std::function<void(QList<QDiscordChannel>)>& callback)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Self::getPrivateChannels(),
                 [&rest, callback](QNetworkReply* reply) {
                     QList<QDiscordChannel> channelList;
                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(channelList);
                         return;
                     }
                     QJsonArray array =
                         QJsonDocument::fromJson(reply->readAll()).array();
                     for(const QJsonValueRef& v : array)
                     {
                         QDiscordChannel channel(v.toObject());
                         channel.setRest(&rest);
                         channelList.append(channel);
                     }
                     callback(channelList);
                 });
}

void QDiscordChannel::getMessage(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QDiscordID& message,
    const std::function<void(QDiscordMessage)>& callback)
{
    QDiscordMessage::get(rest, channel, message, callback);
}

void QDiscordChannel::getMessage(
    const QDiscordID& message,
    const std::function<void(QDiscordMessage)>& callback)
{
    if(!_rest || !_id)
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
    const std::function<void(QList<QDiscordMessage>)>& callback)
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
                     for(const QJsonValueRef& value : messageArray)
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
    const std::function<void(QList<QDiscordMessage>)>& callback)
{
    getMessages(rest, channel, 50, callback);
}

void QDiscordChannel::getMessages(
    int limit,
    const std::function<void(QList<QDiscordMessage>)>& callback)
{
    if(!_rest || !_id)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    QDiscordChannel::getMessages(*_rest, _id, limit, callback);
}

void QDiscordChannel::getMessages(
    const std::function<void(QList<QDiscordMessage>)>& callback)
{
    getMessages(50, callback);
}

void QDiscordChannel::getMessagesAfter(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QDiscordID& message,
    int limit,
    const std::function<void(QList<QDiscordMessage>)>& callback)
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
                     for(const QJsonValueRef& value : messageArray)
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
    const std::function<void(QList<QDiscordMessage>)>& callback)
{
    getMessagesAfter(rest, channel, message, 50, callback);
}

void QDiscordChannel::getMessagesAfter(
    const QDiscordID& message,
    int limit,
    const std::function<void(QList<QDiscordMessage>)>& callback)
{
    if(!_rest || !_id)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    QDiscordChannel::getMessagesAfter(*_rest, _id, message, limit, callback);
}

void QDiscordChannel::getMessagesAfter(
    const QDiscordID& message,
    const std::function<void(QList<QDiscordMessage>)>& callback)
{
    getMessagesAfter(message, 50, callback);
}

void QDiscordChannel::getMessagesBefore(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QDiscordID& message,
    int limit,
    const std::function<void(QList<QDiscordMessage>)>& callback)
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
                     for(const QJsonValueRef& value : messageArray)
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
    const std::function<void(QList<QDiscordMessage>)>& callback)
{
    getMessagesBefore(rest, channel, message, 50, callback);
}

void QDiscordChannel::getMessagesBefore(
    const QDiscordID& message,
    int limit,
    const std::function<void(QList<QDiscordMessage>)>& callback)
{
    if(!_rest || !_id)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    QDiscordChannel::getMessagesBefore(*_rest, _id, message, limit, callback);
}

void QDiscordChannel::getMessagesBefore(
    const QDiscordID& message,
    const std::function<void(QList<QDiscordMessage>)>& callback)
{
    getMessagesBefore(message, 50, callback);
}

void QDiscordChannel::getMessagesAround(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QDiscordID& message,
    int limit,
    const std::function<void(QList<QDiscordMessage>)>& callback)
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
                     for(const QJsonValueRef& value : messageArray)
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
    const std::function<void(QList<QDiscordMessage>)>& callback)
{
    getMessagesAround(rest, channel, message, 50, callback);
}

void QDiscordChannel::getMessagesAround(
    const QDiscordID& message,
    int limit,
    const std::function<void(QList<QDiscordMessage>)>& callback)
{
    if(!_rest || !_id)
    {
        callback(QList<QDiscordMessage>());
        return;
    }

    QDiscordChannel::getMessagesAround(*_rest, _id, message, limit, callback);
}

void QDiscordChannel::getMessagesAround(
    const QDiscordID& message,
    const std::function<void(QList<QDiscordMessage>)>& callback)
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

void QDiscordChannel::modify(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QJsonObject& data,
    const std::function<void(QDiscordChannel)>& callback)
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
    if(!_rest || !_id)
        return;

    QDiscordChannel::modify(*_rest, _id, data);
}

void QDiscordChannel::modify(
    const QJsonObject& data,
    const std::function<void(QDiscordChannel)>& callback)
{
    if(!_rest || !_id)
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

void QDiscordChannel::modifyName(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QString& name,
    const std::function<void(QDiscordChannel)>& callback)
{
    QJsonObject data = {{"name", name}};
    modify(rest, channel, data, callback);
}

void QDiscordChannel::modifyName(const QString& name)
{
    if(!_rest || !_id)
        return;

    QDiscordChannel::modifyName(*_rest, _id, name);
}

void QDiscordChannel::modifyName(
    const QString& name,
    const std::function<void(QDiscordChannel)>& callback)
{
    if(!_rest || !_id)
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
    const std::function<void(QDiscordChannel)>& callback)
{
    QJsonObject data = {{"position", position}};
    modify(rest, channel, data, callback);
}

void QDiscordChannel::modifyPosition(int position)
{
    if(!_rest || !_id)
        return;

    QDiscordChannel::modifyPosition(*_rest, _id, position);
}

void QDiscordChannel::modifyPosition(
    int position,
    const std::function<void(QDiscordChannel)>& callback)
{
    if(!_rest || !_id)
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

void QDiscordChannel::modifyTopic(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const QString& topic,
    const std::function<void(QDiscordChannel)>& callback)
{
    QJsonObject data = {{"topic", topic}};
    modify(rest, channel, data, callback);
}

void QDiscordChannel::modifyTopic(const QString& topic)
{
    if(!_rest || !_id)
        return;

    QDiscordChannel::modifyTopic(*_rest, _id, topic);
}

void QDiscordChannel::modifyTopic(
    const QString& topic,
    const std::function<void(QDiscordChannel)>& callback)
{
    if(!_rest || !_id)
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
    const std::function<void(QDiscordChannel)>& callback)
{
    QJsonObject data = {{"bitrate", bitrate}};
    modify(rest, channel, data, callback);
}

void QDiscordChannel::modifyBitrate(int bitrate)
{
    if(!_rest || !_id)
        return;

    QDiscordChannel::modifyBitrate(*_rest, _id, bitrate);
}

void QDiscordChannel::modifyBitrate(
    int bitrate,
    const std::function<void(QDiscordChannel)>& callback)
{
    if(!_rest || !_id)
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
    const std::function<void(QDiscordChannel)>& callback)
{
    QJsonObject data = {{"user_limit", userLimit}};
    modify(rest, channel, data, callback);
}

void QDiscordChannel::modifyUserLimit(int userLimit)
{
    if(!_rest || !_id)
        return;

    QDiscordChannel::modifyUserLimit(*_rest, _id, userLimit);
}

void QDiscordChannel::modifyUserLimit(
    int userLimit,
    const std::function<void(QDiscordChannel)>& callback)
{
    if(!_rest || !_id)
    {
        callback(QDiscordChannel());
        return;
    }

    QDiscordChannel::modifyUserLimit(*_rest, _id, userLimit, callback);
}

void QDiscordChannel::triggerTyping(QDiscordRest& rest,
                                    const QDiscordID& channel)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Channels::sendTyping(channel));
}

void QDiscordChannel::triggerTyping(QDiscordRest& rest,
                                    const QDiscordID& channel,
                                    const std::function<void(bool)>& callback)
{
    rest.request(
        QNetworkRequest(),
        QDiscordRoutes::Channels::sendTyping(channel),
        [callback](QNetworkReply* reply) { callback(reply->error() == 204); });
}

void QDiscordChannel::triggerTyping()
{
    if(!_rest || !_id)
        return;

    QDiscordChannel::triggerTyping(*_rest, _id);
}

void QDiscordChannel::triggerTyping(const std::function<void(bool)>& callback)
{
    if(!_rest || !_id)
    {
        callback(false);
        return;
    }

    QDiscordChannel::triggerTyping(*_rest, _id, callback);
}

void QDiscordChannel::remove(QDiscordRest& rest, const QDiscordID& channel)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Channels::deleteChannel(channel));
}

void QDiscordChannel::remove(
    QDiscordRest& rest,
    const QDiscordID& channel,
    const std::function<void(QDiscordChannel)>& callback)
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
    if(!_rest || !_id)
        return;

    QDiscordChannel::remove(*_rest, _id);
}

void QDiscordChannel::remove(
    const std::function<void(QDiscordChannel)>& callback)
{
    if(!_rest || !_id)
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
}

void QDiscordChannel::deserialize(const QJsonObject& object)
{
    deserializeJson(object);
}

QJsonObject QDiscordChannel::serialize() const
{
    return serializeJson();
}

void QDiscordChannel::setGuild(const QSharedPointer<QDiscordGuild>& guild)
{
    _guild = guild;
    if(!_guild)
    {
        _guildId = QDiscordID();
        return;
    }
    _guildId = guild->id();
}

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action,
                          QDiscordChannel::Type& value,
                          const QString& name)
{
    value = static_cast<QDiscordChannel::Type>(action.data()[name].toInt(255));
}

template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action,
                          const QDiscordChannel::Type& value,
                          const QString& name)
{
    action.data().insert(name, static_cast<int>(value));
}

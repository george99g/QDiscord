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

#include "qdiscordstate.hpp"
#include "qdiscordrest.hpp"

QDiscordState::QDiscordState(QObject* parent)
    : QDiscordAbstractState(parent)
{
    _rest = nullptr;
}

QDiscordState::~QDiscordState() {}

void QDiscordState::readyReceived(const QJsonObject& object)
{
    _protocolVersion = object["v"].toInt(-1);
    _user = QDiscordUser::fromJson(object["user"].toObject());
    if(_rest)
        _user->setRest(_rest);
    emit selfCreated(_user);
    for(QJsonValue item : object["guilds"].toArray())
        guildCreateReceived(item.toObject());
    for(QJsonValue item : object["private_channels"].toArray())
        channelCreateReceived(item.toObject());
}

void QDiscordState::channelCreateReceived(const QJsonObject& object)
{
    QSharedPointer<QDiscordChannel> channel = QDiscordChannel::fromJson(object);
    if(_rest)
        channel->setRest(_rest);
    if(channel->type() == QDiscordChannel::Type::DirectMessage
       || channel->type() == QDiscordChannel::Type::GroupDirectMessage)
    {
        _dmChannels.insert(channel->id(), channel);
    }
    else
    {
        channel->setGuild(guild(channel->guildId()));
        if(!channel->guild())
            return;
        channel->guild()->addChannel(channel);
    }
    emit channelCreated(channel);
}

void QDiscordState::channelUpdateReceived(const QJsonObject& object)
{
    QSharedPointer<QDiscordChannel> channel = QDiscordChannel::fromJson(object);
    if(_rest)
        channel->setRest(_rest);
    channel->setGuild(guild(channel->guildId()));
    if(channel->guild())
        channel->guild()->addChannel(channel);
    emit channelUpdated(channel);
}

void QDiscordState::channelDeleteReceived(const QJsonObject& object)
{
    QSharedPointer<QDiscordChannel> channel = QDiscordChannel::fromJson(object);
    if(_rest)
        channel->setRest(_rest);
    if(channel->type() == QDiscordChannel::Type::DirectMessage
       || channel->type() == QDiscordChannel::Type::GroupDirectMessage)
    {
        _dmChannels.remove(channel->id());
    }
    else
    {
        channel->setGuild(guild(channel->guildId()));
        if(channel->guild())
            channel->guild()->removeChannel(channel->id());
    }
    emit channelDeleted(channel);
}

void QDiscordState::guildCreateReceived(const QJsonObject& object)
{
    QSharedPointer<QDiscordGuild> guild = QDiscordGuild::fromJson(object);
    if(_rest)
        guild->setRest(_rest);
    _guilds.insert(guild->id(), guild);
    if(guild->unavailable())
        emit guildCreated(guild);
    else
        emit guildAvailable(guild);
}

void QDiscordState::guildUpdateReceived(const QJsonObject& object)
{
    QSharedPointer<QDiscordGuild> newGuild = QDiscordGuild::fromJson(object);
    QSharedPointer<QDiscordGuild> oldGuild = guild(newGuild->id());
    if(oldGuild)
    {
        oldGuild->update(object);
        if(_rest)
            oldGuild->setRest(_rest);
        emit guildUpdated(oldGuild);
    }
}

void QDiscordState::guildDeleteReceived(const QJsonObject& object)
{
    QSharedPointer<QDiscordGuild> guild = QDiscordGuild::fromJson(object);
    if(_rest)
        guild->setRest(_rest);
    _guilds.remove(guild->id());
    if(guild->unavailable())
        emit guildUnavailable(guild);
    else
        emit guildDeleted(guild);
}

void QDiscordState::guildBanAddReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::guildBanRemoveReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::guildEmojisUpdateReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::guildIntegrationsUpdateReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::guildMemberAddReceived(const QJsonObject& object)
{
    QSharedPointer<QDiscordMember> member = QDiscordMember::fromJson(object);
    if(_rest)
        member->user().setRest(_rest);
    QDiscordID guildId = QDiscordID(object["guild_id"].toString());
    member->setGuild(guild(guildId));
    if(!member->guild())
        return;
    member->guild()->addMember(member);
    emit guildMemberAdded(member);
}

void QDiscordState::guildMemberRemoveReceived(const QJsonObject& object)
{
    QSharedPointer<QDiscordMember> member = QDiscordMember::fromJson(object);
    if(_rest)
        member->user().setRest(_rest);
    QDiscordID guildId = QDiscordID(object["guild_id"].toString());
    member->setGuild(guild(guildId));
    if(!member->guild())
        return;
    QSharedPointer<QDiscordMember> oldMember =
        member->guild()->member(member->user().id());
    if(!oldMember)
        return;
    member->guild()->removeMember(member->user().id());
    emit guildMemberRemoved(oldMember);
}

void QDiscordState::guildMemberUpdateReceived(const QJsonObject& object)
{
    QSharedPointer<QDiscordMember> member = QDiscordMember::fromJson(object);
    if(_rest)
        member->user().setRest(_rest);
    QDiscordID guildId = QDiscordID(object["guild_id"].toString());
    member->setGuild(guild(guildId));
    if(!member->guild())
        return;
    QSharedPointer<QDiscordMember> oldMember =
        member->guild()->member(member->user().id());
    if(!oldMember)
        return;
    oldMember->update(object);
    emit guildMemberUpdated(oldMember);
}

void QDiscordState::guildMembersChunkReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::guildRoleCreateReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::guildRoleUpdateReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::guildRoleDeleteReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::messageCreateReceived(const QJsonObject& object)
{
    QDiscordMessage message(object);
    if(_rest)
        message.setRest(_rest);
    message.setChannel(channel(message.channelId()));
    emit messageCreated(message);
}

void QDiscordState::messageUpdateReceived(const QJsonObject& object)
{
    QDiscordMessage message(object);
    if(_rest)
        message.setRest(_rest);
    message.setChannel(channel(message.channelId()));
    emit messageUpdated(message);
}

void QDiscordState::messageDeleteReceived(const QJsonObject& object)
{
    QDiscordMessage message(object);
    if(_rest)
        message.setRest(_rest);
    message.setChannel(channel(message.channelId()));
    emit messageDeleted(message);
}

void QDiscordState::messageDeleteBulkReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::presenceUpdateReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::typingStartReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::userUpdateReceived(const QJsonObject& object)
{
    QSharedPointer<QDiscordUser> user = QDiscordUser::fromJson(object);
    if(_rest)
        user->setRest(_rest);
    _user = user;
    emit selfUpdated(user);
}

void QDiscordState::voiceStateUpdateReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::voiceServerUpdateReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::reset()
{
    _protocolVersion = -1;
    _user = QSharedPointer<QDiscordUser>();
    _dmChannels.clear();
    _guilds.clear();
}

QSharedPointer<QDiscordChannel> QDiscordState::channel(QDiscordID id) const
{
    QSharedPointer<QDiscordChannel> channel;
    if((channel = dmChannel(id)))
        return channel;
    for(QSharedPointer<QDiscordGuild> guild : _guilds.values())
    {
        if((channel = guild->channel(id)))
            return channel;
    }
    return nullptr;
}

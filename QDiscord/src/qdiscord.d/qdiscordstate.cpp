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
}

QDiscordState::~QDiscordState() {}

void QDiscordState::readyReceived(int protocolVersion,
                                  QSharedPointer<QDiscordUser> user)
{
    _protocolVersion = protocolVersion;
    _user = user;
    if(_rest)
        _user->setRest(_rest);
    emit selfCreated(_user);
}

void QDiscordState::channelCreateReceived(
    QSharedPointer<QDiscordChannel> channel)
{
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

void QDiscordState::channelUpdateReceived(
    QSharedPointer<QDiscordChannel> channel)
{
    if(_rest)
        channel->setRest(_rest);
    channel->setGuild(guild(channel->guildId()));
    if(channel->guild())
        channel->guild()->addChannel(channel);
    emit channelUpdated(channel);
}

void QDiscordState::channelDeleteReceived(
    QSharedPointer<QDiscordChannel> channel)
{
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

void QDiscordState::guildCreateReceived(QSharedPointer<QDiscordGuild> guild)
{
    if(_rest)
        guild->setRest(_rest);
    _guilds.insert(guild->id(), guild);
    if(!guild->unavailable().has_value() || guild->unavailable().value())
        emit guildCreated(guild);
    else
        emit guildAvailable(guild);
}

void QDiscordState::guildUpdateReceived(QSharedPointer<QDiscordGuild> guild)
{
    QSharedPointer<QDiscordGuild> oldGuild = QDiscordState::guild(guild->id());
    if(oldGuild)
    {
        oldGuild->update(*guild);
        if(_rest)
            oldGuild->setRest(_rest);
        emit guildUpdated(oldGuild);
    }
}

void QDiscordState::guildDeleteReceived(QSharedPointer<QDiscordGuild> guild)
{
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

void QDiscordState::guildMemberAddReceived(
    QSharedPointer<QDiscordMember> member,
    QDiscordID guildId)
{
    if(_rest)
        member->user().setRest(_rest);
    member->setGuild(guild(guildId));
    if(!member->guild())
        return;
    member->guild()->addMember(member);
    emit guildMemberAdded(member);
}

void QDiscordState::guildMemberRemoveReceived(
    QSharedPointer<QDiscordMember> member,
    QDiscordID guildId)
{
    if(_rest)
        member->user().setRest(_rest);
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

void QDiscordState::guildMemberUpdateReceived(
    QSharedPointer<QDiscordMember> member,
    QDiscordID guildId)
{
    if(_rest)
        member->user().setRest(_rest);
    member->setGuild(guild(guildId));
    if(!member->guild())
        return;
    QSharedPointer<QDiscordMember> oldMember =
        member->guild()->member(member->user().id());
    if(!oldMember)
        return;
    oldMember->update(*member);
    emit guildMemberUpdated(oldMember);
}

void QDiscordState::guildMembersChunkReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordState::guildRoleCreateReceived(QSharedPointer<QDiscordRole> role,
                                            QDiscordID guildId)
{
    if(_rest)
        role->setRest(_rest);
    role->setGuild(guild(guildId));
    if(!role->guild())
        return;
    role->guild()->addRole(role);
    emit guildRoleCreated(role);
}

void QDiscordState::guildRoleUpdateReceived(QSharedPointer<QDiscordRole> role,
                                            QDiscordID guildId)
{
    if(_rest)
        role->setRest(_rest);
    role->setGuild(guild(guildId));
    if(!role->guild())
        return;
    role->guild()->addRole(role);
    emit guildRoleUpdated(role);
}

void QDiscordState::guildRoleDeleteReceived(QDiscordID roleId,
                                            QDiscordID guildId)
{
    QSharedPointer<QDiscordGuild> guild = QDiscordState::guild(guildId);
    if(!guild)
        return;
    QSharedPointer<QDiscordRole> role = guild->role(roleId);
    if(!role)
        return;
    guild->removeRole(role);
    emit guildRoleDeleted(role);
}

void QDiscordState::messageCreateReceived(QDiscordMessage message)
{
    if(_rest)
        message.setRest(_rest);
    message.setChannel(channel(message.channelId()));
    emit messageCreated(message);
}

void QDiscordState::messageUpdateReceived(QDiscordMessage message)
{
    if(_rest)
        message.setRest(_rest);
    message.setChannel(channel(message.channelId()));
    emit messageUpdated(message);
}

void QDiscordState::messageDeleteReceived(QDiscordMessage message)
{
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

void QDiscordState::userUpdateReceived(QSharedPointer<QDiscordUser> user)
{
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

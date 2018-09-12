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

#include "qdiscord.d/qdiscordjsondecoder.hpp"

const QMap<QString, void (QDiscordJsonDecoder::*)(const QJsonObject&)>
    QDiscordJsonDecoder::_dispatchTable = {
        {"READY", &QDiscordJsonDecoder::readyReceived},
        {"CHANNEL_CREATE", &QDiscordJsonDecoder::channelCreateReceived},
        {"CHANNEL_UPDATE", &QDiscordJsonDecoder::channelUpdateReceived},
        {"CHANNEL_DELETE", &QDiscordJsonDecoder::channelDeleteReceived},
        {"GUILD_CREATE", &QDiscordJsonDecoder::guildCreateReceived},
        {"GUILD_UPDATE", &QDiscordJsonDecoder::guildUpdateReceived},
        {"GUILD_DELETE", &QDiscordJsonDecoder::guildDeleteReceived},
        {"GUILD_BAN_ADD", &QDiscordJsonDecoder::guildBanAddReceived},
        {"GUILD_BAN_REMOVE", &QDiscordJsonDecoder::guildBanRemoveReceived},
        {"GUILD_EMOJIS_UPDATE",
         &QDiscordJsonDecoder::guildEmojisUpdateReceived},
        {"GUILD_INTEGRATIONS_UPDATE",
         &QDiscordJsonDecoder::guildIntegrationsUpdateReceived},
        {"GUILD_MEMBER_ADD", &QDiscordJsonDecoder::guildMemberAddReceived},
        {"GUILD_MEMBER_REMOVE",
         &QDiscordJsonDecoder::guildMemberRemoveReceived},
        {"GUILD_MEMBER_UPDATE",
         &QDiscordJsonDecoder::guildMemberUpdateReceived},
        {"GUILD_MEMBERS_CHUNK",
         &QDiscordJsonDecoder::guildMembersChunkReceived},
        {"GUILD_ROLE_CREATE", &QDiscordJsonDecoder::guildRoleCreateReceived},
        {"GUILD_ROLE_UPDATE", &QDiscordJsonDecoder::guildRoleUpdateReceived},
        {"GUILD_ROLE_DELETE", &QDiscordJsonDecoder::guildRoleDeleteReceived},
        {"MESSAGE_CREATE", &QDiscordJsonDecoder::messageCreateReceived},
        {"MESSAGE_UPDATE", &QDiscordJsonDecoder::messageUpdateReceived},
        {"MESSAGE_DELETE", &QDiscordJsonDecoder::messageDeleteReceived},
        {"MESSSAGE_DELETE_BULK",
         &QDiscordJsonDecoder::messageDeleteBulkReceived},
        {"PRESENCE_UPDATE", &QDiscordJsonDecoder::presenceUpdateReceived},
        {"TYPING_START", &QDiscordJsonDecoder::typingStartReceived},
        {"USER_UPDATE", &QDiscordJsonDecoder::userUpdateReceived},
        {"VOICE_STATE_UPDATE", &QDiscordJsonDecoder::voiceStateUpdateReceived},
        {"VOICE_SERVER_UPDATE",
         &QDiscordJsonDecoder::voiceServerUpdateReceived},
};

QDiscordJsonDecoder::QDiscordJsonDecoder(QObject* parent)
    : QObject(parent)
{
}

void QDiscordJsonDecoder::input(const QJsonObject& d, const QString& t)
{
    if(!_state)
        return;
    if(_dispatchTable.contains(t))
        (this->*_dispatchTable[t])(d);
    else
        qCDebug(STATE, ) << "No dispatch table entry found for" << t;
}

void QDiscordJsonDecoder::readyReceived(const QJsonObject& object)
{
    if(_state)
        _state->readyReceived(
            object["v"].toInt(-1),
            QDiscordUser::fromJson(object["user"].toObject()));

    for(const QJsonValueRef& item : object["guilds"].toArray())
        guildCreateReceived(item.toObject());

    for(const QJsonValueRef& item : object["private_channels"].toArray())
        channelCreateReceived(item.toObject());
}

void QDiscordJsonDecoder::channelCreateReceived(const QJsonObject& object)
{
    if(_state)
        _state->channelCreateReceived(QDiscordChannel::fromJson(object));
}

void QDiscordJsonDecoder::channelUpdateReceived(const QJsonObject& object)
{
    if(_state)
        _state->channelUpdateReceived(QDiscordChannel::fromJson(object));
}

void QDiscordJsonDecoder::channelDeleteReceived(const QJsonObject& object)
{
    if(_state)
        _state->channelDeleteReceived(QDiscordChannel::fromJson(object));
}

void QDiscordJsonDecoder::guildCreateReceived(const QJsonObject& object)
{
    if(_state)
        _state->guildCreateReceived(QDiscordGuild::fromJson(object));
}

void QDiscordJsonDecoder::guildUpdateReceived(const QJsonObject& object)
{
    if(_state)
        _state->guildUpdateReceived(QDiscordGuild::fromJson(object));
}

void QDiscordJsonDecoder::guildDeleteReceived(const QJsonObject& object)
{
    if(_state)
        _state->guildDeleteReceived(QDiscordGuild::fromJson(object));
}

void QDiscordJsonDecoder::guildBanAddReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordJsonDecoder::guildBanRemoveReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordJsonDecoder::guildEmojisUpdateReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordJsonDecoder::guildIntegrationsUpdateReceived(
    const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordJsonDecoder::guildMemberAddReceived(const QJsonObject& object)
{
    if(_state)
    {
        _state->guildMemberAddReceived(
            QDiscordMember::fromJson(object),
            QDiscordID(object["guild_id"].toString()));
    }
}

void QDiscordJsonDecoder::guildMemberRemoveReceived(const QJsonObject& object)
{
    if(_state)
    {
        _state->guildMemberRemoveReceived(
            QDiscordMember::fromJson(object),
            QDiscordID(object["guild_id"].toString()));
    }
}

void QDiscordJsonDecoder::guildMemberUpdateReceived(const QJsonObject& object)
{
    if(_state)
    {
        _state->guildMemberUpdateReceived(
            QDiscordMember::fromJson(object),
            QDiscordID(object["guild_id"].toString()));
    }
}

void QDiscordJsonDecoder::guildMembersChunkReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordJsonDecoder::guildRoleCreateReceived(const QJsonObject& object)
{
    if(_state)
    {
        _state->guildRoleCreateReceived(
            QDiscordRole::fromJson(object),
            QDiscordID(object["guild_id"].toString()));
    }
}

void QDiscordJsonDecoder::guildRoleUpdateReceived(const QJsonObject& object)
{
    if(_state)
    {
        _state->guildRoleUpdateReceived(
            QDiscordRole::fromJson(object),
            QDiscordID(object["guild_id"].toString()));
    }
}

void QDiscordJsonDecoder::guildRoleDeleteReceived(const QJsonObject& object)
{
    if(_state)
    {
        _state->guildRoleDeleteReceived(
            QDiscordID(object["role_id"].toString()),
            QDiscordID(object["guild_id"].toString()));
    }
}

void QDiscordJsonDecoder::messageCreateReceived(const QJsonObject& object)
{
    if(_state)
        _state->messageCreateReceived(QDiscordMessage(object));
}

void QDiscordJsonDecoder::messageUpdateReceived(const QJsonObject& object)
{
    if(_state)
        _state->messageUpdateReceived(QDiscordMessage(object));
}

void QDiscordJsonDecoder::messageDeleteReceived(const QJsonObject& object)
{
    if(_state)
        _state->messageDeleteReceived(QDiscordMessage(object));
}

void QDiscordJsonDecoder::messageDeleteBulkReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordJsonDecoder::presenceUpdateReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordJsonDecoder::typingStartReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordJsonDecoder::userUpdateReceived(const QJsonObject& object)
{
    if(_state)
        _state->userUpdateReceived(QDiscordUser::fromJson(object));
}

void QDiscordJsonDecoder::voiceStateUpdateReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

void QDiscordJsonDecoder::voiceServerUpdateReceived(const QJsonObject& object)
{
    Q_UNUSED(object);
    // TODO: Implement this
}

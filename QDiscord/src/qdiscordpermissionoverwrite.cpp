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

#include "qdiscord.d/qdiscordpermissionoverwrite.hpp"

QDiscordPermissionOverwrite::QDiscordPermissionOverwrite() {}

QDiscordPermissionOverwrite::QDiscordPermissionOverwrite(
    QDiscordPermission allow,
    QDiscordPermission deny)
{
    for(quint8 i = 0; i < QDiscordPermission::bits; i++)
    {
        if(allow.bit(i))
            _value[i] = true;
        if(deny.bit(i))
            _value[i] = false;
    }
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::createInstantInvite() const
{
    return bit(0);
}

void QDiscordPermissionOverwrite::setCreateInstantInvite(
    std::experimental::optional<bool> value)
{
    set(0, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::kickMembers() const
{
    return bit(1);
}

void QDiscordPermissionOverwrite::setKickMembers(
    std::experimental::optional<bool> value)
{
    set(1, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::banMembers() const
{
    return bit(2);
}

void QDiscordPermissionOverwrite::setBanMembers(
    std::experimental::optional<bool> value)
{
    set(2, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::administrator() const
{
    return bit(3);
}

void QDiscordPermissionOverwrite::setAdministrator(
    std::experimental::optional<bool> value)
{
    set(3, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageChannels() const
{
    return bit(4);
}

void QDiscordPermissionOverwrite::setManageChannels(
    std::experimental::optional<bool> value)
{
    set(4, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageServer() const
{
    return bit(5);
}

void QDiscordPermissionOverwrite::setManageServer(
    std::experimental::optional<bool> value)
{
    set(5, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::addReactions() const
{
    return bit(6);
}

void QDiscordPermissionOverwrite::setAddReactions(
    std::experimental::optional<bool> value)
{
    set(6, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::viewAuditLogs() const
{
    return bit(7);
}

void QDiscordPermissionOverwrite::setViewAuditLogs(
    std::experimental::optional<bool> value)
{
    set(7, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::readMessages() const
{
    return bit(10);
}

void QDiscordPermissionOverwrite::setReadMessages(
    std::experimental::optional<bool> value)
{
    set(10, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::sendMessages() const
{
    return bit(11);
}

void QDiscordPermissionOverwrite::setSendMessages(
    std::experimental::optional<bool> value)
{
    set(11, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::sendTtsMessages() const
{
    return bit(12);
}

void QDiscordPermissionOverwrite::setSendTtsMessages(
    std::experimental::optional<bool> value)
{
    set(12, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageMessages() const
{
    return bit(13);
}

void QDiscordPermissionOverwrite::setManageMessages(
    std::experimental::optional<bool> value)
{
    set(13, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::embedLinks() const
{
    return bit(14);
}

void QDiscordPermissionOverwrite::setEmbedLinks(
    std::experimental::optional<bool> value)
{
    set(14, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::attachFiles() const
{
    return bit(15);
}

void QDiscordPermissionOverwrite::setAttachFiles(
    std::experimental::optional<bool> value)
{
    set(15, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::readMessageHistory() const
{
    return bit(16);
}

void QDiscordPermissionOverwrite::setReadMessageHistory(
    std::experimental::optional<bool> value)
{
    set(16, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::mentionEveryone() const
{
    return bit(17);
}

void QDiscordPermissionOverwrite::setMentionEveryone(
    std::experimental::optional<bool> value)
{
    set(17, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::externalEmojis() const
{
    return bit(18);
}

void QDiscordPermissionOverwrite::setExternalEmojis(
    std::experimental::optional<bool> value)
{
    set(18, value);
}

std::experimental::optional<bool> QDiscordPermissionOverwrite::connect() const
{
    return bit(20);
}

void QDiscordPermissionOverwrite::setConnect(
    std::experimental::optional<bool> value)
{
    set(20, value);
}

std::experimental::optional<bool> QDiscordPermissionOverwrite::speak() const
{
    return bit(21);
}

void QDiscordPermissionOverwrite::setSpeak(
    std::experimental::optional<bool> value)
{
    set(21, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::muteMembers() const
{
    return bit(22);
}

void QDiscordPermissionOverwrite::setMuteMembers(
    std::experimental::optional<bool> value)
{
    set(22, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::deafenMembers() const
{
    return bit(23);
}

void QDiscordPermissionOverwrite::setDeafenMembers(
    std::experimental::optional<bool> value)
{
    set(23, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::moveMembers() const
{
    return bit(24);
}

void QDiscordPermissionOverwrite::setMoveMembers(
    std::experimental::optional<bool> value)
{
    set(24, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::useVoiceActivation() const
{
    return bit(25);
}

void QDiscordPermissionOverwrite::setUseVoiceActivation(
    std::experimental::optional<bool> value)
{
    set(25, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::changeNickname() const
{
    return bit(26);
}

void QDiscordPermissionOverwrite::setChangeNickname(
    std::experimental::optional<bool> value)
{
    set(26, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageNicknames() const
{
    return bit(27);
}

void QDiscordPermissionOverwrite::setManageNicknames(
    std::experimental::optional<bool> value)
{
    set(27, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageRoles() const
{
    return bit(28);
}

void QDiscordPermissionOverwrite::setManageRoles(
    std::experimental::optional<bool> value)
{
    set(28, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageWebhooks() const
{
    return bit(29);
}

void QDiscordPermissionOverwrite::setManageWebhooks(
    std::experimental::optional<bool> value)
{
    set(29, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageEmojis() const
{
    return bit(30);
}

void QDiscordPermissionOverwrite::setManageEmojis(
    std::experimental::optional<bool> value)
{
    set(30, value);
}

QPair<QDiscordPermission, QDiscordPermission>
QDiscordPermissionOverwrite::pair() const
{
    QDiscordPermission allow;
    QDiscordPermission deny;

    for(quint8 i = 0; i < QDiscordPermission::bits; i++)
    {
        if(_value[i].has_value())
        {
            if(_value[i].value())
                allow.set(i, true);
            else
                deny.set(i, true);
        }
    }

    return {allow, deny};
}

bool QDiscordPermissionOverwrite::isEmpty() const
{
    for(const std::experimental::optional<bool> value : _value)
    {
        if(value.has_value())
            return false;
    }

    return true;
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::bit(quint8 index) const
{
    return _value[index];
}

void QDiscordPermissionOverwrite::set(quint8 index,
                                      std::experimental::optional<bool> value)
{
    _value[index] = value;
}

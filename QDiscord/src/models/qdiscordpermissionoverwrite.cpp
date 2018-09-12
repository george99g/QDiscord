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

#include "qdiscord.d/models/qdiscordpermissionoverwrite.hpp"

QDiscordPermissionOverwrite::QDiscordPermissionOverwrite(
    QDiscordPermission allow,
    QDiscordPermission deny)
{
    for(quint8 i = 0; i < QDiscordPermission::bits; i++)
    {
        if(allow.bit(i))
            _value.at(i) = true;
        if(deny.bit(i))
            _value.at(i) = false;
    }
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::createInstantInvite() const
{
    return bit(0);
}

void QDiscordPermissionOverwrite::setCreateInstantInvite(
    const std::experimental::optional<bool>& value)
{
    set(0, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::kickMembers() const
{
    return bit(1);
}

void QDiscordPermissionOverwrite::setKickMembers(
    const std::experimental::optional<bool>& value)
{
    set(1, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::banMembers() const
{
    return bit(2);
}

void QDiscordPermissionOverwrite::setBanMembers(
    const std::experimental::optional<bool>& value)
{
    set(2, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::administrator() const
{
    return bit(3);
}

void QDiscordPermissionOverwrite::setAdministrator(
    const std::experimental::optional<bool>& value)
{
    set(3, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageChannels() const
{
    return bit(4);
}

void QDiscordPermissionOverwrite::setManageChannels(
    const std::experimental::optional<bool>& value)
{
    set(4, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageServer() const
{
    return bit(5);
}

void QDiscordPermissionOverwrite::setManageServer(
    const std::experimental::optional<bool>& value)
{
    set(5, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::addReactions() const
{
    return bit(6);
}

void QDiscordPermissionOverwrite::setAddReactions(
    const std::experimental::optional<bool>& value)
{
    set(6, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::viewAuditLogs() const
{
    return bit(7);
}

void QDiscordPermissionOverwrite::setViewAuditLogs(
    const std::experimental::optional<bool>& value)
{
    set(7, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::readMessages() const
{
    return bit(10);
}

void QDiscordPermissionOverwrite::setReadMessages(
    const std::experimental::optional<bool>& value)
{
    set(10, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::sendMessages() const
{
    return bit(11);
}

void QDiscordPermissionOverwrite::setSendMessages(
    const std::experimental::optional<bool>& value)
{
    set(11, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::sendTtsMessages() const
{
    return bit(12);
}

void QDiscordPermissionOverwrite::setSendTtsMessages(
    const std::experimental::optional<bool>& value)
{
    set(12, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageMessages() const
{
    return bit(13);
}

void QDiscordPermissionOverwrite::setManageMessages(
    const std::experimental::optional<bool>& value)
{
    set(13, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::embedLinks() const
{
    return bit(14);
}

void QDiscordPermissionOverwrite::setEmbedLinks(
    const std::experimental::optional<bool>& value)
{
    set(14, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::attachFiles() const
{
    return bit(15);
}

void QDiscordPermissionOverwrite::setAttachFiles(
    const std::experimental::optional<bool>& value)
{
    set(15, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::readMessageHistory() const
{
    return bit(16);
}

void QDiscordPermissionOverwrite::setReadMessageHistory(
    const std::experimental::optional<bool>& value)
{
    set(16, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::mentionEveryone() const
{
    return bit(17);
}

void QDiscordPermissionOverwrite::setMentionEveryone(
    const std::experimental::optional<bool>& value)
{
    set(17, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::externalEmojis() const
{
    return bit(18);
}

void QDiscordPermissionOverwrite::setExternalEmojis(
    const std::experimental::optional<bool>& value)
{
    set(18, value);
}

std::experimental::optional<bool> QDiscordPermissionOverwrite::connect() const
{
    return bit(20);
}

void QDiscordPermissionOverwrite::setConnect(
    const std::experimental::optional<bool>& value)
{
    set(20, value);
}

std::experimental::optional<bool> QDiscordPermissionOverwrite::speak() const
{
    return bit(21);
}

void QDiscordPermissionOverwrite::setSpeak(
    const std::experimental::optional<bool>& value)
{
    set(21, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::muteMembers() const
{
    return bit(22);
}

void QDiscordPermissionOverwrite::setMuteMembers(
    const std::experimental::optional<bool>& value)
{
    set(22, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::deafenMembers() const
{
    return bit(23);
}

void QDiscordPermissionOverwrite::setDeafenMembers(
    const std::experimental::optional<bool>& value)
{
    set(23, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::moveMembers() const
{
    return bit(24);
}

void QDiscordPermissionOverwrite::setMoveMembers(
    const std::experimental::optional<bool>& value)
{
    set(24, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::useVoiceActivation() const
{
    return bit(25);
}

void QDiscordPermissionOverwrite::setUseVoiceActivation(
    const std::experimental::optional<bool>& value)
{
    set(25, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::changeNickname() const
{
    return bit(26);
}

void QDiscordPermissionOverwrite::setChangeNickname(
    const std::experimental::optional<bool>& value)
{
    set(26, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageNicknames() const
{
    return bit(27);
}

void QDiscordPermissionOverwrite::setManageNicknames(
    const std::experimental::optional<bool>& value)
{
    set(27, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageRoles() const
{
    return bit(28);
}

void QDiscordPermissionOverwrite::setManageRoles(
    const std::experimental::optional<bool>& value)
{
    set(28, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageWebhooks() const
{
    return bit(29);
}

void QDiscordPermissionOverwrite::setManageWebhooks(
    const std::experimental::optional<bool>& value)
{
    set(29, value);
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::manageEmojis() const
{
    return bit(30);
}

void QDiscordPermissionOverwrite::setManageEmojis(
    const std::experimental::optional<bool>& value)
{
    set(30, value);
}

QDiscordPermission QDiscordPermissionOverwrite::allow() const
{
    return pair().first;
}

QDiscordPermission QDiscordPermissionOverwrite::deny() const
{
    return pair().second;
}

QPair<QDiscordPermission, QDiscordPermission>
QDiscordPermissionOverwrite::pair() const
{
    QDiscordPermission allow;
    QDiscordPermission deny;

    for(quint8 i = 0; i < QDiscordPermission::bits; i++)
    {
        if(_value.at(i).has_value())
        {
            if(_value.at(i).value())
                allow.set(i, true);
            else
                deny.set(i, true);
        }
    }

    return {allow, deny};
}

bool QDiscordPermissionOverwrite::isEmpty() const
{
    for(const std::experimental::optional<bool>& value : _value)
    {
        if(value.has_value())
            return false;
    }

    return true;
}

std::experimental::optional<bool>
QDiscordPermissionOverwrite::bit(const quint8 index) const
{
    return _value.at(index);
}

void QDiscordPermissionOverwrite::set(
    const quint8 index,
    const std::experimental::optional<bool>& value)
{
    _value.at(index) = value;
}

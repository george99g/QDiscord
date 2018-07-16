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

#include "qdiscord.d/qdiscordpermission.hpp"

QDiscordPermission QDiscordPermission::none()
{
    return QDiscordPermission();
}

QDiscordPermission QDiscordPermission::all()
{
    return QDiscordPermission(0x7ff7fcff);
}

QDiscordPermission QDiscordPermission::allChannel()
{
    return QDiscordPermission(0x33f7fc51);
}

QDiscordPermission QDiscordPermission::general()
{
    return QDiscordPermission(0x7c0000bf);
}

QDiscordPermission QDiscordPermission::text()
{
    return QDiscordPermission(0x7fc40);
}

QDiscordPermission QDiscordPermission::voice()
{
    return QDiscordPermission(0x3f00000);
}

QDiscordPermission::QDiscordPermission(quint64 value)
    : _value(value)
{
}

bool QDiscordPermission::isSubset(const QDiscordPermission& other) const
{
    return (_value & other._value) == _value;
}

bool QDiscordPermission::isSuperset(const QDiscordPermission& other) const
{
    return (_value | other._value) == _value;
}

bool QDiscordPermission::isStrictSubset(const QDiscordPermission& other) const
{
    return isSubset(other) && operator!=(other);
}

bool QDiscordPermission::isStrictSuperset(const QDiscordPermission& other) const
{
    return isSuperset(other) && operator!=(other);
}

void QDiscordPermission::handleOverwrite(quint64 allow, quint64 deny)
{
    _value = (_value & ~deny) | allow;
}

void QDiscordPermission::handleOverwrite(const QDiscordPermission& allow,
                                         const QDiscordPermission& deny)
{
    handleOverwrite(allow._value, deny._value);
}

bool QDiscordPermission::createInstantInvite() const
{
    return bit(0);
}

void QDiscordPermission::setCreateInstantInvite(bool value)
{
    set(0, value);
}

bool QDiscordPermission::kickMembers() const
{
    return bit(1);
}

void QDiscordPermission::setKickMembers(bool value)
{
    set(1, value);
}

bool QDiscordPermission::banMembers() const
{
    return bit(2);
}

void QDiscordPermission::setBanMembers(bool value)
{
    set(2, value);
}

bool QDiscordPermission::administrator() const
{
    return bit(3);
}

void QDiscordPermission::setAdministrator(bool value)
{
    set(3, value);
}

bool QDiscordPermission::manageChannels() const
{
    return bit(4);
}

void QDiscordPermission::setManageChannels(bool value)
{
    set(4, value);
}

bool QDiscordPermission::manageServer() const
{
    return bit(5);
}

void QDiscordPermission::setManageServer(bool value)
{
    set(5, value);
}

bool QDiscordPermission::addReactions() const
{
    return bit(6);
}

void QDiscordPermission::setAddReactions(bool value)
{
    set(6, value);
}

bool QDiscordPermission::viewAuditLogs() const
{
    return bit(7);
}

void QDiscordPermission::setViewAuditLogs(bool value)
{
    set(7, value);
}

bool QDiscordPermission::readMessages() const
{
    return bit(10);
}

void QDiscordPermission::setReadMessages(bool value)
{
    set(10, value);
}

bool QDiscordPermission::sendMessages() const
{
    return bit(11);
}

void QDiscordPermission::setSendMessages(bool value)
{
    set(11, value);
}

bool QDiscordPermission::sendTtsMessages() const
{
    return bit(12);
}

void QDiscordPermission::setSendTtsMessages(bool value)
{
    set(12, value);
}

bool QDiscordPermission::manageMessages() const
{
    return bit(13);
}

void QDiscordPermission::setManageMessages(bool value)
{
    set(13, value);
}

bool QDiscordPermission::embedLinks() const
{
    return bit(14);
}

void QDiscordPermission::setEmbedLinks(bool value)
{
    set(14, value);
}

bool QDiscordPermission::attachFiles() const
{
    return bit(15);
}

void QDiscordPermission::setAttachFiles(bool value)
{
    set(15, value);
}

bool QDiscordPermission::readMessageHistory() const
{
    return bit(16);
}

void QDiscordPermission::setReadMessageHistory(bool value)
{
    set(16, value);
}

bool QDiscordPermission::mentionEveryone() const
{
    return bit(17);
}

void QDiscordPermission::setMentionEveryone(bool value)
{
    set(17, value);
}

bool QDiscordPermission::externalEmojis() const
{
    return bit(18);
}

void QDiscordPermission::setExternalEmojis(bool value)
{
    set(18, value);
}

bool QDiscordPermission::connect() const
{
    return bit(20);
}

void QDiscordPermission::setConnect(bool value)
{
    set(20, value);
}

bool QDiscordPermission::speak() const
{
    return bit(21);
}

void QDiscordPermission::setSpeak(bool value)
{
    set(21, value);
}

bool QDiscordPermission::muteMembers() const
{
    return bit(22);
}

void QDiscordPermission::setMuteMembers(bool value)
{
    set(22, value);
}

bool QDiscordPermission::deafenMembers() const
{
    return bit(23);
}

void QDiscordPermission::setDeafenMembers(bool value)
{
    set(23, value);
}

bool QDiscordPermission::moveMembers() const
{
    return bit(24);
}

void QDiscordPermission::setMoveMembers(bool value)
{
    set(24, value);
}

bool QDiscordPermission::useVoiceActivation() const
{
    return bit(25);
}

void QDiscordPermission::setUseVoiceActivation(bool value)
{
    set(25, value);
}

bool QDiscordPermission::changeNickname() const
{
    return bit(26);
}

void QDiscordPermission::setChangeNickname(bool value)
{
    set(26, value);
}

bool QDiscordPermission::manageNicknames() const
{
    return bit(27);
}

void QDiscordPermission::setManageNicknames(bool value)
{
    set(27, value);
}

bool QDiscordPermission::manageRoles() const
{
    return bit(28);
}

void QDiscordPermission::setManageRoles(bool value)
{
    set(28, value);
}

bool QDiscordPermission::manageWebhooks() const
{
    return bit(29);
}

void QDiscordPermission::setManageWebhooks(bool value)
{
    set(29, value);
}

bool QDiscordPermission::manageEmojis() const
{
    return bit(30);
}

void QDiscordPermission::setManageEmojis(bool value)
{
    set(30, value);
}

quint64 QDiscordPermission::value() const
{
    return _value;
}

bool QDiscordPermission::operator==(const QDiscordPermission& other) const
{
    return _value == other._value;
}

bool QDiscordPermission::operator!=(const QDiscordPermission& other) const
{
    return !operator==(other);
}

bool QDiscordPermission::operator>(const QDiscordPermission& other) const
{
    return isStrictSuperset(other);
}

bool QDiscordPermission::operator<(const QDiscordPermission& other) const
{
    return isStrictSubset(other);
}

bool QDiscordPermission::operator>=(const QDiscordPermission& other) const
{
    return isSuperset(other);
}

bool QDiscordPermission::operator<=(const QDiscordPermission& other) const
{
    return isSubset(other);
}

bool QDiscordPermission::bit(quint8 index) const
{
    return (_value >> index) & 1;
}

void QDiscordPermission::set(quint8 index, bool value)
{
    if(value)
        _value |= (1 << index);
    else
        _value &= ~(1 << index);
}

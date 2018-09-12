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

#ifndef QDISCORDPERMISSIONOVERWRITE_HPP
#define QDISCORDPERMISSIONOVERWRITE_HPP

#include "qdiscord.d/external/optional/optional.hpp"
#include "qdiscord.d/models/qdiscordpermission.hpp"
#include <QMetaType>
#include <QPair>
#include <array>

// Based on https://github.com/Rapptz/discord.py

class QDiscordPermissionOverwrite
{
public:
    QDiscordPermissionOverwrite() = default;
    QDiscordPermissionOverwrite(QDiscordPermission allow,
                                QDiscordPermission deny);

    std::experimental::optional<bool> createInstantInvite() const;
    void setCreateInstantInvite(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> kickMembers() const;
    void setKickMembers(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> banMembers() const;
    void setBanMembers(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> administrator() const;
    void setAdministrator(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> manageChannels() const;
    void setManageChannels(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> manageServer() const;
    void setManageServer(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> addReactions() const;
    void setAddReactions(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> viewAuditLogs() const;
    void setViewAuditLogs(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> readMessages() const;
    void setReadMessages(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> sendMessages() const;
    void setSendMessages(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> sendTtsMessages() const;
    void setSendTtsMessages(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> manageMessages() const;
    void setManageMessages(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> embedLinks() const;
    void setEmbedLinks(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> attachFiles() const;
    void setAttachFiles(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> readMessageHistory() const;
    void setReadMessageHistory(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> mentionEveryone() const;
    void setMentionEveryone(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> externalEmojis() const;
    void setExternalEmojis(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> connect() const;
    void setConnect(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> speak() const;
    void setSpeak(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> muteMembers() const;
    void setMuteMembers(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> deafenMembers() const;
    void setDeafenMembers(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> moveMembers() const;
    void setMoveMembers(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> useVoiceActivation() const;
    void setUseVoiceActivation(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> changeNickname() const;
    void setChangeNickname(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> manageNicknames() const;
    void setManageNicknames(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> manageRoles() const;
    void setManageRoles(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> manageWebhooks() const;
    void setManageWebhooks(const std::experimental::optional<bool>& value);
    std::experimental::optional<bool> manageEmojis() const;
    void setManageEmojis(const std::experimental::optional<bool>& value);

    QPair<QDiscordPermission, QDiscordPermission> pair() const;
    bool isEmpty() const;

private:
    std::experimental::optional<bool> bit(const quint8 index) const;
    void set(const quint8 index,
             const std::experimental::optional<bool>& value);

    std::array<std::experimental::optional<bool>, QDiscordPermission::bits>
        _value;
};

Q_DECLARE_METATYPE(QDiscordPermissionOverwrite)

#endif // QDISCORDPERMISSIONOVERWRITE_HPP

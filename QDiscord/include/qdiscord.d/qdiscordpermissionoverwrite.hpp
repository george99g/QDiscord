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
#include "qdiscord.d/qdiscordpermission.hpp"
#include <QMetaType>
#include <QPair>
#include <array>

// Based on https://github.com/Rapptz/discord.py

class QDiscordPermissionOverwrite
{
public:
    QDiscordPermissionOverwrite();
    QDiscordPermissionOverwrite(QDiscordPermission allow,
                                QDiscordPermission deny);

    std::experimental::optional<bool> createInstantInvite() const;
    void setCreateInstantInvite(std::experimental::optional<bool> value);
    std::experimental::optional<bool> kickMembers() const;
    void setKickMembers(std::experimental::optional<bool> value);
    std::experimental::optional<bool> banMembers() const;
    void setBanMembers(std::experimental::optional<bool> value);
    std::experimental::optional<bool> administrator() const;
    void setAdministrator(std::experimental::optional<bool> value);
    std::experimental::optional<bool> manageChannels() const;
    void setManageChannels(std::experimental::optional<bool> value);
    std::experimental::optional<bool> manageServer() const;
    void setManageServer(std::experimental::optional<bool> value);
    std::experimental::optional<bool> addReactions() const;
    void setAddReactions(std::experimental::optional<bool> value);
    std::experimental::optional<bool> viewAuditLogs() const;
    void setViewAuditLogs(std::experimental::optional<bool> value);
    std::experimental::optional<bool> readMessages() const;
    void setReadMessages(std::experimental::optional<bool> value);
    std::experimental::optional<bool> sendMessages() const;
    void setSendMessages(std::experimental::optional<bool> value);
    std::experimental::optional<bool> sendTtsMessages() const;
    void setSendTtsMessages(std::experimental::optional<bool> value);
    std::experimental::optional<bool> manageMessages() const;
    void setManageMessages(std::experimental::optional<bool> value);
    std::experimental::optional<bool> embedLinks() const;
    void setEmbedLinks(std::experimental::optional<bool> value);
    std::experimental::optional<bool> attachFiles() const;
    void setAttachFiles(std::experimental::optional<bool> value);
    std::experimental::optional<bool> readMessageHistory() const;
    void setReadMessageHistory(std::experimental::optional<bool> value);
    std::experimental::optional<bool> mentionEveryone() const;
    void setMentionEveryone(std::experimental::optional<bool> value);
    std::experimental::optional<bool> externalEmojis() const;
    void setExternalEmojis(std::experimental::optional<bool> value);
    std::experimental::optional<bool> connect() const;
    void setConnect(std::experimental::optional<bool> value);
    std::experimental::optional<bool> speak() const;
    void setSpeak(std::experimental::optional<bool> value);
    std::experimental::optional<bool> muteMembers() const;
    void setMuteMembers(std::experimental::optional<bool> value);
    std::experimental::optional<bool> deafenMembers() const;
    void setDeafenMembers(std::experimental::optional<bool> value);
    std::experimental::optional<bool> moveMembers() const;
    void setMoveMembers(std::experimental::optional<bool> value);
    std::experimental::optional<bool> useVoiceActivation() const;
    void setUseVoiceActivation(std::experimental::optional<bool> value);
    std::experimental::optional<bool> changeNickname() const;
    void setChangeNickname(std::experimental::optional<bool> value);
    std::experimental::optional<bool> manageNicknames() const;
    void setManageNicknames(std::experimental::optional<bool> value);
    std::experimental::optional<bool> manageRoles() const;
    void setManageRoles(std::experimental::optional<bool> value);
    std::experimental::optional<bool> manageWebhooks() const;
    void setManageWebhooks(std::experimental::optional<bool> value);
    std::experimental::optional<bool> manageEmojis() const;
    void setManageEmojis(std::experimental::optional<bool> value);

    QPair<QDiscordPermission, QDiscordPermission> pair() const;
    bool isEmpty() const;

private:
    std::experimental::optional<bool> bit(quint8 index) const;
    void set(quint8 index, std::experimental::optional<bool> value);

    std::array<std::experimental::optional<bool>, QDiscordPermission::bits>
        _value;
};

Q_DECLARE_METATYPE(QDiscordPermissionOverwrite)

#endif // QDISCORDPERMISSIONOVERWRITE_HPP

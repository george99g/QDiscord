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

#ifndef QDISCORDPERMISSION_HPP
#define QDISCORDPERMISSION_HPP

#include <QMetaType>

// Based on https://github.com/Rapptz/discord.py

class QDiscordPermission
{
    friend class QDiscordPermissionOverwrite;

public:
    static constexpr quint8 bits = 53;

    static QDiscordPermission none();
    static QDiscordPermission all();
    static QDiscordPermission allChannel();
    static QDiscordPermission general();
    static QDiscordPermission text();
    static QDiscordPermission voice();

    QDiscordPermission(quint64 value = 0);

    bool isSubset(const QDiscordPermission& other) const;
    bool isSuperset(const QDiscordPermission& other) const;
    bool isStrictSubset(const QDiscordPermission& other) const;
    bool isStrictSuperset(const QDiscordPermission& other) const;

    void handleOverwrite(quint64 allow, quint64 deny);
    void handleOverwrite(const QDiscordPermission& allow,
                         const QDiscordPermission& deny);

    bool createInstantInvite() const;
    void setCreateInstantInvite(bool value);
    bool kickMembers() const;
    void setKickMembers(bool value);
    bool banMembers() const;
    void setBanMembers(bool value);
    bool administrator() const;
    void setAdministrator(bool value);
    bool manageChannels() const;
    void setManageChannels(bool value);
    bool manageServer() const;
    void setManageServer(bool value);
    bool addReactions() const;
    void setAddReactions(bool value);
    bool viewAuditLogs() const;
    void setViewAuditLogs(bool value);
    bool readMessages() const;
    void setReadMessages(bool value);
    bool sendMessages() const;
    void setSendMessages(bool value);
    bool sendTtsMessages() const;
    void setSendTtsMessages(bool value);
    bool manageMessages() const;
    void setManageMessages(bool value);
    bool embedLinks() const;
    void setEmbedLinks(bool value);
    bool attachFiles() const;
    void setAttachFiles(bool value);
    bool readMessageHistory() const;
    void setReadMessageHistory(bool value);
    bool mentionEveryone() const;
    void setMentionEveryone(bool value);
    bool externalEmojis() const;
    void setExternalEmojis(bool value);
    bool connect() const;
    void setConnect(bool value);
    bool speak() const;
    void setSpeak(bool value);
    bool muteMembers() const;
    void setMuteMembers(bool value);
    bool deafenMembers() const;
    void setDeafenMembers(bool value);
    bool moveMembers() const;
    void setMoveMembers(bool value);
    bool useVoiceActivation() const;
    void setUseVoiceActivation(bool value);
    bool changeNickname() const;
    void setChangeNickname(bool value);
    bool manageNicknames() const;
    void setManageNicknames(bool value);
    bool manageRoles() const;
    void setManageRoles(bool value);
    bool manageWebhooks() const;
    void setManageWebhooks(bool value);
    bool manageEmojis() const;
    void setManageEmojis(bool value);

    quint64 value() const;

    bool operator==(const QDiscordPermission& other) const;
    bool operator!=(const QDiscordPermission& other) const;
    bool operator>(const QDiscordPermission& other) const;
    bool operator<(const QDiscordPermission& other) const;
    bool operator>=(const QDiscordPermission& other) const;
    bool operator<=(const QDiscordPermission& other) const;

private:
    bool bit(quint8 index) const;
    void set(quint8 index, bool value);

    quint64 _value;
};

Q_DECLARE_METATYPE(QDiscordPermission)

#endif // QDISCORDPERMISSION_HPP

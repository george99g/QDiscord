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

#include "qdiscord.d/models/qdiscordmodel.hpp"
#include <QMetaType>

// Based on https://github.com/Rapptz/discord.py

class QDiscordPermission
{
    Q_GADGET

    Q_PROPERTY(quint64 value READ value WRITE setValue)
    Q_PROPERTY(bool createInstantInvite READ createInstantInvite WRITE
                   setCreateInstantInvite STORED false)
    Q_PROPERTY(
        bool kickMembers READ kickMembers WRITE setKickMembers STORED false)
    Q_PROPERTY(bool banMembers READ banMembers WRITE setBanMembers STORED false)
    Q_PROPERTY(bool administrator READ administrator WRITE setAdministrator
                   STORED false)
    Q_PROPERTY(bool manageChannels READ manageChannels WRITE setManageChannels
                   STORED false)
    Q_PROPERTY(
        bool manageServer READ manageServer WRITE setManageServer STORED false)
    Q_PROPERTY(
        bool addReactions READ addReactions WRITE setAddReactions STORED false)
    Q_PROPERTY(bool viewAuditLogs READ viewAuditLogs WRITE setViewAuditLogs
                   STORED false)
    Q_PROPERTY(
        bool readMessages READ readMessages WRITE setReadMessages STORED false)
    Q_PROPERTY(
        bool sendMessages READ sendMessages WRITE setSendMessages STORED false)
    Q_PROPERTY(bool sendTtsMessages READ sendTtsMessages WRITE
                   setSendTtsMessages STORED false)
    Q_PROPERTY(bool manageMessages READ manageMessages WRITE setManageMessages
                   STORED false)
    Q_PROPERTY(bool embedLinks READ embedLinks WRITE setEmbedLinks STORED false)
    Q_PROPERTY(
        bool attachFiles READ attachFiles WRITE setAttachFiles STORED false)
    Q_PROPERTY(bool readMessageHistory READ readMessageHistory WRITE
                   setReadMessageHistory STORED false)
    Q_PROPERTY(bool mentionEveryone READ mentionEveryone WRITE
                   setMentionEveryone STORED false)
    Q_PROPERTY(bool externalEmojis READ externalEmojis WRITE setExternalEmojis
                   STORED false)
    Q_PROPERTY(bool connect READ connect WRITE setConnect STORED false)
    Q_PROPERTY(bool speak READ speak WRITE setSpeak STORED false)
    Q_PROPERTY(
        bool muteMembers READ muteMembers WRITE setMuteMembers STORED false)
    Q_PROPERTY(bool deafenMembers READ deafenMembers WRITE setDeafenMembers
                   STORED false)
    Q_PROPERTY(
        bool moveMembers READ moveMembers WRITE setMoveMembers STORED false)
    Q_PROPERTY(bool useVoiceActivation READ useVoiceActivation WRITE
                   setUseVoiceActivation STORED false)
    Q_PROPERTY(bool changeNickname READ changeNickname WRITE setChangeNickname
                   STORED false)
    Q_PROPERTY(bool manageNicknames READ manageNicknames WRITE
                   setManageNicknames STORED false)
    Q_PROPERTY(
        bool manageRoles READ manageRoles WRITE setManageRoles STORED false)
    Q_PROPERTY(bool manageWebhooks READ manageWebhooks WRITE setManageWebhooks
                   STORED false)
    Q_PROPERTY(
        bool manageEmojis READ manageEmojis WRITE setManageEmojis STORED false)

    friend class QDiscordPermissionOverwrite;

public:
    static constexpr quint8 bits = 53;

    Q_INVOKABLE static QDiscordPermission none();
    Q_INVOKABLE static QDiscordPermission all();
    Q_INVOKABLE static QDiscordPermission allChannel();
    Q_INVOKABLE static QDiscordPermission general();
    Q_INVOKABLE static QDiscordPermission text();
    Q_INVOKABLE static QDiscordPermission voice();

    QDiscordPermission(quint64 value = 0);

    Q_INVOKABLE bool isSubset(const QDiscordPermission& other) const;
    Q_INVOKABLE bool isSuperset(const QDiscordPermission& other) const;
    Q_INVOKABLE bool isStrictSubset(const QDiscordPermission& other) const;
    Q_INVOKABLE bool isStrictSuperset(const QDiscordPermission& other) const;

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
    void setValue(const quint64 value);

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

namespace QDiscordModel {
    template<>
    void field(QDiscordModel::DeserializeJsonAction& action,
               QDiscordPermission& value,
               const QString& name);

    template<>
    void field(QDiscordModel::SerializeJsonAction& action,
               const QDiscordPermission& value,
               const QString& name);
} // namespace QDiscordModel

#endif // QDISCORDPERMISSION_HPP

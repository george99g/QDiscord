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

#ifndef QDISCORDSTATE_HPP
#define QDISCORDSTATE_HPP

#include "qdiscord.d/qdiscordabstractstate.hpp"

class QDiscordRest;

class QDiscordState : public QDiscordAbstractState
{
    Q_OBJECT
public:
    explicit QDiscordState(QObject* parent = nullptr);
    virtual ~QDiscordState() = default;
    virtual void readyReceived(int protocolVersion,
                               QSharedPointer<QDiscordUser> user) override;
    virtual void
    channelCreateReceived(QSharedPointer<QDiscordChannel> channel) override;
    virtual void
    channelUpdateReceived(QSharedPointer<QDiscordChannel> channel) override;
    virtual void
    channelDeleteReceived(QSharedPointer<QDiscordChannel> channel) override;
    virtual void
    guildCreateReceived(QSharedPointer<QDiscordGuild> guild) override;
    virtual void
    guildUpdateReceived(QSharedPointer<QDiscordGuild> guild) override;
    virtual void
    guildDeleteReceived(QSharedPointer<QDiscordGuild> guild) override;
    virtual void guildBanAddReceived(const QJsonObject& object) override;
    virtual void guildBanRemoveReceived(const QJsonObject& object) override;
    virtual void guildEmojisUpdateReceived(const QJsonObject& object) override;
    virtual void
    guildIntegrationsUpdateReceived(const QJsonObject& object) override;
    virtual void guildMemberAddReceived(QSharedPointer<QDiscordMember> member,
                                        QDiscordID guildId) override;
    virtual void
    guildMemberRemoveReceived(QSharedPointer<QDiscordMember> member,
                              QDiscordID guildId) override;
    virtual void
    guildMemberUpdateReceived(QSharedPointer<QDiscordMember> member,
                              QDiscordID guildId) override;
    virtual void guildMembersChunkReceived(const QJsonObject& object) override;
    virtual void guildRoleCreateReceived(QSharedPointer<QDiscordRole> role,
                                         QDiscordID guildId) override;
    virtual void guildRoleUpdateReceived(QSharedPointer<QDiscordRole> role,
                                         QDiscordID guildId) override;
    virtual void guildRoleDeleteReceived(QDiscordID roleId,
                                         QDiscordID guildId) override;
    virtual void messageCreateReceived(QDiscordMessage message) override;
    virtual void messageUpdateReceived(QDiscordMessage message) override;
    virtual void messageDeleteReceived(QDiscordMessage message) override;
    virtual void messageDeleteBulkReceived(const QJsonObject& object) override;
    virtual void presenceUpdateReceived(const QJsonObject& object) override;
    virtual void typingStartReceived(const QJsonObject& object) override;
    virtual void userUpdateReceived(QSharedPointer<QDiscordUser> user) override;
    virtual void voiceStateUpdateReceived(const QJsonObject& object) override;
    virtual void voiceServerUpdateReceived(const QJsonObject& object) override;
    // TODO: Add ETF support
    virtual void reset() override;

    QDiscordRest* rest() const { return _rest; }
    void setRest(QDiscordRest* rest) { _rest = rest; }

    int protocolVersion() const { return _protocolVersion; }

    QSharedPointer<QDiscordUser> user() const { return _user; }
    void setUser(QSharedPointer<QDiscordUser> user) { _user = user; }

    QSharedPointer<QDiscordChannel> dmChannel(QDiscordID id) const
    {
        return _dmChannels.value(id);
    }
    QList<QSharedPointer<QDiscordChannel>> dmChannels() const
    {
        return _dmChannels.values();
    }
    QMap<QDiscordID, QSharedPointer<QDiscordChannel>> dmChannelsMap() const
    {
        return _dmChannels;
    }
    QSharedPointer<QDiscordChannel> channel(QDiscordID id) const;
    QSharedPointer<QDiscordGuild> guild(QDiscordID id) const
    {
        return _guilds.value(id);
    }
    QList<QSharedPointer<QDiscordGuild>> guilds() const
    {
        return _guilds.values();
    }
    QMap<QDiscordID, QSharedPointer<QDiscordGuild>> guildsMap() const
    {
        return _guilds;
    }

private:
    int _protocolVersion = -1;
    QSharedPointer<QDiscordUser> _user;
    QMap<QDiscordID, QSharedPointer<QDiscordChannel>> _dmChannels;
    QMap<QDiscordID, QSharedPointer<QDiscordGuild>> _guilds;
    QDiscordRest* _rest = nullptr;
};

#endif // QDISCORDSTATE_HPP

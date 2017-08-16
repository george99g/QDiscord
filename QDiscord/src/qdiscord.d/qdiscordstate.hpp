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

#include "qdiscordabstractstate.hpp"

class QDiscordRest;

class QDiscordState : public QDiscordAbstractState
{
    Q_OBJECT
public:
    explicit QDiscordState(QObject* parent = nullptr);
    virtual ~QDiscordState();
    virtual void readyReceived(const QJsonObject& object) override;
    virtual void channelCreateReceived(const QJsonObject& object) override;
    virtual void channelUpdateReceived(const QJsonObject& object) override;
    virtual void channelDeleteReceived(const QJsonObject& object) override;
    virtual void guildCreateReceived(const QJsonObject& object) override;
    virtual void guildUpdateReceived(const QJsonObject& object) override;
    virtual void guildDeleteReceived(const QJsonObject& object) override;
    virtual void guildBanAddReceived(const QJsonObject& object) override;
    virtual void guildBanRemoveReceived(const QJsonObject& object) override;
    virtual void guildEmojisUpdateReceived(const QJsonObject& object) override;
    virtual void
    guildIntegrationsUpdateReceived(const QJsonObject& object) override;
    virtual void guildMemberAddReceived(const QJsonObject& object) override;
    virtual void guildMemberRemoveReceived(const QJsonObject& object) override;
    virtual void guildMemberUpdateReceived(const QJsonObject& object) override;
    virtual void guildMembersChunkReceived(const QJsonObject& object) override;
    virtual void guildRoleCreateReceived(const QJsonObject& object) override;
    virtual void guildRoleUpdateReceived(const QJsonObject& object) override;
    virtual void guildRoleDeleteReceived(const QJsonObject& object) override;
    virtual void messageCreateReceived(const QJsonObject& object) override;
    virtual void messageUpdateReceived(const QJsonObject& object) override;
    virtual void messageDeleteReceived(const QJsonObject& object) override;
    virtual void messageDeleteBulkReceived(const QJsonObject& object) override;
    virtual void presenceUpdateReceived(const QJsonObject& object) override;
    virtual void typingStartReceived(const QJsonObject& object) override;
    virtual void userUpdateReceived(const QJsonObject& object) override;
    virtual void voiceStateUpdateReceived(const QJsonObject& object) override;
    virtual void voiceServerUpdateReceived(const QJsonObject& object) override;
    // TODO: Add ETF support
    virtual void reset() override;

    QDiscordRest* rest() const { return _rest; }
    void setRest(QDiscordRest* rest) { _rest = rest; }

    int protocolVersion() const { return _protocolVersion; }
    QSharedPointer<QDiscordChannel> privateChannel(QDiscordID id) const
    {
        return _privateChannels.value(id);
    }
    QList<QSharedPointer<QDiscordChannel>> privateChannels() const
    {
        return _privateChannels.values();
    }
    QMap<QDiscordID, QSharedPointer<QDiscordChannel>> privateChannelsMap() const
    {
        return _privateChannels;
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
    QMap<QDiscordID, QSharedPointer<QDiscordChannel>> _privateChannels;
    QMap<QDiscordID, QSharedPointer<QDiscordGuild>> _guilds;
    QDiscordRest* _rest;
};

#endif // QDISCORDSTATE_HPP

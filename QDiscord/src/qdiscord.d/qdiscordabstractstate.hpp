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

#ifndef QDISCORDABSTRACTSTATE_HPP
#define QDISCORDABSTRACTSTATE_HPP

#include <QObject>
#include "qdiscorduser.hpp"
#include "qdiscordmember.hpp"
#include "qdiscordchannel.hpp"
#include "qdiscordmessage.hpp"

class QDiscordAbstractState : public QObject
{
	Q_OBJECT
public:
	explicit QDiscordAbstractState(QObject* parent = nullptr);
	virtual ~QDiscordAbstractState();
	virtual void readyReceived(const QJsonObject& object) = 0;
	virtual void channelCreateReceived(const QJsonObject& object) = 0;
	virtual void channelUpdateReceived(const QJsonObject& object) = 0;
	virtual void channelDeleteReceived(const QJsonObject& object) = 0;
	virtual void guildCreateReceived(const QJsonObject& object) = 0;
	virtual void guildUpdateReceived(const QJsonObject& object) = 0;
	virtual void guildDeleteReceived(const QJsonObject& object) = 0;
	virtual void guildBanAddReceived(const QJsonObject& object) = 0;
	virtual void guildBanRemoveReceived(const QJsonObject& object) = 0;
	virtual void guildEmojisUpdateReceived(const QJsonObject& object) = 0;
	virtual void guildIntegrationsUpdateReceived(const QJsonObject& object) = 0;
	virtual void guildMemberAddReceived(const QJsonObject& object) = 0;
	virtual void guildMemberRemoveReceived(const QJsonObject& object) = 0;
	virtual void guildMemberUpdateReceived(const QJsonObject& object) = 0;
	virtual void guildMembersChunkReceived(const QJsonObject& object) = 0;
	virtual void guildRoleCreateReceived(const QJsonObject& object) = 0;
	virtual void guildRoleUpdateReceived(const QJsonObject& object) = 0;
	virtual void guildRoleDeleteReceived(const QJsonObject& object) = 0;
	virtual void messageCreateReceived(const QJsonObject& object) = 0;
	virtual void messageUpdateReceived(const QJsonObject& object) = 0;
	virtual void messageDeleteReceived(const QJsonObject& object) = 0;
	virtual void messageDeleteBulkReceived(const QJsonObject& object) = 0;
	virtual void presenceUpdateReceived(const QJsonObject& object) = 0;
	virtual void typingStartReceived(const QJsonObject& object) = 0;
	virtual void userUpdateReceived(const QJsonObject& object) = 0;
	virtual void voiceStateUpdateReceived(const QJsonObject& object) = 0;
	virtual void voiceServerUpdateReceived(const QJsonObject& object) = 0;
	//TODO: Add a set of methods for ETF handling here
	virtual void reset() = 0;
signals:
	void selfCreated(QSharedPointer<QDiscordUser> user);
	void channelCreated(QSharedPointer<QDiscordChannel> channel);
	void channelUpdated(QSharedPointer<QDiscordChannel> channel);
	void channelDeleted(QSharedPointer<QDiscordChannel> channel);
	void guildCreated(QSharedPointer<QDiscordGuild> guild);
	void guildAvailable(QSharedPointer<QDiscordGuild> guild);
	void guildUpdated(QSharedPointer<QDiscordGuild> guild);
	void guildDeleted(QSharedPointer<QDiscordGuild> guild);
	void guildUnavailable(QSharedPointer<QDiscordGuild> guild);
	void guildBanAdded(QSharedPointer<QDiscordGuild> guild, QDiscordUser user);
	void guildBanRemoved(QSharedPointer<QDiscordGuild> guild,
						 QDiscordUser user);
	void guildEmojisUpdated(/* TODO: Fill this in */);
	void guildIntegrationsUpdated(QSharedPointer<QDiscordGuild> guild);
	void guildMemberAdded(QSharedPointer<QDiscordMember> member);
	void guildMemberRemoved(QSharedPointer<QDiscordMember> member);
	void guildMemberUpdated(QSharedPointer<QDiscordMember> member);
	void guildMembersChunk(QSharedPointer<QDiscordGuild> guild,
						   QList<QSharedPointer<QDiscordMember>> members);
	void guildRoleCreated(/* TODO: Fill this in */);
	void guildRoleUpdated(/* TODO: Fill this in */);
	void guildRoleDeleted(/* TODO: Fill this in */);
	void messageCreated(QDiscordMessage message);
	void messageUpdated(QDiscordMessage message);
	void messageDeleted(QDiscordMessage message);
	void messagesDeleted(QList<QDiscordMessage> messages);
	void presenceUpdated(/* TODO: Fill this in */);
	void typingStarted(QSharedPointer<QDiscordChannel> channel,
					   QSharedPointer<QDiscordUser> user,
					   QDateTime timestamp);
	void selfUpdated(QSharedPointer<QDiscordUser> user);
	void voiceStateUpdated(/* TODO: Fill this in */);
	void voiceServerUpdated(QString token,
							QSharedPointer<QDiscordGuild> guild,
							QString endpoint);
private:

};

#endif // QDISCORDABSTRACTSTATE_HPP

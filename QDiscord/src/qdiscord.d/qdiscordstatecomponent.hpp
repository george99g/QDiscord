/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016 george99g
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

#ifndef QDISCORDSTATECOMPONENT_HPP
#define QDISCORDSTATECOMPONENT_HPP

#include <QObject>
#include <QMap>
#include "qdiscordguild.hpp"
#include "qdiscorduser.hpp"
#include "qdiscordchannel.hpp"
#include "qdiscordmessage.hpp"

/*!
 * \brief The state component of QDiscord.
 *
 * This class contains and manages all information related to the current state of the client.
 */
class QDISCORD_API QDiscordStateComponent : public QObject
{
	Q_OBJECT
	friend class QDiscord;
public:
	///\brief Standard QObject constructor.
	explicit QDiscordStateComponent(QObject* parent = 0);
	~QDiscordStateComponent();
	/*!
	 * \brief Returns a pointer to the guild that has the provided ID.
	 * May return `nullptr` if nothing was found.
	 * \returns `nullptr` if nothing was found.
	 */
	QDiscordGuild* guild(const QString& id) {return _guilds.value(id, nullptr);}
	///\brief Returns a map of pointers to all guilds and their IDs.
	QMap<QString, QDiscordGuild*> guilds() {return _guilds;}
	/*!
	 * \brief Returns a pointer to the channel that has the provided ID.
	 * May return `nullptr` if nothing was found.
	 * \returns A private channel, a guild channel or `nullptr` if nothing was found.
	 */
	QDiscordChannel* channel(const QString& id);
	///\brief Returns a map of pointers to all private channels and their IDs.
	QMap<QString, QDiscordChannel*> privateChannels() {return _privateChannels;}
	///\brief Returns a pointer to this client's information.
	QDiscordUser* self() {return _self;}
signals:
	/*!
	 * \brief Emitted when a guild has been created.
	 *
	 * The guild may be unavailable as this signal is emitted when any guild is created.\n
	 * Explicit checks will be required due to this.
	 * \param guild A pointer to the guild that has been created.
	 */
	void guildCreated(QDiscordGuild* guild);
	/*!
	 * \brief Emitted when a guild has become available.
	 *
	 * It should be safe to assume that all guilds provided by this signal will be available.
	 * \param guild A pointer to the guild that has become available.
	 */
	void guildAvailable(QDiscordGuild* guild);
	/*!
	 * \brief Emitted when a guild has been deleted.
	 * \param guild An object containing information about the guild that was deleted.
	 */
	void guildDeleted(QDiscordGuild guild);
	/*!
	 * \brief Emitted when a member has been added to a guild.
	 * \param member A pointer to the guild member that has been added.
	 */
	void guildMemberAdded(QDiscordMember* member);
	/*!
	 * \brief Emitted when a member has been removed from a guild.
	 * \param member An object containing information ab out the member that was deleted.
	 */
	void guildMemberRemoved(QDiscordMember member);
	/*!
	 * \brief Emitted when a member in a guild has received an update.
	 * \param member A pointer to the guild member that has been updated.
	 */
	void guildMemberUpdated(QDiscordMember* member);
	/*!
	 * \brief Emitted when information about the current client has been collected.
	 *
	 * This usually gets emitted whenever the READY event gets processed.
	 * \param self An object of this client's user.
	 */
	void selfCreated(QDiscordUser self);
	/*!
	 * \brief Emitted when a channel has been created.
	 * \param channel A pointer to the channel that was created.
	 */
	void channelCreated(QDiscordChannel* channel);
	/*!
	 * \brief Emitted when a channel has been deleted.
	 * \param channel An object containing information about the channel that was deleted.
	 */
	void channelDeleted(QDiscordChannel channel);
	/*!
	 * \brief Emitted when a channel has updated.
	 * \param channel A pointer to the channel that was updated.
	 */
	void channelUpdated(QDiscordChannel* channel);
	/*!
	 * \brief Emitted when a private channel is created.
	 * \param channel A pointer to the private channel that was created.
	 */
	void privateChannelCreated(QDiscordChannel* channel);
	/*!
	 * \brief Emitted when a private channel has been deleted.
	 * \param channel A pointer to the pirvate channel that was deleted.
	 */
	void privateChannelDeleted(QDiscordChannel channel);
	/*!
	 * \brief Emitted when a private channel has been updated.
	 * \param channel A pointer to the channel that was updated.
	 */
	void privateChannelUpdated(QDiscordChannel* channel);
	/*!
	 * \brief Emitted when a message has been created.
	 * \param message An object containing information about the sent message.
	 */
	void messageCreated(QDiscordMessage message);
	/*!
	 * \brief Emitted when a message has been created.
	 * \param message An object containing information about the deleted message. Usually,
	 * the only valid information is the ID.
	 */
	void messageDeleted(QDiscordMessage message);
	/*!
	 * \brief Emitted when a message has been updated.
	 * \param message An object containing information about the new message.
	 * \param editedTimestamp The timestamp when the message was edited.
	 */
	void messageUpdated(QDiscordMessage message, QDateTime editedTimestamp);
private:
	void clear();
	void readyReceived(const QJsonObject& object);
	void guildCreateReceived(const QJsonObject& object);
	void guildDeleteReceived(const QJsonObject& object);
	void guildBanAddReceived(const QJsonObject& object);
	void guildBanRemoveReceived(const QJsonObject& object);
	void guildIntegrationsUpdateRecevied(const QJsonObject& object);
	void guildMemberAddReceived(const QJsonObject& object);
	void guildMemberRemoveReceived(const QJsonObject& object);
	void guildMemberUpdateReceived(const QJsonObject& object);
	void guildRoleCreateReceived(const QJsonObject& object);
	void guildRoleDeleteReceived(const QJsonObject& object);
	void guildRoleUpdateReceived(const QJsonObject& object);
	void guildUpdateReceived(const QJsonObject& object);
	void messageCreateReceived(const QJsonObject& object);
	void messageDeleteReceived(const QJsonObject& object);
	void messageUpdateReceived(const QJsonObject& object);
	void presenceUpdateReceived(const QJsonObject& object);
	void typingStartReceived(const QJsonObject& object);
	void userSettingsUpdateReceived(const QJsonObject& object);
	void voiceStateUpdateReceived(const QJsonObject& object);
	void channelCreateReceived(const QJsonObject& object);
	void channelDeleteReceived(const QJsonObject& object);
	void channelUpdateReceived(const QJsonObject& object);
	QMap<QString, QDiscordGuild*> _guilds;
	QMap<QString, QDiscordChannel*> _privateChannels;
	QDiscordUser* _self;
};

#endif // QDISCORDSTATECOMPONENT_HPP

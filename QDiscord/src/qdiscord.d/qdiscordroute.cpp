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

#include "qdiscordroute.hpp"

QDiscordRoute::QDiscordRoute(Method method, QString url)
{
	route(method, url);
}

QDiscordRoute::Method QDiscordRoute::method() const
{
	return _method;
}

QString QDiscordRoute::bucketUrl() const
{
	return _bucketUrl;
}

QString QDiscordRoute::fullUrl() const
{
	return _fullUrl;
}

QString QDiscordRoute::routeString(QString url)
{
	return url;
}

void QDiscordRoute::route(QDiscordRoute::Method method, QString url)
{
	_method = method;
	_fullUrl = url;
	_bucketUrl = url;
}

// Self
QDiscordRoute QDiscordRoutes::Self::getSelf()
{
	return QDiscordRoute(QDiscordRoute::Method::GET,
						 QDiscordUtilities::endPoints.me);
}

QDiscordRoute QDiscordRoutes::Self::modifySelf()
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH,
						 QDiscordUtilities::endPoints.me);
}

QDiscordRoute QDiscordRoutes::Self::getGuilds()
{
	return QDiscordRoute(QDiscordRoute::Method::GET,
						 QDiscordUtilities::endPoints.me + "/guilds");
}

QDiscordRoute QDiscordRoutes::Self::leaveGuild(const QString& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::DELETE,
						 QDiscordUtilities::endPoints.me + "/guilds/{guildm}",
						 guild);
}

QDiscordRoute QDiscordRoutes::Self::getPrivateChannels()
{
	return QDiscordRoute(QDiscordRoute::Method::GET,
						 QDiscordUtilities::endPoints.me + "/channels");
}

QDiscordRoute QDiscordRoutes::Self::createPrivateChannel()
{
	return QDiscordRoute(QDiscordRoute::Method::POST,
						 QDiscordUtilities::endPoints.me + "/channels");
}

QDiscordRoute QDiscordRoutes::Self::gateway()
{
	return QDiscordRoute(QDiscordRoute::Method::GET,
						 QDiscordUtilities::endPoints.gateway);
}

QDiscordRoute QDiscordRoutes::Self::userSettings()
{
	return QDiscordRoute(QDiscordRoute::Method::GET,
						 QDiscordUtilities::endPoints.me + "/settings");
}

QDiscordRoute QDiscordRoutes::Self::login()
{
	return QDiscordRoute(QDiscordRoute::Method::POST,
						 QDiscordUtilities::endPoints.login);
}

QDiscordRoute QDiscordRoutes::Self::logout()
{
	return QDiscordRoute(QDiscordRoute::Method::POST,
						 QDiscordUtilities::endPoints.logout);
}

// Users
QDiscordRoute QDiscordRoutes::Users::getUser(const QString& user)
{
	return QDiscordRoute(QDiscordRoute::Method::GET,
						 QDiscordUtilities::endPoints.users + "/{user}",
						 user);
}

// Guilds
QDiscordRoute QDiscordRoutes::Guilds::getGuild(const QString& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::GET,
						 QDiscordUtilities::endPoints.guilds + "/{guild}",
						 guild);
}

QDiscordRoute QDiscordRoutes::Guilds::modifyGuild(const QString& guild)
{
	return QDiscordRoute(QDiscordRoute::Method::PATCH,
						 QDiscordUtilities::endPoints.guilds + "/{guild}",
						 guild);
}

QDiscordRoute QDiscordRoutes::Guilds::createChannel(const QString& guild)
{
	return QDiscordRoute(
				QDiscordRoute::Method::POST,
				QDiscordUtilities::endPoints.guilds + "/{guild}/channels",
				guild
				);
}

QDiscordRoute QDiscordRoutes::Guilds::getChannels(const QString& guild)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.guilds + "/{guild}/channels",
				guild
				);
}

QDiscordRoute QDiscordRoutes::Guilds::modifyChannels(const QString& guild)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PATCH,
				QDiscordUtilities::endPoints.guilds + "/{guild}/channels",
				guild
				);
}

QDiscordRoute QDiscordRoutes::Guilds::getBans(const QString& guild)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.guilds + "/{guild}/bans",
				guild
				);
}

QDiscordRoute QDiscordRoutes::Guilds::ban(const QString& guild,
										  const QString& user)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PUT,
				QDiscordUtilities::endPoints.guilds + "/{guild}/bans/{user}",
				guild,
				user
				);
}

QDiscordRoute QDiscordRoutes::Guilds::banWithDelete(const QString& guild,
													const QString& user,
													int days)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PUT,
				QDiscordUtilities::endPoints.guilds +
					"/{guild}/bans/{user}?delete-message-days={days}",
				guild,
				user,
				QString::number(days)
				);
}

QDiscordRoute QDiscordRoutes::Guilds::unban(const QString& guild,
											const QString& user)
{
	return QDiscordRoute(
				QDiscordRoute::Method::DELETE,
				QDiscordUtilities::endPoints.guilds + "/{guild}/bans/{user}",
				guild,
				user
				);
}

QDiscordRoute QDiscordRoutes::Guilds::kickMember(const QString& guild,
												 const QString& user)
{
	return QDiscordRoute(
				QDiscordRoute::Method::DELETE,
				QDiscordUtilities::endPoints.guilds + "/{guild}/members/{user}",
				guild,
				user
				);
}

QDiscordRoute QDiscordRoutes::Guilds::modifyMember(const QString& guild,
												   const QString& user)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PATCH,
				QDiscordUtilities::endPoints.guilds + "/{guild}/members/{user}",
				guild,
				user
				);
}

QDiscordRoute QDiscordRoutes::Guilds::modifySelfNick(const QString& guild)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PATCH,
				QDiscordUtilities::endPoints.guilds + "/{guild}/@me/nick",
				guild
				);
}

QDiscordRoute QDiscordRoutes::Guilds::prunableCount(const QString& guild,
													int days)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.guilds +
					"/{guild}/prune?days={days}",
				guild,
				QString::number(days)
				);
}

QDiscordRoute QDiscordRoutes::Guilds::pruneMembers(const QString& guild,
												   int days)
{
	return QDiscordRoute(
				QDiscordRoute::Method::POST,
				QDiscordUtilities::endPoints.guilds +
					"/{guild}/prune?days={days}",
				guild,
				QString::number(days)
				);
}

QDiscordRoute QDiscordRoutes::Guilds::createGuild()
{
	return QDiscordRoute(QDiscordRoute::Method::POST,
						 QDiscordUtilities::endPoints.guilds);
}

QDiscordRoute QDiscordRoutes::Guilds::deleteGuild(const QString& guild)
{
	return QDiscordRoute(
				QDiscordRoute::Method::POST,
				QDiscordUtilities::endPoints.guilds + "/{guildm}/delete",
				guild
				);
}

// Emotes
QDiscordRoute QDiscordRoutes::Emotes::modifyEmote(const QString& guild,
												  const QString& emote)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PATCH,
				QDiscordUtilities::endPoints.guilds +
					"/{guildm}/emojis/{emote}",
				guild,
				emote
				);
}

QDiscordRoute QDiscordRoutes::Emotes::deleteEmote(const QString& guild,
												  const QString& emote)
{
	return QDiscordRoute(
				QDiscordRoute::Method::DELETE,
				QDiscordUtilities::endPoints.guilds +
					"/{guildm}/emojis/{emote}",
				guild,
				emote
				);
}

QDiscordRoute QDiscordRoutes::Emotes::createEmote(const QString& guild)
{
	return QDiscordRoute(
				QDiscordRoute::Method::POST,
				QDiscordUtilities::endPoints.guilds + "/{guildm}/emojis",
				guild
				);
}

// Roles
QDiscordRoute QDiscordRoutes::Roles::getRoles(const QString& guild)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.guilds + "/{guild}/roles",
				guild
				);
}

QDiscordRoute QDiscordRoutes::Roles::createRole(const QString& guild)
{
	return QDiscordRoute(
				QDiscordRoute::Method::POST,
				QDiscordUtilities::endPoints.guilds + "/{guild}/roles",
				guild
				);
}

QDiscordRoute QDiscordRoutes::Roles::getRole(const QString& guild,
											 const QString& role)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.guilds + "/{guild}/roles/{role}",
				guild,
				role
				);
}

QDiscordRoute QDiscordRoutes::Roles::modifyRole(const QString& guild,
												const QString& role)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PATCH,
				QDiscordUtilities::endPoints.guilds + "/{guild}/roles/{role}",
				guild,
				role
				);
}

QDiscordRoute QDiscordRoutes::Roles::deleteRole(const QString& guild,
												const QString& role)
{
	return QDiscordRoute(
				QDiscordRoute::Method::DELETE,
				QDiscordUtilities::endPoints.guilds + "/{guild}/roles/{role}",
				guild,
				role
				);
}

// Channels
QDiscordRoute QDiscordRoutes::Channels::deleteChannel(const QString& channel)
{
	return QDiscordRoute(
				QDiscordRoute::Method::DELETE,
				QDiscordUtilities::endPoints.channels + "/{channelm}",
				channel
				);
}

QDiscordRoute QDiscordRoutes::Channels::modifyChannel(const QString& channel)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PATCH,
				QDiscordUtilities::endPoints.channels + "/{channel}",
				channel
				);
}

QDiscordRoute QDiscordRoutes::Channels::sendTyping(const QString& channel)
{
	return QDiscordRoute(
				QDiscordRoute::Method::POST,
				QDiscordUtilities::endPoints.channels + "/{channel}/typing",
				channel
				);
}

QDiscordRoute QDiscordRoutes::Channels::getPermissions(const QString& channel)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/permissions",
				channel
				);
}

QDiscordRoute QDiscordRoutes::Channels::getPermissionsOverride(
		const QString& channel,
		const QString& permissionsOverride)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/permissions/{permoverride}",
				channel,
				permissionsOverride
				);
}

QDiscordRoute QDiscordRoutes::Channels::createPermissionsOverride(
		const QString& channel,
		const QString& permissionsOverride)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PUT,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/permissions/{permoverride}",
				channel,
				permissionsOverride
				);
}

QDiscordRoute QDiscordRoutes::Channels::modifyPermissionsOverride(
		const QString& channel,
		const QString& permissionsOverride)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PUT,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/permissions/{permoverride}",
				channel,
				permissionsOverride
				);
}

QDiscordRoute QDiscordRoutes::Channels::deletePermissionsOverride(
		const QString& channel,
		const QString& permissionsOverride)
{
	return QDiscordRoute(
				QDiscordRoute::Method::DELETE,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/permissions/{permoverride}",
				channel,
				permissionsOverride
	);
}

// Messages
QDiscordRoute QDiscordRoutes::Messages::sendMessage(const QString& channel)
{
	return QDiscordRoute(
				QDiscordRoute::Method::POST,
				QDiscordUtilities::endPoints.channels + "/{channel}/messages",
				channel
				);
}

QDiscordRoute QDiscordRoutes::Messages::editMessage(const QString& channel,
													const QString& message)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PATCH,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages/{message}",
				channel,
				message
				);
}

QDiscordRoute QDiscordRoutes::Messages::deleteMessage(const QString& channel,
													  const QString& message)
{
	return QDiscordRoute(
				QDiscordRoute::Method::DELETE,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages/{message}",
				channel,
				message
				);
}

QDiscordRoute QDiscordRoutes::Messages::getPinnedMessages(
		const QString& channel)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/pins",
				channel
				);
}

QDiscordRoute QDiscordRoutes::Messages::addPinnedMessage(
			const QString& channel,
			const QString& message)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PUT,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/pins/{message}",
				channel,
				message
				);
}

QDiscordRoute QDiscordRoutes::Messages::removePinnedMessage(
			const QString& channel,
			const QString& message)
{
	return QDiscordRoute(
				QDiscordRoute::Method::DELETE,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/pins/{message}",
				channel,
				message
				);
}

QDiscordRoute QDiscordRoutes::Messages::addReaction(const QString& channel,
													const QString& message,
													const QString& reactionCode)
{
	return QDiscordRoute(
				QDiscordRoute::Method::PUT,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages/{message}/reactions/{reacion}/@me",
				channel,
				message,
				reactionCode
				);
}

QDiscordRoute QDiscordRoutes::Messages::removeReaction(
			const QString& channel,
			const QString& message,
			const QString& reactionCode,
			const QString& user)
{
	return QDiscordRoute(
				QDiscordRoute::Method::DELETE,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages/{message}/reactions/{reaction}/{user}",
				channel,
				message,
				reactionCode,
				user
				);
}

QDiscordRoute QDiscordRoutes::Messages::removeAllReactions(
			const QString& channel,
			const QString& message)
{
	return QDiscordRoute(
				QDiscordRoute::Method::DELETE,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages/{message}/reactions",
				channel,
				message
				);
}

QDiscordRoute QDiscordRoutes::Messages::getReactionUsers(
			const QString& channel,
			const QString& message,
			const QString& reactionCode,
			int limit)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages/{message}"
					"/reactions/{reaction}?limit={limit}",
				channel,
				message,
				reactionCode,
				QString::number(limit)
				);
}

QDiscordRoute QDiscordRoutes::Messages::getMessageHistory(
			const QString& channel,
			int limit)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages?limit={limit}",
				channel,
				limit
				);
}

QDiscordRoute QDiscordRoutes::Messages::getMessageHistoryBefore(
			const QString& channel,
			int limit,
			const QString& before)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages?limit={limit}&before={before}",
				channel,
				QString::number(limit),
				before
				);
}

QDiscordRoute QDiscordRoutes::Messages::getMessageHistoryAfter(
			const QString& channel,
			int limit,
			const QString& after)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages?limit={limit}&after={after}",
				channel,
				QString::number(limit),
				after
				);
}

QDiscordRoute QDiscordRoutes::Messages::getMessageHistoryAround(
			const QString& channel,
			int limit,
			const QString& around)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages?limit={limit}&around={around}",
				channel,
				QString::number(limit),
				around
				);
}

QDiscordRoute QDiscordRoutes::Messages::getMessage(
			const QString& channel,
			const QString& message)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages/{message}",
				channel,
				message
				);
}

QDiscordRoute QDiscordRoutes::Messages::deleteMessages(const QString& channel)
{
	return QDiscordRoute(
				QDiscordRoute::Method::POST,
				QDiscordUtilities::endPoints.channels +
					"/{channel}/messages/bulk-delete",
				channel
				);
}

// Invites
QDiscordRoute QDiscordRoutes::Invites::getInvite(const QString& code)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.apiBase + "/invites/{code}",
				code
				);
}

QDiscordRoute QDiscordRoutes::Invites::deleteInvite(const QString& code)
{
	return QDiscordRoute(
				QDiscordRoute::Method::DELETE,
				QDiscordUtilities::endPoints.apiBase + "/invites/{code}",
				code
				);
}

QDiscordRoute QDiscordRoutes::Invites::getGuildInvites(const QString& guild)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.guilds + "/{guild}/invites",
				guild
				);
}

QDiscordRoute QDiscordRoutes::Invites::getChannelInvites(const QString& channel)
{
	return QDiscordRoute(
				QDiscordRoute::Method::GET,
				QDiscordUtilities::endPoints.channels + "/{channel}/invites",
				channel
				);
}

QDiscordRoute QDiscordRoutes::Invites::createInvite(const QString& channel)
{
	return QDiscordRoute(
				QDiscordRoute::Method::POST,
				QDiscordUtilities::endPoints.channels + "/{channel}/invites",
				channel
				);
}

QDiscordRoute QDiscordRoutes::Invites::acceptInvite(const QString& code)
{
	return QDiscordRoute(
				QDiscordRoute::Method::POST,
				QDiscordUtilities::endPoints.apiBase + "/invites/{code}",
				code
				);
}

#ifdef QDISCORD_LIBRARY_DEBUG
QDebug& operator<<(QDebug& d, const QDiscordRoute& route)
{
	d.nospace() << "QDiscordRoute(Method: ";
	switch(route.method())
	{
	case QDiscordRoute::Method::DELETE:
		d << "DELETE";
		break;
	case QDiscordRoute::Method::GET:
		d << "GET";
		break;
	case QDiscordRoute::Method::PATCH:
		d << "PATCH";
		break;
	case QDiscordRoute::Method::POST:
		d << "POST";
		break;
	case QDiscordRoute::Method::PUT:
		d << "PUT";
		break;
	default:
		d << "?";
	}

	d << " Full URL: " << route.fullUrl();
	d << " Bucket URL: " << route.bucketUrl();
	d << ")";

	return d.maybeSpace();
}
#endif

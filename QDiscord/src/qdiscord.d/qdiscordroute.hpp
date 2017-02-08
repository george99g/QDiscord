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

#ifndef QDISCORDROUTE_HPP
#define QDISCORDROUTE_HPP

/*
 * This code is based off of the following code by FiniteReality:
 * https://github.com/FiniteReality/disccord/blob/master/include/rest/route.hpp
 * https://github.com/FiniteReality/disccord/blob/master/lib/rest/route.cpp
 * And the following code by DV8FromTheWorld:
 * https://github.com/DV8FromTheWorld/JDA/blob/master/src/main/java/net/dv8tion/jda/core/requests/Route.java
 */

#include <QString>
#include "qdiscordid.hpp"

class QDiscordRoute
{
public:
	enum class Method {
		GET, POST, PUT,
		DELETE, PATCH
	};
	QDiscordRoute(Method method, QString url);
	template<class TFirst, class... TArgs>
	QDiscordRoute(Method method, QString base, TFirst first, TArgs... args)
	{
		route(method, base, first, args...);
	}
	Method method() const;
	QString bucketUrl() const;
	QString fullUrl() const;

private:
	template<class TFirst, class... TArgs>
	static QString routeString(QString base, TFirst first, TArgs... args)
	{
		int start = base.indexOf('{');
		int end = base.indexOf('}', start);

		return routeString(base.replace(start, end, first), args...);
	}
	static QString routeString(QString url);
	template<class TFirst, class... TArgs>
	void route(Method method, QString base, TFirst first, TArgs... args)
	{
		int start = base.indexOf('{');
		int end = base.indexOf('}', start) - start + 1;

		QString parameter = base.mid(start, end);
		if(parameter == "{channel}" || parameter == "{guild}")
			route(method, base.replace(start, end, first), args...);
		else
		{
			_method = method;
			_bucketUrl = base;
			_fullUrl = routeString(base.replace(start, end, first), args...);
		}
	}
	void route(Method method, QString url);
	Method _method;
	QString _bucketUrl;
	QString _fullUrl;
};

#ifdef QDISCORD_LIBRARY_DEBUG
QDebug& operator<<(QDebug& d, const QDiscordRoute& route);
#endif

namespace QDiscordRoutes {
	namespace Self {
		QDiscordRoute getSelf();
		QDiscordRoute modifySelf();
		QDiscordRoute getGuilds();
		QDiscordRoute leaveGuild(const QDiscordID& guild);
		QDiscordRoute getPrivateChannels();
		QDiscordRoute createPrivateChannel();
		QDiscordRoute gateway();

		//Client-only
		QDiscordRoute userSettings();
		QDiscordRoute login();
		QDiscordRoute logout();
	}

	namespace Users {
		QDiscordRoute getUser(const QDiscordID& user);
	}

	namespace Guilds {
		QDiscordRoute getGuild(const QDiscordID& guild);
		QDiscordRoute modifyGuild(const QDiscordID& guild);
		QDiscordRoute createChannel(const QDiscordID& guild);
		QDiscordRoute getChannels(const QDiscordID& guild);
		QDiscordRoute modifyChannels(const QDiscordID& guild);
		QDiscordRoute getBans(const QDiscordID& guild);
		QDiscordRoute ban(const QDiscordID& guild, const QDiscordID& user);
		QDiscordRoute banWithDelete(
				const QDiscordID& guild,
				const QDiscordID& user,
				int days
		);
		QDiscordRoute unban(const QDiscordID& guild, const QDiscordID& user);
		QDiscordRoute kickMember(
				const QDiscordID& guild,
				const QDiscordID& user
		);
		QDiscordRoute modifyMember(
				const QDiscordID& guild,
				const QDiscordID& user
		);
		QDiscordRoute modifySelfNick(const QDiscordID& guild);
		QDiscordRoute prunableCount(const QDiscordID& guild, int days);
		QDiscordRoute pruneMembers(const QDiscordID& guild, int days);

		//Client-only
		QDiscordRoute createGuild();
		QDiscordRoute deleteGuild(const QDiscordID& guild);
	}

	namespace Emotes {
		QDiscordRoute modifyEmote(
				const QDiscordID& guild,
				const QDiscordID& emote
		);
		QDiscordRoute deleteEmote(
				const QDiscordID& guild,
				const QDiscordID& emote
		);
		QDiscordRoute createEmote(const QDiscordID& guild);
	}

	namespace Roles {
		QDiscordRoute getRoles(const QDiscordID& guild);
		QDiscordRoute createRole(const QDiscordID& guild);
		QDiscordRoute getRole(const QDiscordID& guild, const QDiscordID& role);
		QDiscordRoute modifyRole(
				const QDiscordID& guild,
				const QDiscordID& role
		);
		QDiscordRoute deleteRole(
				const QDiscordID& guild,
				const QDiscordID& role
		);
	}

	namespace Channels {
		QDiscordRoute deleteChannel(const QDiscordID& channel);
		QDiscordRoute modifyChannel(const QDiscordID& channel);
		QDiscordRoute sendTyping(const QDiscordID& channel);
		QDiscordRoute getPermissions(const QDiscordID& channel);
		QDiscordRoute getPermissionsOverride(
				const QDiscordID& channel,
				const QDiscordID& permissionsOverride
		);
		QDiscordRoute createPermissionsOverride(
				const QDiscordID& channel,
				const QDiscordID& permissionsOverride
		);
		QDiscordRoute modifyPermissionsOverride(
				const QDiscordID& channel,
				const QDiscordID& permissionsOverride
		);
		QDiscordRoute deletePermissionsOverride(
				const QDiscordID& channel,
				const QDiscordID& permissionsOverride
		);
	}

	namespace Messages {
		QDiscordRoute sendMessage(const QDiscordID& channel);
		QDiscordRoute editMessage(const QDiscordID& channel,
								  const QDiscordID& message);
		QDiscordRoute deleteMessage(const QDiscordID& channel,
									const QDiscordID& message);
		QDiscordRoute getPinnedMessages(const QDiscordID& channel);
		QDiscordRoute addPinnedMessage(const QDiscordID& channel,
									   const QDiscordID& message);
		QDiscordRoute removePinnedMessage(const QDiscordID& channel,
										  const QDiscordID& message);

		QDiscordRoute addReaction(const QDiscordID& channel,
								  const QDiscordID& message,
								  const QString& reactionCode);
		QDiscordRoute removeReaction(const QDiscordID& channel,
									 const QDiscordID& message,
									 const QString& reactionCode,
									 const QDiscordID& user);
		QDiscordRoute removeAllReactions(const QDiscordID& channel,
										 const QDiscordID& message);
		QDiscordRoute getReactionUsers(const QDiscordID& channel,
									   const QDiscordID& message,
									   const QString& reactionCode,
									   int limit);

		QDiscordRoute getMessageHistory(const QDiscordID& channel,
										int limit);
		QDiscordRoute getMessageHistoryBefore(const QDiscordID& channel,
											  int limit,
											  const QDiscordID& before);
		QDiscordRoute getMessageHistoryAfter(const QDiscordID& channel,
											 int limit,
											 const QDiscordID& after);
		QDiscordRoute getMessageHistoryAround(const QDiscordID& channel,
											  int limit,
											  const QDiscordID& around);

		//Bot-only
		QDiscordRoute getMessage(const QDiscordID& channel,
								 const QDiscordID& message);
		QDiscordRoute deleteMessages(const QDiscordID& channel);
	}

	namespace Invites {
		QDiscordRoute getInvite(const QString& code);
		QDiscordRoute deleteInvite(const QString& code);
		QDiscordRoute getGuildInvites(const QDiscordID& guild);
		QDiscordRoute getChannelInvites(const QDiscordID& channel);
		QDiscordRoute createInvite(const QDiscordID& channel);

		//Client-only
		QDiscordRoute acceptInvite(const QString& code);
	}
}

#endif // QDISCORDROUTE_HPP

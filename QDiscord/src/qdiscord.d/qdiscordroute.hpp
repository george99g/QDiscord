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
#include "qdiscordutilities.hpp"

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
		QDiscordRoute leaveGuild(const QString& guild);
		QDiscordRoute getPrivateChannels();
		QDiscordRoute createPrivateChannel();
		QDiscordRoute gateway();

		//Client-only
		QDiscordRoute userSettings();
		QDiscordRoute login();
		QDiscordRoute logout();
	}

	namespace Users {
		QDiscordRoute getUser(const QString& user);
	}

	namespace Guilds {
		QDiscordRoute getGuild(const QString& guild);
		QDiscordRoute modifyGuild(const QString& guild);
		QDiscordRoute createChannel(const QString& guild);
		QDiscordRoute getChannels(const QString& guild);
		QDiscordRoute modifyChannels(const QString& guild);
		QDiscordRoute getBans(const QString& guild);
		QDiscordRoute ban(const QString& guild, const QString& user);
		QDiscordRoute banWithDelete(
				const QString& guild,
				const QString& user,
				int days
		);
		QDiscordRoute unban(const QString& guild, const QString& user);
		QDiscordRoute kickMember(const QString& guild, const QString& user);
		QDiscordRoute modifyMember(const QString& guild, const QString& user);
		QDiscordRoute modifySelfNick(const QString& guild);
		QDiscordRoute prunableCount(const QString& guild, int days);
		QDiscordRoute pruneMembers(const QString& guild, int days);

		//Client-only
		QDiscordRoute createGuild();
		QDiscordRoute deleteGuild(const QString& guild);
	}

	namespace Emotes {
		QDiscordRoute modifyEmote(const QString& guild, const QString& emote);
		QDiscordRoute deleteEmote(const QString& guild, const QString& emote);
		QDiscordRoute createEmote(const QString& guild);
	}

	namespace Roles {
		QDiscordRoute getRoles(const QString& guild);
		QDiscordRoute createRole(const QString& guild);
		QDiscordRoute getRole(const QString& guild, const QString& role);
		QDiscordRoute modifyRole(const QString& guild, const QString& role);
		QDiscordRoute deleteRole(const QString& guild, const QString& role);
	}

	namespace Channels {
		QDiscordRoute deleteChannel(const QString& channel);
		QDiscordRoute modifyChannel(const QString& channel);
		QDiscordRoute sendTyping(const QString& channel);
		QDiscordRoute getPermissions(const QString& channel);
		QDiscordRoute getPermissionsOverride(
				const QString& channel,
				const QString& permissionsOverride
		);
		QDiscordRoute createPermissionsOverride(
				const QString& channel,
				const QString& permissionsOverride
		);
		QDiscordRoute modifyPermissionsOverride(
				const QString& channel,
				const QString& permissionsOverride
		);
		QDiscordRoute deletePermissionsOverride(
				const QString& channel,
				const QString& permissionsOverride
		);
	}

	namespace Messages {
		QDiscordRoute sendMessage(const QString& channel);
		QDiscordRoute editMessage(const QString& channel,
								  const QString& message);
		QDiscordRoute deleteMessage(const QString& channel,
									const QString& message);
		QDiscordRoute getPinnedMessages(const QString& channel);
		QDiscordRoute addPinnedMessage(const QString& channel,
									   const QString& message);
		QDiscordRoute removePinnedMessage(const QString& channel,
										  const QString& message);

		QDiscordRoute addReaction(const QString& channel,
								  const QString& message,
								  const QString& reactionCode);
		QDiscordRoute removeReaction(const QString& channel,
									 const QString& message,
									 const QString& reactionCode,
									 const QString& user);
		QDiscordRoute removeAllReactions(const QString& channel,
										 const QString& message);
		QDiscordRoute getReactionUsers(const QString& channel,
									   const QString& message,
									   const QString& reactionCode,
									   int limit);

		QDiscordRoute getMessageHistory(const QString& channel,
										int limit);
		QDiscordRoute getMessageHistoryBefore(const QString& channel,
											  int limit,
											  const QString& before);
		QDiscordRoute getMessageHistoryAfter(const QString& channel,
											 int limit,
											 const QString& after);
		QDiscordRoute getMessageHistoryAround(const QString& channel,
											  int limit,
											  const QString& around);

		//Bot-only
		QDiscordRoute getMessage(const QString& channel,
								 const QString& message);
		QDiscordRoute deleteMessages(const QString& channel);
	}

	namespace Invites {
		QDiscordRoute getInvite(const QString& code);
		QDiscordRoute deleteInvite(const QString& code);
		QDiscordRoute getGuildInvites(const QString& guild);
		QDiscordRoute getChannelInvites(const QString& channel);
		QDiscordRoute createInvite(const QString& channel);

		//Client-only
		QDiscordRoute acceptInvite(const QString& code);
	}
}

#endif // QDISCORDROUTE_HPP

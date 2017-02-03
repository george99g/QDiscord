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
 */

#include <QString>

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
	Method method();
	QString bucketUrl();
	QString fullUrl();
private:
	template<class TFirst, class... TArgs>
	QString routeString(QString base, TFirst first, TArgs... args)
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

#endif // QDISCORDROUTE_HPP

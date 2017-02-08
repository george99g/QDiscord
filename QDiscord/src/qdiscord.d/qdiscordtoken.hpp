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

#ifndef QDISCORDTOKEN_HPP
#define QDISCORDTOKEN_HPP

#include <QMetaType>
#include <QString>

class QDiscordToken
{
public:
	enum class Type
	{
		Auto,
		Bearer, Bot, None
	};
	QDiscordToken();
	QDiscordToken(QString token, Type type = Type::Bot);
	QString rawToken() const;
	void setRawToken(QString token);
	Type type() const;
	void setType(Type type);
	QString fullToken() const;
	bool isEmpty() const;
	void clear();
private:
	QString _token;
	Type _type;
};

Q_DECLARE_METATYPE(QDiscordToken)
Q_DECLARE_METATYPE(QDiscordToken::Type)

#endif // QDISCORDTOKEN_HPP

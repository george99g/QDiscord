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

#include "qdiscordtoken.hpp"

QDiscordToken::QDiscordToken()
{
	_type = Type::None;
}

QDiscordToken::QDiscordToken(QString token, Type type)
{
	//The token passed already has a type, so we'll have to use the string.
	if(type == Type::Auto)
	{
		int spacePos = token.indexOf(' ');
		//No space, no type, thus user token.
		if(spacePos == -1)
		{
			_token = token;
			_type = Type::None;
		}
		else //We have a space, let's try to find the type.
		{
			QString type = token.mid(0, spacePos);
			type = type.toLower();
			if(type == "bot")
			{
				_token = token.mid(spacePos + 1);
				_type = Type::Bot;
			}
			else if(type == "bearer")
			{
				_token = token.mid(spacePos + 1);
				_type = Type::Bearer;
			}
			else //Not a valid type. We'll assume they meant bot.
			{
				_token = token.mid(spacePos + 1);
				_type = Type::Bot;
			}
		}
	}
	else //The user has given us a type, use that.
	{
		_token = token;
		_type = type;
	}
}

QString QDiscordToken::rawToken() const
{
	return _token;
}

void QDiscordToken::setRawToken(QString token)
{
	_token = token;
}

QDiscordToken::Type QDiscordToken::type() const
{
	return _type;
}

void QDiscordToken::setType(QDiscordToken::Type type)
{
	_type = type;
}

QString QDiscordToken::fullToken() const
{
	switch(_type)
	{
	case Type::Bearer:
		return "Bearer " + _token;
	case Type::Bot:
		return "Bot " + _token;
	default:
		return _token;
	}
}

bool QDiscordToken::isEmpty() const
{
	return _token.isEmpty();
}

void QDiscordToken::clear()
{
	_token.clear();
	_type = Type::None;
}

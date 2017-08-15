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

#include "qdiscorduser.hpp"
#include "qdiscordutilities.hpp"
#include "qdiscordrest.hpp"

using std::experimental::optional;

QSharedPointer<QDiscordUser> QDiscordUser::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordUser> user(new QDiscordUser());
	user->deserialize(object);
	return user;
}

QDiscordUser::QDiscordUser(const QJsonObject& object)
{
	deserialize(object);
}

QDiscordUser::QDiscordUser()
{
	_bot = false;
	_mfaEnabled = false;
	_rest = nullptr;
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordUser("<<this<<") constructed";
#endif
}

QDiscordUser::~QDiscordUser()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordUser("<<this<<") destroyed";
#endif
}

void QDiscordUser::deserialize(const QJsonObject& object)
{
	_id = QDiscordID(object["id"].toString());
	_username = object["username"].toString();
	_discriminator = QDiscordDiscriminator(object["discriminator"].toString());
	_avatar = object["avatar"].toString();
	_bot = object["bot"].toBool(false);
	_mfaEnabled =  object["mfa_enabled"].toBool(false);
	if(object.contains("email"))
		_email = object["email"].toString();
	if(object.contains("verified"))
		_verified = object["verified"].toBool();
}

QJsonObject QDiscordUser::serialize() const
{
	QJsonObject object;

	object["id"] = _id.toString();
	object["username"] = _username;
	object["discriminator"] = _discriminator.toString();
	object["avatar"] = _avatar.isEmpty()?QJsonValue():_avatar;
	object["bot"] = _bot;
	object["mfa_enabled"] = _mfaEnabled;
	if(_email.has_value())
		object["email"] = _email.value();
	if(_verified.has_value())
		object["verified"] = _verified.value();

	return object;
}

void QDiscordUser::update(const QJsonObject& object)
{
	if(object.contains("id"))
		_id = QDiscordID(object["id"].toString());
	if(object.contains("username"))
		_username = object["username"].toString();
	if(object.contains("discriminator"))
	{
		_discriminator =
				QDiscordDiscriminator(object["discriminator"].toString());
	}
	if(object.contains("avatar"))
		_avatar = object["avatar"].toString();
	if(object.contains("bot"))
		_bot = object["bot"].toBool(false);
	if(object.contains("mfa_enabled"))
		_mfaEnabled = object["mfa_enabled"].toBool(false);
	if(object.contains("email"))
		_email = object["email"].toString();
	if(object.contains("verified"))
		_verified = object["verified"].toBool(false);

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordUser("<<this<<") updated";
#endif
}

QString QDiscordUser::mention() const
{
	return QString("<@%1>").arg(_id?_id.toString():"invalid ID");
}

QDiscordUser::operator bool() const
{
	return _id;
}

bool QDiscordUser::operator ==(const QDiscordUser& other) const
{
	return _id == other._id;
}

bool QDiscordUser::operator <(const QDiscordUser& other) const
{
	return _id < other._id;
}

bool QDiscordUser::operator >(const QDiscordUser& other) const
{
	return _id > other._id;
}

bool QDiscordUser::operator <=(const QDiscordUser& other) const
{
	return _id <= other._id;
}

bool QDiscordUser::operator >=(const QDiscordUser& other) const
{
	return _id >= other._id;
}

bool QDiscordUser::operator !=(const QDiscordUser& other) const
{
	return !operator ==(other);
}

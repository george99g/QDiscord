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

#include "qdiscordchannel.hpp"
#include "qdiscordguild.hpp"

QSharedPointer<QDiscordGuild> QDiscordGuild::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordGuild> guild(new QDiscordGuild());
	guild->deserialize(object);
	return guild;
}

QDiscordGuild::QDiscordGuild(const QDiscordGuild& other)
:QEnableSharedFromThis<QDiscordGuild>()
{
	_id = other._id;
	_unavailable = other._unavailable;
	_name = other._name;
	_verificationLevel = other._verificationLevel;
	_afkTimeout = other._afkTimeout;
	_memberCount = other._memberCount;
	_joinedAt = other._joinedAt;
	for(QSharedPointer<QDiscordChannel> item : other.channels())
	{
		QSharedPointer<QDiscordChannel> newChannel =
				QSharedPointer<QDiscordChannel>(
						new QDiscordChannel(*item)
					);
		newChannel->setGuild(sharedFromThis());
		_channels.insert(other.channelsMap().key(item), newChannel);
	}

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordGuild("<<this<<") copy-constructed";
#endif
}

QDiscordGuild::QDiscordGuild()
{
	_afkTimeout = -1;
	_embedEnabled = false;
	_verificationLevel = VerificationLevel::Unknown;
	_defaultMessageNotifications = NotificationLevel::Unknown;
	_mfaLevel = -1;
	_large = false;
	_unavailable = false;
	_memberCount = -1;

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordGuild("<<this<<") constructed";
#endif
}

QDiscordGuild::~QDiscordGuild()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordGuild("<<this<<") destroyed";
#endif
}

void QDiscordGuild::deserialize(const QJsonObject& object)
{
	_id = QDiscordID(object["id"].toString());
	_unavailable = object["unavailable"].toBool(false);
	if(!_unavailable)
	{
		_name = object["name"].toString();
		_icon = object["icon"].toString();
		_splash	= object["splash"].toString();
		_ownerId = QDiscordID(object["owner_id"].toString());
		_region = object["region"].toString();
		if(!object["afk_channel_id"].isNull())
			_afkChannelId = QDiscordID(object["afk_channel_id"].toString());
		_afkTimeout = object["afk_timeout"].toInt(-1);
		_embedEnabled = object["embed_enabled"].toBool(false);
		if(!object["embed_channel_id"].isNull())
			_embedChannelId = QDiscordID(object["embed_channel_id"].toString());

		switch(object["verification_level"].toInt(-1))
		{
		case 0:
			_verificationLevel = VerificationLevel::None;
			break;
		case 1:
			_verificationLevel = VerificationLevel::Low;
			break;
		case 2:
			_verificationLevel = VerificationLevel::Medium;
			break;
		case 3:
			_verificationLevel = VerificationLevel::High;
			break;
		default:
			_verificationLevel = VerificationLevel::Unknown;
		}

		switch(object["default_message_notifications"].toInt(-1))
		{
		case 0:
			_defaultMessageNotifications = NotificationLevel::AllMessages;
			break;
		case 1:
			_defaultMessageNotifications = NotificationLevel::OnlyMentions;
			break;
		default:
			_defaultMessageNotifications = NotificationLevel::Unknown;
		}

		switch(object["explicit_content_filter"].toInt(-1))
		{
		case 0:
			_explicitContentFilter = ExplicitContentFilterLevel::None;
			break;
		case 1:
			_explicitContentFilter = ExplicitContentFilterLevel::WithoutRoles;
			break;
		case 2:
			_explicitContentFilter = ExplicitContentFilterLevel::All;
			break;
		default:
			_explicitContentFilter = ExplicitContentFilterLevel::Unknown;
		}

		{
			QStringList features;
			for(QJsonValue value : object["features"].toArray())
				features.append(value.toString());
			_features = features;
		}
		_mfaLevel = object["mfa_level"].toInt(-1);
		_joinedAt = QDateTime::fromString(
					object["joined_at"].toString(),
					Qt::ISODateWithMs
				);
		_large = object["large"].toBool(false);
		_memberCount = object["member_count"].toInt(-1);
		for(const QJsonValue& item : object["members"].toArray())
		{
			QSharedPointer<QDiscordMember> member =
					QDiscordMember::fromJson(item.toObject());
			member->setGuild(sharedFromThis());
			_members.insert(member->user().id(), member);
		}
		for(const QJsonValue& item: object["channels"].toArray())
		{
			QSharedPointer<QDiscordChannel> channel =
					QDiscordChannel::fromJson(item.toObject());
			channel->setGuild(sharedFromThis());
			_channels.insert(channel->id(), channel);
		}
	}
}

QJsonObject QDiscordGuild::serialize()
{
	QJsonObject object;

	object["id"] = _id.toString();
	object["unavailable"] = _unavailable;
	if(!_unavailable)
	{
		object["name"] = _name;
		object["icon"] = _icon.isEmpty()?QJsonValue():_icon;
		object["splash"] = _splash.isEmpty()?QJsonValue():_splash;
		object["owner_id"] = _ownerId.toString();
		object["region"] = _region;
		object["afk_channel_id"] =
				_afkChannelId?_afkChannelId.toString():QJsonValue();
		object["afk_timeout"] = _afkTimeout;
		object["embed_enabled"] = _embedEnabled;
		object["embed_channel_id"] =
				_embedChannelId?_embedChannelId.toString():QJsonValue();
		object["verification_level"] = static_cast<qint8>(_verificationLevel);
		object["default_message_notifications"] =
				static_cast<qint8>(_defaultMessageNotifications);
		object["explicit_content_filter"] =
				static_cast<qint8>(_explicitContentFilter);
		{
			QJsonArray features;
			for(QString string : _features)
				features.append(string);
			object["features"] = features;
		}
		object["mfa_level"] = _mfaLevel;
		{
			object["joined_at"] =
					_joinedAt.toTimeSpec(Qt::OffsetFromUTC)
							 .toString(Qt::ISODateWithMs);
		}
		object["large"] = _large;
		object["member_count"] = _memberCount;
		{
			QJsonArray members;
			for(const QSharedPointer<QDiscordMember> member : _members.values())
				members.append(member->serialize());
			object["members"] = members;
		}
		{
			QJsonArray channels;
			for(const QSharedPointer<QDiscordChannel> channel
				: _channels.values())
			{
				channels.append(channel->serialize());
			}
			object["channels"] = channels;
		}
	}

	return object;
}

void QDiscordGuild::addChannel(QSharedPointer<QDiscordChannel> channel)
{
	if(!channel)
		return;
	 _channels.insert(channel->id(), channel);
}

bool QDiscordGuild::removeChannel(QSharedPointer<QDiscordChannel> channel)
{
	if(!channel)
		return false;
	if(!_channels.keys().contains(channel->id()))
		return false;
	_channels.remove(channel->id());
	return true;
}

void QDiscordGuild::addMember(QSharedPointer<QDiscordMember> member)
{
	if(!member)
		return;
	_members.insert(member->user().id(), member);
}

bool QDiscordGuild::removeMember(QSharedPointer<QDiscordMember> member)
{
	if(!member)
		return false;
	if(!_members.keys().contains(member->user().id()))
		return false;
	_members.remove(member->user().id());
	return true;
}

bool QDiscordGuild::operator ==(const QDiscordGuild& other) const
{
	return _id == other._id;
}

bool QDiscordGuild::operator !=(const QDiscordGuild& other) const
{
	return !operator ==(other);
}

bool QDiscordGuild::operator <(const QDiscordGuild& other) const
{
	return _id < other._id;
}

bool QDiscordGuild::operator >(const QDiscordGuild& other) const
{
	return _id > other._id;
}

bool QDiscordGuild::operator <=(const QDiscordGuild& other) const
{
	return _id <= other._id;
}

bool QDiscordGuild::operator >=(const QDiscordGuild& other) const
{
	return _id >= other._id;
}

QDiscordGuild::operator bool() const
{
	return _id;
}

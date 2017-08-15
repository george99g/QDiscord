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

namespace {
	QDiscordGuild::VerificationLevel vlFromInt(int i)
	{
		switch(i)
		{
		case 0:
			return QDiscordGuild::VerificationLevel::None;
		case 1:
			return QDiscordGuild::VerificationLevel::Low;
		case 2:
			return QDiscordGuild::VerificationLevel::Medium;
		case 3:
			return QDiscordGuild::VerificationLevel::High;
		default:
			return QDiscordGuild::VerificationLevel::Unknown;
		}
	}

	QDiscordGuild::NotificationLevel dmnFromInt(int i)
	{
		switch(i)
		{
		case 0:
			return QDiscordGuild::NotificationLevel::AllMessages;
		case 1:
			return QDiscordGuild::NotificationLevel::OnlyMentions;
		default:
			return QDiscordGuild::NotificationLevel::Unknown;
		}
	}

	QDiscordGuild::ExplicitContentFilterLevel ecfFromInt(int i)
	{
		switch(i)
		{
		case 0:
			return QDiscordGuild::ExplicitContentFilterLevel::None;
		case 1:
			return QDiscordGuild::ExplicitContentFilterLevel::WithoutRoles;
		case 2:
			return QDiscordGuild::ExplicitContentFilterLevel::All;
		default:
			return QDiscordGuild::ExplicitContentFilterLevel::Unknown;
		}
	}
}

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
	_icon = other._icon;
	_splash = other._splash;
	_ownerId = other._ownerId;
	_region = other._region;
	_afkChannelId = other._afkChannelId;
	_verificationLevel = other._verificationLevel;
	_afkTimeout = other._afkTimeout;
	_embedEnabled = other._embedEnabled;
	_embedChannelId = other._embedChannelId;
	_defaultMessageNotifications = other._defaultMessageNotifications;
	_explicitContentFilter = other._explicitContentFilter;
	_features = other._features;
	_mfaLevel = other._mfaLevel;
	_large = other._large;
	_memberCount = other._memberCount;
	_joinedAt = other._joinedAt;
	_applicationId = other._applicationId;
	for(QSharedPointer<QDiscordChannel> item : other.channels())
	{
		QSharedPointer<QDiscordChannel> newChannel =
				QSharedPointer<QDiscordChannel>(
						new QDiscordChannel(*item)
					);
		newChannel->setGuild(sharedFromThis());
		_channels.insert(newChannel->id(), newChannel);
	}

	for(QSharedPointer<QDiscordMember> item : other.members())
	{
		QSharedPointer<QDiscordMember> newMember =
				QSharedPointer<QDiscordMember>(
						new QDiscordMember(*item)
					);
		item->setGuild(sharedFromThis());
		_members.insert(newMember->user().id(), newMember);
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
	_explicitContentFilter = ExplicitContentFilterLevel::Unknown;
	_mfaLevel = -1;
	_large = false;
	_unavailable = false;
	_memberCount = -1;
	_rest = nullptr;

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
		_verificationLevel = vlFromInt(object["verification_level"].toInt(-1));
		_defaultMessageNotifications =
				dmnFromInt(object["default_message_notifications"].toInt(-1));
		_explicitContentFilter =
				ecfFromInt(object["explicit_content_filter"].toInt(-1));

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
		if(!object["application_id"].isNull())
			_applicationId = QDiscordID(object["application_id"].toString());
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
		object["application_id"] =
				_applicationId?_applicationId.toString():QJsonValue();
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

void QDiscordGuild::update(const QJsonObject& object)
{
	if(object.contains("id"))
		_id = QDiscordID(object["id"].toString());
	if(object.contains("unavailable"))
		_unavailable = object["unavailable"].toBool(false);
	if(!_unavailable)
	{
		if(object.contains("name"))
			_name = object["name"].toString();
		if(object.contains("icon"))
			_icon = object["icon"].toString();
		if(object.contains("splash"))
			_splash = object["splash"].toString();
		if(object.contains("owner_id"))
			_ownerId = QDiscordID(object["owner_id"].toString());
		if(object.contains("region"))
			_region = object["region"].toString();
		if(object.contains("afk_channel_id"))
		{
			if(object["afk_channel_id"].isNull())
				_afkTimeout = -1;
			else
				_afkTimeout = object["afk_channel_id"].toInt(-1);
		}
		if(object.contains("embed_enabled"))
			_embedEnabled = object["embed_enabled"].toBool(false);
		if(object.contains("embed_channel_id"))
		{
			if(object["embed_channel_id"].isNull())
				_embedChannelId = QDiscordID();
			else
			{
				_embedChannelId =
						QDiscordID(object["embed_channel_id"].toString());
			}
		}
		if(object.contains("verification_level"))
		{
			_verificationLevel =
					vlFromInt(object["verification_level"].toInt(-1));
		}
		if(object.contains("default_message_notifications"))
		{
			_defaultMessageNotifications = dmnFromInt(
						object["default_message_notifications"].toInt(-1)
					);
		}
		if(object.contains("explicit_content_filter"))
		{
			_explicitContentFilter =
					ecfFromInt(object["explicit_content_filter"].toInt(-1));
		}
		if(object.contains("features"))
		{
			QStringList features;
			for(QJsonValue value : object["features"].toArray())
				features.append(value.toString());
			_features = features;
		}
		if(object.contains("mfa_level"))
			_mfaLevel = object["mfa_level"].toInt(-1);
		if(object.contains("joined_at"))
		{
			_joinedAt = QDateTime::fromString(
						object["joined_at"].toString(),
						Qt::ISODateWithMs
					);
		}
		if(object.contains("large"))
			_large = object["large"].toBool(false);
		if(object.contains("member_count"))
			_memberCount = object["member_count"].toInt(-1);
		if(object.contains("application_id"))
		{
			if(object["application_id"].isNull())
				_applicationId = QDiscordID();
			else
			{
				_applicationId =
						QDiscordID(object["application_id"].toString());
			}
		}
		if(object.contains("members"))
		{
			for(const QJsonValue& item : object["members"].toArray())
			{
				_members.clear();
				QSharedPointer<QDiscordMember> member =
						QDiscordMember::fromJson(item.toObject());
				member->setGuild(sharedFromThis());
				_members.insert(member->user().id(), member);
			}
		}
		if(object.contains("channels"))
		{
			for(const QJsonValue& item: object["channels"].toArray())
			{
				_channels.clear();
				QSharedPointer<QDiscordChannel> channel =
						QDiscordChannel::fromJson(item.toObject());
				channel->setGuild(sharedFromThis());
				_channels.insert(channel->id(), channel);
			}
		}
	}
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

bool QDiscordGuild::removeChannel(QDiscordID channel)
{
	return _channels.remove(channel);
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

bool QDiscordGuild::removeMember(QDiscordID member)
{
	return _members.remove(member);
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

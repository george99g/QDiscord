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

#include "qdiscordguild.hpp"
#include "qdiscordchannel.hpp"
#include "qdiscordrest.hpp"

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
} // namespace

QSharedPointer<QDiscordGuild> QDiscordGuild::fromJson(const QJsonObject& object)
{
    QSharedPointer<QDiscordGuild> guild(new QDiscordGuild());
    guild->deserialize(object);
    return guild;
}

void QDiscordGuild::listMembers(
    QDiscordRest& rest,
    const QDiscordID& guild,
    std::function<void(QList<QDiscordMember>)> callback)
{
    QDiscordGuild::listMembers(rest, guild, 1, QDiscordID(0), callback);
}

void QDiscordGuild::listMembers(
    QDiscordRest& rest,
    const QDiscordID& guild,
    uint16_t limit,
    std::function<void(QList<QDiscordMember>)> callback)
{
    QDiscordGuild::listMembers(rest, guild, limit, QDiscordID(0), callback);
}

void QDiscordGuild::listMembers(
    QDiscordRest& rest,
    const QDiscordID& guild,
    const QDiscordID& after,
    std::function<void(QList<QDiscordMember>)> callback)
{
    QDiscordGuild::listMembers(rest, guild, 1, after, callback);
}

void QDiscordGuild::listMembers(
    std::function<void(QList<QDiscordMember>)> callback)
{
    QDiscordGuild::listMembers(1, QDiscordID(0), callback);
}

void QDiscordGuild::listMembers(
    uint16_t limit,
    std::function<void(QList<QDiscordMember>)> callback)
{
    QDiscordGuild::listMembers(limit, QDiscordID(0), callback);
}

void QDiscordGuild::listMembers(
    const QDiscordID& after,
    std::function<void(QList<QDiscordMember>)> callback)
{
    QDiscordGuild::listMembers(1, after, callback);
}

void QDiscordGuild::listMembers(
    QDiscordRest& rest,
    const QDiscordID& guild,
    uint16_t limit,
    const QDiscordID& after,
    std::function<void(QList<QDiscordMember>)> callback)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Guilds::listGuildMembers(guild, limit, after),
                 [&rest, callback](QNetworkReply* reply) {
                     QList<QDiscordMember> memberList;
                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(memberList);
                         return;
                     }
                     QJsonArray array =
                         QJsonDocument::fromJson(reply->readAll()).array();
                     for(const QJsonValue v : array)
                     {
                         QDiscordMember member(v.toObject());
                         member.setRest(&rest);
                         memberList.append(member);
                     }
                     callback(memberList);
                 });
}

void QDiscordGuild::listMembers(
    uint16_t limit,
    const QDiscordID& after,
    std::function<void(QList<QDiscordMember>)> callback)
{
    QDiscordGuild::listMembers(*_rest, _id, limit, after, callback);
}

QDiscordGuild::QDiscordGuild(const QDiscordGuild& other)
    : QEnableSharedFromThis<QDiscordGuild>()
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
    for(QSharedPointer<QDiscordRole> item : other.roles())
    {
        QSharedPointer<QDiscordRole> newRole(new QDiscordRole(*item));
        newRole->setGuild(sharedFromThis());
        _roles.insert(newRole->id(), newRole);
    }

    for(QSharedPointer<QDiscordChannel> item : other.channels())
    {
        QSharedPointer<QDiscordChannel> newChannel =
            QSharedPointer<QDiscordChannel>(new QDiscordChannel(*item));
        newChannel->setGuild(sharedFromThis());
        _channels.insert(newChannel->id(), newChannel);
    }

    for(QSharedPointer<QDiscordMember> item : other.members())
    {
        QSharedPointer<QDiscordMember> newMember =
            QSharedPointer<QDiscordMember>(new QDiscordMember(*item));
        item->setGuild(sharedFromThis());
        _members.insert(newMember->user().id(), newMember);
    }

#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordGuild(" << this << ") copy-constructed";
#endif
}

QDiscordGuild::QDiscordGuild()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordGuild(" << this << ") constructed";
#endif
}

QDiscordGuild::~QDiscordGuild()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordGuild(" << this << ") destroyed";
#endif
}

void QDiscordGuild::deserialize(const QJsonObject& object)
{
    _id = QDiscordID(object["id"].toString());
    _unavailable = object["unavailable"].toBool(false);
    if(!_unavailable.value())
    {
        _name = object["name"].toString();
        _icon = object["icon"].toString();
        _splash = object["splash"].toString();
        _ownerId = QDiscordID(object["owner_id"].toString());
        _region = object["region"].toString();
        if(!object["afk_channel_id"].isNull())
            _afkChannelId = QDiscordID(object["afk_channel_id"].toString());
        _afkTimeout = object["afk_timeout"].toInt(-1);
        if(object.contains("embed_enabled"))
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
        _joinedAt = QDateTime::fromString(object["joined_at"].toString(),
                                          Qt::ISODateWithMs);
        if(object.contains("large"))
            _large = object["large"].toBool(false);
        _memberCount = object["member_count"].toInt(-1);
        if(!object["application_id"].isNull())
            _applicationId = QDiscordID(object["application_id"].toString());
        for(const QJsonValue& item : object["roles"].toArray())
        {
            QSharedPointer<QDiscordRole> role =
                QDiscordRole::fromJson(item.toObject());
            role->setGuild(sharedFromThis());
            _roles.insert(role->id(), role);
        }
        for(const QJsonValue& item : object["members"].toArray())
        {
            QSharedPointer<QDiscordMember> member =
                QDiscordMember::fromJson(item.toObject());
            member->setGuild(sharedFromThis());
            _members.insert(member->user().id(), member);
        }
        for(const QJsonValue& item : object["channels"].toArray())
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
    if(_unavailable.has_value())
        object["unavailable"] = _unavailable.value();
    if(!_unavailable)
    {
        object["name"] = _name;
        object["icon"] = _icon.isEmpty() ? QJsonValue() : _icon;
        object["splash"] = _splash.isEmpty() ? QJsonValue() : _splash;
        object["owner_id"] = _ownerId.toString();
        object["region"] = _region;
        object["afk_channel_id"] =
            _afkChannelId ? _afkChannelId.toString() : QJsonValue();
        object["afk_timeout"] = _afkTimeout;
        if(_embedEnabled.has_value())
            object["embed_enabled"] = _embedEnabled.value();
        object["embed_channel_id"] =
            _embedChannelId ? _embedChannelId.toString() : QJsonValue();
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
            object["joined_at"] = _joinedAt.toTimeSpec(Qt::OffsetFromUTC)
                                      .toString(Qt::ISODateWithMs);
        }
        if(_large.has_value())
            object["large"] = _large.value();
        object["member_count"] = _memberCount;
        object["application_id"] =
            _applicationId ? _applicationId.toString() : QJsonValue();
        {
            QJsonArray roles;
            for(const QSharedPointer<QDiscordRole> role : _roles.values())
                roles.append(role->serialize());
            object["roles"] = roles;
        }
        {
            QJsonArray members;
            for(const QSharedPointer<QDiscordMember> member : _members.values())
                members.append(member->serialize());
            object["members"] = members;
        }
        {
            QJsonArray channels;
            for(const QSharedPointer<QDiscordChannel> channel :
                _channels.values())
            {
                channels.append(channel->serialize());
            }
            object["channels"] = channels;
        }
    }

    return object;
}

void QDiscordGuild::update(const QDiscordGuild& other)
{
    if(other.id())
        _id = other.id();
    if(other.unavailable().has_value())
        _unavailable = other.unavailable();
    if(_unavailable.has_value() && !_unavailable.value())
    {
        if(!other.name().isEmpty())
            _name = other.name();
        if(!other.icon().isEmpty())
            _icon = other.icon();
        if(!other.splash().isEmpty())
            _splash = other.splash();
        if(other.ownerId())
            _ownerId = other.ownerId();
        if(!other.region().isEmpty())
            _region = other.region();
        if(other.afkTimeout() != -1)
            _afkTimeout = other.afkTimeout();
        if(other.embedEnabled().has_value())
            _embedEnabled = other.embedEnabled();
        if(other.embedChannelId())
            _embedChannelId = embedChannelId();
        if(other.verificationLevel() != VerificationLevel::Unknown)
            _verificationLevel = other.verificationLevel();
        if(other.defaultMessageNotifications() != NotificationLevel::Unknown)
            _defaultMessageNotifications = other.defaultMessageNotifications();
        if(other.explicitContentFilter() != ExplicitContentFilterLevel::Unknown)
            _explicitContentFilter = other.explicitContentFilter();
        if(!other.features().isEmpty())
            _features = other.features();
        if(other.mfaLevel() != -1)
            _mfaLevel = other.mfaLevel();
        if(other.joinedAt().isValid())
            _joinedAt = other.joinedAt();
        if(other.large().has_value())
            _large = other.large();
        if(other.memberCount() != -1)
            _memberCount = other.memberCount();
        if(other.applicationId())
            _applicationId = other.applicationId();
        if(!other.rolesMap().isEmpty())
            _roles = other.rolesMap();
        if(!other.membersMap().isEmpty())
            _members = other.membersMap();
        if(!other.channelsMap().isEmpty())
            _channels = other.channelsMap();
    }

#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordGuild(" << this << ") updated";
#endif
}

void QDiscordGuild::addRole(QSharedPointer<QDiscordRole> role)
{
    if(!role)
        return;
    _roles.insert(role->id(), role);
}

bool QDiscordGuild::removeRole(QSharedPointer<QDiscordRole> role)
{
    if(!role)
        return false;
    return _roles.remove(role->id());
}

bool QDiscordGuild::removeRole(QDiscordID role)
{
    return _roles.remove(role);
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
    return _channels.remove(channel->id());
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
    return _members.remove(member->user().id());
}

bool QDiscordGuild::removeMember(QDiscordID member)
{
    return _members.remove(member);
}

void QDiscordGuild::setRest(QDiscordRest* rest)
{
    _rest = rest;
    for(QSharedPointer<QDiscordChannel> channel : _channels)
        channel->setRest(rest);
    for(QSharedPointer<QDiscordMember> member : _members)
        member->setRest(rest);
}

bool QDiscordGuild::operator==(const QDiscordGuild& other) const
{
    return _id == other._id;
}

bool QDiscordGuild::operator!=(const QDiscordGuild& other) const
{
    return !operator==(other);
}

bool QDiscordGuild::operator<(const QDiscordGuild& other) const
{
    return _id < other._id;
}

bool QDiscordGuild::operator>(const QDiscordGuild& other) const
{
    return _id > other._id;
}

bool QDiscordGuild::operator<=(const QDiscordGuild& other) const
{
    return _id <= other._id;
}

bool QDiscordGuild::operator>=(const QDiscordGuild& other) const
{
    return _id >= other._id;
}

QDiscordGuild::operator bool() const
{
    return _id;
}

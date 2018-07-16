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

#ifndef QDISCORDGUILD_HPP
#define QDISCORDGUILD_HPP

#include "qdiscord.d/external/optional/optional.hpp"
#include "qdiscord.d/qdiscordchannel.hpp"
#include "qdiscord.d/qdiscordmember.hpp"
#include "qdiscord.d/qdiscordrole.hpp"
#include <QDateTime>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

class QDiscordRest;

///\brief Represents a guild in the Discord API.
class QDiscordGuild : public QEnableSharedFromThis<QDiscordGuild>
{
public:
    static QSharedPointer<QDiscordGuild> fromJson(const QJsonObject& object);

    enum class NotificationLevel : qint8
    {
        AllMessages = 0,
        OnlyMentions = 1,
        Unknown = -1
    };

    enum class VerificationLevel : qint8
    {
        None = 0,
        Low = 1,
        Medium = 2,
        High = 3,
        Unknown = -1
    };

    enum class ExplicitContentFilterLevel : qint8
    {
        None = 0,
        WithoutRoles = 1,
        All = 2,
        Unknown = -1
    };

    static void
    listMembers(QDiscordRest& rest,
                const QDiscordID& guild,
                std::function<void(QList<QDiscordMember>)> callback);

    static void
    listMembers(QDiscordRest& rest,
                const QDiscordID& guild,
                uint16_t limit,
                std::function<void(QList<QDiscordMember>)> callback);

    static void
    listMembers(QDiscordRest& rest,
                const QDiscordID& guild,
                uint16_t limit,
                const QDiscordID& after,
                std::function<void(QList<QDiscordMember>)> callback);

    static void
    listMembers(QDiscordRest& rest,
                const QDiscordID& guild,
                const QDiscordID& after,
                std::function<void(QList<QDiscordMember>)> callback);

    void listMembers(std::function<void(QList<QDiscordMember>)> callback);

    void listMembers(uint16_t limit,
                     std::function<void(QList<QDiscordMember>)> callback);

    void listMembers(uint16_t limit,
                     const QDiscordID& after,
                     std::function<void(QList<QDiscordMember>)> callback);

    void listMembers(const QDiscordID& after,
                     std::function<void(QList<QDiscordMember>)> callback);

    QDiscordGuild(const QDiscordGuild& other);
    QDiscordGuild();
    ~QDiscordGuild();
    void deserialize(const QJsonObject& object);
    QJsonObject serialize();
    ///\brief Returns the guild's ID.
    QDiscordID id() const { return _id; }
    void setId(QDiscordID id) { _id = id; }
    ///\brief Returns the guild's name.
    QString name() const { return _name; }
    void setName(const QString& name) { _name = name; }
    QString icon() const { return _icon; }
    void setIcon(const QString& icon) { _icon = icon; }
    QString splash() const { return _splash; }
    void setSplash(const QString& splash) { _splash = splash; }
    QDiscordID ownerId() const { return _ownerId; }
    void setOwnerId(QDiscordID ownerId) { _ownerId = ownerId; }
    QDiscordID applicationId() const { return _applicationId; }
    void setApplicationId(QDiscordID applicationId)
    {
        _applicationId = applicationId;
    }
    QString region() const { return _region; }
    void setRegion(const QString& region) { _region = region; }
    QDiscordID afkChannelId() const { return _afkChannelId; }
    void setAfkChannelId(QDiscordID afkChannelId)
    {
        _afkChannelId = afkChannelId;
    }
    /*!
     * \brief Returns the guild's AFK time needed to move a user to the AFK
     * channel.
     */
    int afkTimeout() const { return _afkTimeout; }
    void setAfkTimeout(int afkTimeout) { _afkTimeout = afkTimeout; }
    std::experimental::optional<bool> embedEnabled() const
    {
        return _embedEnabled;
    }
    void setEmbedEnabled(bool embedEnabled) { _embedEnabled = embedEnabled; }
    void resetEmbedEnabled() { _embedEnabled.reset(); }
    QDiscordID embedChannelId() const { return _embedChannelId; }
    void setEmbedChannelId(QDiscordID embedChannelId)
    {
        _embedChannelId = embedChannelId;
    }
    ///\brief Returns the guild's verification level.
    VerificationLevel verificationLevel() const { return _verificationLevel; }
    void setVerificationLevel(VerificationLevel verificationLevel)
    {
        _verificationLevel = verificationLevel;
    }
    NotificationLevel defaultMessageNotifications() const
    {
        return _defaultMessageNotifications;
    }
    void setDefaultMessageNotifications(
        NotificationLevel defaultMessageNotifications)
    {
        _defaultMessageNotifications = defaultMessageNotifications;
    }
    ExplicitContentFilterLevel explicitContentFilter() const
    {
        return _explicitContentFilter;
    }
    void
    setExplicitContentFilter(ExplicitContentFilterLevel explicitContentFilter)
    {
        _explicitContentFilter = explicitContentFilter;
    }
    QStringList features() const { return _features; }
    void setFeatures(const QStringList& features) { _features = features; }
    int mfaLevel() const { return _mfaLevel; }
    void setMfaLevel(int mfaLevel) { _mfaLevel = mfaLevel; }
    ///\brief Returns the date the current user joined this guild.
    QDateTime joinedAt() const { return _joinedAt; }
    void setJoinedAt(const QDateTime& joinedAt) { _joinedAt = joinedAt; }
    std::experimental::optional<bool> large() const { return _large; }
    void setLarge(bool large) { _large = large; }
    void resetLarge() { _large.reset(); }
    /*!
     * \brief Returns whether the guild is unavailable.
     *
     * If this is true, a majority of guild information will not be available.
     */
    std::experimental::optional<bool> unavailable() const
    {
        return _unavailable;
    }
    void setUnavailable(bool unavailable) { _unavailable = unavailable; }
    void resetUnavailable() { _unavailable.reset(); }
    ///\brief Returns the guild's member count.
    int memberCount() const { return _memberCount; }
    void setMemberCount(int memberCount) { _memberCount = memberCount; }
    void update(const QDiscordGuild& other);
    QMap<QDiscordID, QSharedPointer<QDiscordRole>> rolesMap() const
    {
        return _roles;
    }
    ///\brief Returns a map of pointers to the guild's members and their IDs.
    QMap<QDiscordID, QSharedPointer<QDiscordMember>> membersMap() const
    {
        return _members;
    }
    ///\brief Returns a map of pointers to the guild's channels and their IDs.
    QMap<QDiscordID, QSharedPointer<QDiscordChannel>> channelsMap() const
    {
        return _channels;
    }
    QList<QSharedPointer<QDiscordRole>> roles() const
    {
        return _roles.values();
    }
    QList<QSharedPointer<QDiscordMember>> members() const
    {
        return _members.values();
    }
    QList<QSharedPointer<QDiscordChannel>> channels() const
    {
        return _channels.values();
    }
    QSharedPointer<QDiscordRole> role(const QDiscordID& id) const
    {
        return _roles.value(id, QSharedPointer<QDiscordRole>());
    }
    /*!
     * \brief Returns a pointer to a guild channel that has the provided ID.
     *
     * Returns `nullptr` if the channel was not found.
     */
    QSharedPointer<QDiscordChannel> channel(const QDiscordID& id) const
    {
        return _channels.value(id, QSharedPointer<QDiscordChannel>());
    }
    /*!
     * \brief Returns a pointer to a guild member that has the provided ID.
     *
     * Returns `nullptr` if the member was not found.
     */
    QSharedPointer<QDiscordMember> member(const QDiscordID& id) const
    {
        return _members.value(id, QSharedPointer<QDiscordMember>());
    }
    void addRole(QSharedPointer<QDiscordRole> role);
    bool removeRole(QSharedPointer<QDiscordRole> role);
    bool removeRole(QDiscordID role);
    ///\brief Adds the provided channel to the guild.
    void addChannel(QSharedPointer<QDiscordChannel> channel);
    /*!
     * \brief Removes the provided channel from the guild.
     *
     * Returns `true` if the channel was successfully removed. `false` if
     * `nullptr` was passed or the channel was not found.
     */
    bool removeChannel(QSharedPointer<QDiscordChannel> channel);
    bool removeChannel(QDiscordID channel);
    ///\brief Adds the provided member to the guild.
    void addMember(QSharedPointer<QDiscordMember> member);
    /*!
     * \brief Removes the provided member from the guild.
     *
     * Returns `true` if the member was successfully removed. `false` if
     * `nullptr` was passed or the member was not found.
     */
    bool removeMember(QSharedPointer<QDiscordMember> member);
    bool removeMember(QDiscordID member);

    QDiscordRest* rest() const { return _rest; }
    void setRest(QDiscordRest* rest);

    bool isNull() const { return _id.isNull(); }
    operator bool() const;
    bool operator==(const QDiscordGuild& other) const;
    bool operator!=(const QDiscordGuild& other) const;
    bool operator<(const QDiscordGuild& other) const;
    bool operator>(const QDiscordGuild& other) const;
    bool operator<=(const QDiscordGuild& other) const;
    bool operator>=(const QDiscordGuild& other) const;

private:
    QDiscordID _id;
    QString _name;
    QString _icon;
    QString _splash;
    QDiscordID _ownerId;
    QDiscordID _applicationId;
    QString _region;
    QDiscordID _afkChannelId;
    int _afkTimeout = -1;
    std::experimental::optional<bool> _embedEnabled;
    QDiscordID _embedChannelId;
    VerificationLevel _verificationLevel = VerificationLevel::Unknown;
    NotificationLevel _defaultMessageNotifications = NotificationLevel::Unknown;
    ExplicitContentFilterLevel _explicitContentFilter =
        ExplicitContentFilterLevel::Unknown;
    QStringList _features;
    int _mfaLevel = -1;
    QDateTime _joinedAt;
    std::experimental::optional<bool> _large;
    std::experimental::optional<bool> _unavailable;
    int _memberCount = -1;
    QMap<QDiscordID, QSharedPointer<QDiscordRole>> _roles;
    QMap<QDiscordID, QSharedPointer<QDiscordMember>> _members;
    QMap<QDiscordID, QSharedPointer<QDiscordChannel>> _channels;
    QDiscordRest* _rest = nullptr;
};

Q_DECLARE_METATYPE(QDiscordGuild)

#endif // QDISCORDGUILD_HPP

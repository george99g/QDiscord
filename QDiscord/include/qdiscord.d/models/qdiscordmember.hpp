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

#ifndef QDISCORDMEMBER_HPP
#define QDISCORDMEMBER_HPP

#include "qdiscord.d/external/optional/optional.hpp"
#include "qdiscord.d/models/qdiscorduser.hpp"
#include <QDateTime>
#include <QDebug>
#include <QSharedPointer>
#include <QWeakPointer>

class QDiscordGuild;
class QDiscordRest;

/*!
 * \brief Represents a guild member in the Discord API.
 *
 * This class contains a QDiscordUser object which provides more information
 * about the guild member.\n
 * You may acquire a pointer to it using QDiscordMember::user.
 */
class QDiscordMember
    : public QDiscordModelBase<QDiscordMember>
    , public QDiscordModel::CompareById<QDiscordMember>
{
    Q_GADGET

    Q_PROPERTY(QDiscordID dId READ id WRITE setId STORED false)
    Q_PROPERTY(QDiscordUser user READ constUser WRITE setUser)
    Q_PROPERTY(std::experimental::optional<QString> nickname READ nickname WRITE
                   setNickname)
    Q_PROPERTY(QDateTime joinedAt READ joinedAt WRITE setJoinedAt)
    Q_PROPERTY(std::experimental::optional<bool> deaf READ deaf WRITE setDeaf)
    Q_PROPERTY(std::experimental::optional<bool> mute READ mute WRITE setMute)
    Q_PROPERTY(QSharedPointer<QDiscordGuild> guild READ guild WRITE setGuild)
    Q_PROPERTY(QString mentionUsername READ mentionUsername STORED false)
    Q_PROPERTY(QString mentionNickname READ mentionNickname STORED false)

public:
    static QSharedPointer<QDiscordMember> fromJson(const QJsonObject& object);
    /*!
     * \brief Creates an instance from the provided parameters.
     * \param object A JSON object of a Discord guild member.
     * \param guild A pointer to the member's parent guild.
     */
    QDiscordMember(const QJsonObject& object);
    QDiscordMember() = default;
    void deserialize(const QJsonObject& object);
    QJsonObject serialize() const;
    QDiscordID id() const { return _user.id(); }
    void setId(const QDiscordID& id) { _user.setId(id); }
    ///\brief Returns a pointer to the user object contained by this object.
    QDiscordUser& user() { return _user; }
    const QDiscordUser& constUser() const { return _user; }
    void setUser(const QDiscordUser& user) { _user = user; }
    ///\brief Returns this member's nickname.
    std::experimental::optional<QString> nickname() const { return _nickname; }
    void setNickname(const std::experimental::optional<QString>& nickname)
    {
        _nickname = nickname;
    }
    void resetNickname() { _nickname.reset(); }
    ///\brief Returns the date at which the member has joined the guild.
    QDateTime joinedAt() const { return _joinedAt; }
    void setJoinedAt(const QDateTime& joinedAt) { _joinedAt = joinedAt; }
    ///\brief Returns whether the member has disabled their speakers.
    std::experimental::optional<bool> deaf() const { return _deaf; }
    void setDeaf(const std::experimental::optional<bool>& deaf)
    {
        _deaf = deaf;
    }
    void resetDeaf() { _deaf.reset(); }
    ///\brief Returns whether the member has muted their microphone.
    std::experimental::optional<bool> mute() const { return _mute; }
    void setMute(const std::experimental::optional<bool> mute) { _mute = mute; }
    void resetMute() { _mute.reset(); }
    ///\brief Updates the current instance from the provided parameters.
    void update(const QDiscordMember& other);
    ///\brief Returns a pointer to this object's parent guild.
    QSharedPointer<QDiscordGuild> guild() const { return _guild.toStrongRef(); }
    void setGuild(QWeakPointer<QDiscordGuild> guild) { _guild = guild; }
    ///\brief Returns a string which allows you to mention this member using
    /// their  username.
    QString mentionUsername() const;
    ///\brief Returns a string which allows you to mention this member using
    /// their  nickname.
    QString mentionNickname() const;

    QDiscordRest* rest() const { return _user.rest(); }
    void setRest(QDiscordRest* rest);

    bool operator==(const QDiscordMember& other) const;
    bool operator!=(const QDiscordMember& other) const;

    template<class Action>
    void map(Action& a)
    {
        using namespace QDiscordModel;
        field(a, _user, "user");
        field(a, _nickname, "nick");
        field(a, _joinedAt, "joined_at");
        field(a, _deaf, "deaf");
        field(a, _mute, "mute");
    }

    template<class Action>
    void map(Action& a) const
    {
        using namespace QDiscordModel;
        field(a, _user, "user");
        field(a, _nickname, "nick");
        field(a, _joinedAt, "joined_at");
        field(a, _deaf, "deaf");
        field(a, _mute, "mute");
    }

private:
    QDiscordUser _user;
    std::experimental::optional<QString> _nickname;
    QDateTime _joinedAt;
    std::experimental::optional<bool> _deaf;
    std::experimental::optional<bool> _mute;
    QWeakPointer<QDiscordGuild> _guild;
};

Q_DECLARE_METATYPE(QDiscordMember)

#endif // QDISCORDMEMBER_HPP

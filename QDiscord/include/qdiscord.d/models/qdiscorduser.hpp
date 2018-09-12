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

#ifndef QDISCORDUSER_HPP
#define QDISCORDUSER_HPP

#include "qdiscord.d/external/optional/optional.hpp"
#include "qdiscord.d/models/qdiscorddiscriminator.hpp"
#include "qdiscord.d/models/qdiscordid.hpp"
#include "qdiscord.d/models/qdiscordmodel.hpp"
#include <QDebug>
#include <QJsonObject>

class QDiscordRest;

///\brief Represents a user in the Discord API.
class QDiscordUser
    : public QDiscordModelBase<QDiscordUser>
    , public QDiscordModel::CompareById<QDiscordUser>
{
    Q_GADGET

    Q_PROPERTY(QDiscordID dId READ id WRITE setId)
    Q_PROPERTY(QString username READ username WRITE setUsername)
    Q_PROPERTY(QDiscordDiscriminator discriminator READ discriminator WRITE
                   setDiscriminator)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar)
    Q_PROPERTY(std::experimental::optional<bool> bot READ bot WRITE setBot)
    Q_PROPERTY(std::experimental::optional<bool> mfaEnabled READ mfaEnabled
                   WRITE setMfaEnabled)
    Q_PROPERTY(
        std::experimental::optional<QString> email READ email WRITE setEmail)
    Q_PROPERTY(std::experimental::optional<bool> verified READ verified WRITE
                   setVerified)

public:
    static QSharedPointer<QDiscordUser> fromJson(const QJsonObject& object);
    /*!
     * \brief Creates an instance from the provided parameters.
     * \param object A JSON object of a Discord user.
     */
    QDiscordUser(const QJsonObject& object);
    QDiscordUser() = default;
    void deserialize(const QJsonObject& object);
    QJsonObject serialize() const;
    ///\brief Updates the current instance from the provided parameters.
    void update(const QJsonObject& object);
    void update(const QDiscordUser& other);

    ///\brief Returns the user's ID.
    QDiscordID id() const { return _id; }
    void setId(QDiscordID id) { _id = id; }
    ///\brief Returns the user's username.
    QString username() const { return _username; }
    void setUsername(QString username) { _username = username; }
    ///\brief Returns the user's discriminator.
    QDiscordDiscriminator discriminator() const { return _discriminator; }
    void setDiscriminator(QDiscordDiscriminator discriminator)
    {
        _discriminator = discriminator;
    }
    ///\brief Returns the user's avatar string.
    QString avatar() const { return _avatar; }
    void setAvatar(QString avatar) { _avatar = avatar; }
    ///\brief Returns whether the user is a bot.
    std::experimental::optional<bool> bot() const { return _bot; }
    void setBot(const std::experimental::optional<bool>& bot) { _bot = bot; }
    void resetBot() { _bot.reset(); }
    std::experimental::optional<bool> mfaEnabled() const { return _mfaEnabled; }
    void setMfaEnabled(const std::experimental::optional<bool>& mfaEnabled)
    {
        _mfaEnabled = mfaEnabled;
    }
    void resetMfaEnabled() { _mfaEnabled.reset(); }
    ///\brief Returns the user's e-mail, if it can be determined.
    std::experimental::optional<QString> email() const { return _email; }
    void setEmail(const std::experimental::optional<QString>& email)
    {
        _email = email;
    }
    void resetEmail() { _email.reset(); }
    ///\brief Returns whether the user has verified their e-mail.
    std::experimental::optional<bool> verified() const { return _verified; }
    void setVerified(const std::experimental::optional<bool> verified)
    {
        _verified = verified;
    }
    void resetVerified() { _verified.reset(); }
    /*!
     * \brief Returns a string which allows you to mention this user using their
     * username.
     */
    QString mention() const;

    QDiscordRest* rest() const { return _rest; }
    void setRest(QDiscordRest* rest) { _rest = rest; }

    template<class Action>
    void map(Action& a)
    {
        using namespace QDiscordModel;
        field(a, _id, "id");
        field(a, _username, "username");
        field(a, _discriminator, "discriminator");
        field(a, _avatar, "avatar");
        field(a, _bot, "bot");
        field(a, _mfaEnabled, "mfa_enabled");
        field(a, _email, "email");
        field(a, _verified, "verified");
    }

    template<class Action>
    void map(Action& a) const
    {
        using namespace QDiscordModel;
        field(a, _id, "id");
        field(a, _username, "username");
        field(a, _discriminator, "discriminator");
        field(a, _avatar, "avatar");
        field(a, _bot, "bot");
        field(a, _mfaEnabled, "mfa_enabled");
        field(a, _email, "email");
        field(a, _verified, "verified");
    }

private:
    QDiscordID _id;
    QString _username;
    QDiscordDiscriminator _discriminator;
    QString _avatar;
    std::experimental::optional<bool> _bot;
    std::experimental::optional<bool> _mfaEnabled;
    std::experimental::optional<QString> _email;
    std::experimental::optional<bool> _verified;
    QDiscordRest* _rest = nullptr;
};

Q_DECLARE_METATYPE(QDiscordUser)

#endif // QDISCORDUSER_HPP

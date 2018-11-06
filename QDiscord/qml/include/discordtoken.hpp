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

#ifndef QML_DISCORDTOKEN_HPP
#define QML_DISCORDTOKEN_HPP

#include "qdiscord.d/qdiscordtoken.hpp"
#include <QObject>

namespace QDiscordQml {
    class DiscordToken : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QString rawToken READ rawToken WRITE setRawToken NOTIFY
                       rawTokenChanged)
        Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
        Q_PROPERTY(QString fullToken READ fullToken WRITE setFullToken NOTIFY
                       fullTokenChanged STORED false)
        Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)

    public:
        enum class Type
        {
            Auto,
            Bearer,
            Bot,
            None
        };
        Q_ENUM(Type)

        explicit DiscordToken(QObject* parent = nullptr);
        DiscordToken(const QString& token,
                     Type type = Type::Bot,
                     QObject* parent = nullptr);

        QString rawToken() const;
        void setRawToken(const QString& rawToken);

        Type type() const;
        void setType(Type type);

        QString fullToken() const;
        void setFullToken(const QString& fullToken);

        bool isEmpty() const;

        Q_INVOKABLE void clear();

        operator QDiscordToken() const;

    signals:
        void rawTokenChanged(QString rawToken);
        void typeChanged(Type type);
        void fullTokenChanged(QString fullToken);
        void isEmptyChanged(bool isEmpty);

    private:
        QDiscordToken _token;
    };
} // namespace QDiscordQml

#endif // QML_DISCORDTOKEN_HPP

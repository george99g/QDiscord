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
    Q_GADGET

    Q_PROPERTY(QString rawToken READ rawToken WRITE setRawToken)
    Q_PROPERTY(Type type READ type WRITE setType)
    Q_PROPERTY(QString fullToken READ fullToken STORED false)
    Q_PROPERTY(bool isEmpty READ isEmpty STORED false)

public:
    enum class Type
    {
        Auto,
        Bearer,
        Bot,
        None
    };
    Q_ENUM(Type)

    QDiscordToken();
    QDiscordToken(const QString& token, Type type = Type::Bot);
    QString rawToken() const;
    void setRawToken(const QString& token);
    Type type() const;
    void setType(Type type);
    QString fullToken() const;
    bool isEmpty() const;
    Q_INVOKABLE void clear();
    bool operator==(const QDiscordToken& other) const;
    bool operator!=(const QDiscordToken& other) const;
    bool operator<(const QDiscordToken& other) const;
    bool operator>(const QDiscordToken& other) const;
    bool operator<=(const QDiscordToken& other) const;
    bool operator>=(const QDiscordToken& other) const;

private:
    QString _token;
    Type _type;
};

Q_DECLARE_METATYPE(QDiscordToken)

#endif // QDISCORDTOKEN_HPP

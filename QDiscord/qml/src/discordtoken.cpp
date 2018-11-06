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

#include "discordtoken.hpp"
#include <QMap>

namespace {
    QDiscordToken::Type typeToInternalType(QDiscordQml::DiscordToken::Type type)
    {
        static const auto conversionMap =
            QMap<QDiscordQml::DiscordToken::Type, QDiscordToken::Type>{
                {QDiscordQml::DiscordToken::Type::Auto,
                 QDiscordToken::Type::Auto},
                {QDiscordQml::DiscordToken::Type::Bearer,
                 QDiscordToken::Type::Bearer},
                {QDiscordQml::DiscordToken::Type::Bot,
                 QDiscordToken::Type::Bot},
                {QDiscordQml::DiscordToken::Type::None,
                 QDiscordToken::Type::None},

            };

        return conversionMap.value(type, QDiscordToken::Type::None);
    }

    QDiscordQml::DiscordToken::Type internalTypeToType(QDiscordToken::Type type)
    {
        static const auto conversionMap =
            QMap<QDiscordToken::Type, QDiscordQml::DiscordToken::Type>{
                {QDiscordToken::Type::Auto,
                 QDiscordQml::DiscordToken::Type::Auto},
                {QDiscordToken::Type::Bearer,
                 QDiscordQml::DiscordToken::Type::Bearer},
                {QDiscordToken::Type::Bot,
                 QDiscordQml::DiscordToken::Type::Bot},
                {QDiscordToken::Type::None,
                 QDiscordQml::DiscordToken::Type::None}

            };

        return conversionMap.value(type, QDiscordQml::DiscordToken::Type::None);
    }
} // namespace

QDiscordQml::DiscordToken::DiscordToken(QObject* parent)
    : QObject(parent)
{
}

QDiscordQml::DiscordToken::DiscordToken(const QString& token,
                                        QDiscordQml::DiscordToken::Type type,
                                        QObject* parent)
    : QObject(parent)
    , _token(token, typeToInternalType(type))
{
}

QString QDiscordQml::DiscordToken::rawToken() const
{
    return _token.rawToken();
}

void QDiscordQml::DiscordToken::setRawToken(const QString& rawToken)
{
    bool previousIsEmpty = isEmpty();
    if(rawToken != _token.rawToken())
    {
        _token.setRawToken(rawToken);
        emit rawTokenChanged(rawToken);
        if(previousIsEmpty != isEmpty())
            emit isEmptyChanged(isEmpty());
        emit fullTokenChanged(_token.fullToken());
    }
}

QDiscordQml::DiscordToken::Type QDiscordQml::DiscordToken::type() const
{
    return internalTypeToType(_token.type());
}

void QDiscordQml::DiscordToken::setType(QDiscordQml::DiscordToken::Type type)
{
    if(type != internalTypeToType(_token.type()))
    {
        _token.setType(typeToInternalType(type));
        emit typeChanged(type);
        emit fullTokenChanged(_token.fullToken());
    }
}

QString QDiscordQml::DiscordToken::fullToken() const
{
    return _token.fullToken();
}

void QDiscordQml::DiscordToken::setFullToken(const QString& fullToken)
{
    QDiscordToken previousToken = _token;
    _token = QDiscordToken(fullToken, QDiscordToken::Type::Auto);
    if(previousToken.rawToken() != _token.rawToken())
        emit rawTokenChanged(_token.rawToken());
    if(previousToken.type() != _token.type())
        emit typeChanged(internalTypeToType(_token.type()));
    if(previousToken != _token)
        emit fullTokenChanged(_token.fullToken());
}

bool QDiscordQml::DiscordToken::isEmpty() const
{
    return _token.isEmpty();
}

void QDiscordQml::DiscordToken::clear()
{
    QString previousRawToken = _token.rawToken();
    QDiscordToken::Type previousType = _token.type();
    _token.clear();
    if(_token.rawToken() != previousRawToken)
        emit rawTokenChanged(QString());
    if(_token.type() != previousType)
        emit typeChanged(QDiscordQml::DiscordToken::Type::None);
    if(_token.type() != previousType || _token.rawToken() != previousRawToken)
        emit fullTokenChanged(_token.fullToken());
}

QDiscordQml::DiscordToken::operator QDiscordToken() const
{
    return _token;
}

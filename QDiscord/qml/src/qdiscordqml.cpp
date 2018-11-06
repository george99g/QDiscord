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

#include "qdiscordqml.hpp"
#include "discordtoken.hpp"
#include "discorduseragent.hpp"
#include <QQmlEngine>

void QDiscordQml::registerTypes()
{
    constexpr const char* libName = "QDiscord";
    constexpr int majorVersion = 0;
    constexpr int minorVersion = 1;

#define REGISTER_TYPE(TYPE)                                                    \
    qmlRegisterType<QDiscordQml::TYPE>(                                        \
        libName, majorVersion, minorVersion, #TYPE)

    REGISTER_TYPE(DiscordToken);
    REGISTER_TYPE(DiscordUserAgent);
    REGISTER_TYPE(DiscordLibraryVersion);

#undef REGISTER_TYPE
}

void QDiscordQmlPlugin::registerTypes(const char* uri)
{
    Q_ASSERT(uri == QLatin1String("QDiscord"));
    QDiscordQml::registerTypes();
}

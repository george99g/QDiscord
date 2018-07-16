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

#ifndef QDISCORDUSERAGENT_HPP
#define QDISCORDUSERAGENT_HPP

#include <QMetaType>
#include <QString>

struct QDiscordLibraryVersion
{
    QString version;
    quint16 majorVersion;
    quint16 minorVersion;
    quint16 patchVersion;
};

Q_DECLARE_METATYPE(QDiscordLibraryVersion)

class QDiscordUserAgent
{
public:
    QDiscordUserAgent();
    static const QDiscordUserAgent& global();
    QString libraryName() const { return _libraryName; }
    void setLibraryName(const QString& libraryName)
    {
        _libraryName = libraryName;
    }
    QString libraryLink() const { return _libraryLink; }
    void setLibraryLink(const QString& libraryLink)
    {
        _libraryLink = libraryLink;
    }
    QDiscordLibraryVersion libraryVersion() const { return _libraryVersion; }
    void setLibraryVersion(const QDiscordLibraryVersion& libraryVersion)
    {
        _libraryVersion = libraryVersion;
    }
    QString botName() const { return _botName; }
    void setBotName(const QString& botName) { _botName = botName; }
    QString toString() const;

private:
    static QDiscordUserAgent makeGlobalInstance();
    QString _libraryName;
    QString _libraryLink;
    QDiscordLibraryVersion _libraryVersion;
    QString _botName;
};

Q_DECLARE_METATYPE(QDiscordUserAgent)

#endif // QDISCORDUSERAGENT_HPP

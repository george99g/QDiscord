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

#ifndef QML_DISCORDUSERAGENT_HPP
#define QML_DISCORDUSERAGENT_HPP

#include "qdiscord.d/qdiscorduseragent.hpp"
#include <QObject>
#include <QSharedPointer>

namespace QDiscordQml {
    class DiscordLibraryVersion : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(
            QString version READ version WRITE setVersion NOTIFY versionChanged)
        Q_PROPERTY(quint16 majorVersion READ majorVersion WRITE setMajorVersion
                       NOTIFY majorVersionChanged)
        Q_PROPERTY(quint16 minorVersion READ minorVersion WRITE setMinorVersion
                       NOTIFY minorVersionChanged)
        Q_PROPERTY(quint16 patchVersion READ patchVersion WRITE setPatchVersion
                       NOTIFY patchVersionChanged)

    public:
        explicit DiscordLibraryVersion(QObject* parent = nullptr);

        QString version() const;
        void setVersion(const QString& version);

        quint16 majorVersion() const;
        void setMajorVersion(quint16 majorVersion);

        quint16 minorVersion() const;
        void setMinorVersion(quint16 minorVersion);

        quint16 patchVersion() const;
        void setPatchVersion(quint16 patchVersion);

        operator QDiscordLibraryVersion() const;

    signals:
        void versionChanged(QString version);
        void majorVersionChanged(quint16 majorVersion);
        void minorVersionChanged(quint16 minorVersion);
        void patchVersionChanged(quint16 patchVersion);

    private:
        friend class DiscordUserAgent;

        QDiscordLibraryVersion _libraryVersion;
    };

    class DiscordUserAgent : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QString libraryName READ libraryName WRITE setLibraryName
                       NOTIFY libraryNameChanged)
        Q_PROPERTY(QString libraryLink READ libraryLink WRITE setLibraryLink
                       NOTIFY libraryNameChanged)
        Q_PROPERTY(DiscordLibraryVersion* libraryVersion READ libraryVersion
                       WRITE setLibraryVersion NOTIFY libraryVersionChanged)
        Q_PROPERTY(
            QString botName READ botName WRITE setBotName NOTIFY botNameChanged)

    public:
        Q_INVOKABLE static DiscordUserAgent* global(QObject* parent = nullptr);

        explicit DiscordUserAgent(QObject* parent = nullptr);

        QString libraryName() const;
        void setLibraryName(const QString& libraryName);

        QString libraryLink() const;
        void setLibraryLink(const QString& libraryLink);

        DiscordLibraryVersion* libraryVersion() const;
        void setLibraryVersion(DiscordLibraryVersion* libraryVersion);

        QString botName() const;
        void setBotName(const QString& botName);

        Q_INVOKABLE QString string() const;

        operator QDiscordUserAgent() const;

    signals:

        void libraryNameChanged(QString libraryName);
        void libraryLinkChanged(QString libraryLink);
        void libraryVersionChanged(DiscordLibraryVersion* libraryVersion);
        void botNameChanged(QString botName);

    private:
        DiscordLibraryVersion* _libraryVersion;
        QString _libraryName;
        QString _libraryLink;
        QString _botName;
    };
} // namespace QDiscordQml

#endif // QML_DISCORDUSERAGENT_HPP

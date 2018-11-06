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

#include "discorduseragent.hpp"
#include <QQmlEngine>

QDiscordQml::DiscordUserAgent*
QDiscordQml::DiscordUserAgent::global(QObject* parent)
{
    return new DiscordUserAgent(parent);
}

QDiscordQml::DiscordUserAgent::DiscordUserAgent(QObject* parent)
    : QObject(parent)
{
    const QDiscordUserAgent& nativeInstance = QDiscordUserAgent::global();
    auto libVersionInstance = new DiscordLibraryVersion(this);
    libVersionInstance->_libraryVersion.version =
        nativeInstance.libraryVersion().version;
    libVersionInstance->_libraryVersion.majorVersion =
        nativeInstance.libraryVersion().majorVersion;
    libVersionInstance->_libraryVersion.minorVersion =
        nativeInstance.libraryVersion().minorVersion;
    libVersionInstance->_libraryVersion.patchVersion =
        nativeInstance.libraryVersion().patchVersion;

    _libraryVersion = libVersionInstance;
    _botName = nativeInstance.botName();
    _libraryName = nativeInstance.libraryName();
    _libraryLink = nativeInstance.libraryLink();
}

QString QDiscordQml::DiscordUserAgent::libraryName() const
{
    return _libraryName;
}

void QDiscordQml::DiscordUserAgent::setLibraryName(const QString& libraryName)
{
    if(_libraryName == libraryName)
        return;
    _libraryName = libraryName;
    emit libraryNameChanged(libraryName);
}

QString QDiscordQml::DiscordUserAgent::libraryLink() const
{
    return _libraryLink;
}

void QDiscordQml::DiscordUserAgent::setLibraryLink(const QString& libraryLink)
{
    if(_libraryLink == libraryLink)
        return;
    _libraryLink = libraryLink;
    emit libraryLinkChanged(libraryLink);
}

QDiscordQml::DiscordLibraryVersion*
QDiscordQml::DiscordUserAgent::libraryVersion() const
{
    return _libraryVersion;
}

void QDiscordQml::DiscordUserAgent::setLibraryVersion(
    QDiscordQml::DiscordLibraryVersion* libraryVersion)
{
    if(_libraryVersion == libraryVersion)
        return;
    if(libraryVersion == nullptr)
        return;
    if(_libraryVersion->parent() == this)
        delete _libraryVersion;
    _libraryVersion = libraryVersion;
    if(_libraryVersion->parent() == nullptr)
        _libraryVersion->setParent(this);
    emit libraryVersionChanged(libraryVersion);
}

QString QDiscordQml::DiscordUserAgent::botName() const
{
    return _botName;
}

void QDiscordQml::DiscordUserAgent::setBotName(const QString& botName)
{
    if(_botName == botName)
        return;
    _botName = botName;
    emit botNameChanged(botName);
}

QString QDiscordQml::DiscordUserAgent::string() const
{
    return QString("DiscordBot (%1, v%2); %3")
        .arg(_libraryLink, _libraryVersion->version(), _botName);
}

QDiscordQml::DiscordUserAgent::operator QDiscordUserAgent() const
{
    QDiscordUserAgent userAgent;

    userAgent.setLibraryVersion(*_libraryVersion);
    userAgent.setLibraryLink(_libraryLink);
    userAgent.setLibraryName(_libraryName);
    userAgent.setBotName(_botName);

    return userAgent;
}

QDiscordQml::DiscordLibraryVersion::DiscordLibraryVersion(QObject* parent)
    : QObject(parent)
{
}

QString QDiscordQml::DiscordLibraryVersion::version() const
{
    return _libraryVersion.version;
}

void QDiscordQml::DiscordLibraryVersion::setVersion(const QString& version)
{
    if(_libraryVersion.version == version)
        return;
    _libraryVersion.version = version;
    emit versionChanged(version);
}

quint16 QDiscordQml::DiscordLibraryVersion::majorVersion() const
{
    return _libraryVersion.majorVersion;
}

void QDiscordQml::DiscordLibraryVersion::setMajorVersion(quint16 majorVersion)
{
    if(_libraryVersion.majorVersion == majorVersion)
        return;
    _libraryVersion.majorVersion = majorVersion;
    emit majorVersionChanged(majorVersion);
}

quint16 QDiscordQml::DiscordLibraryVersion::minorVersion() const
{
    return _libraryVersion.minorVersion;
}

void QDiscordQml::DiscordLibraryVersion::setMinorVersion(quint16 minorVersion)
{
    if(_libraryVersion.minorVersion == minorVersion)
        return;
    _libraryVersion.minorVersion = minorVersion;
    emit minorVersionChanged(minorVersion);
}

quint16 QDiscordQml::DiscordLibraryVersion::patchVersion() const
{
    return _libraryVersion.patchVersion;
}

void QDiscordQml::DiscordLibraryVersion::setPatchVersion(quint16 patchVersion)
{
    if(_libraryVersion.patchVersion == patchVersion)
        return;
    _libraryVersion.patchVersion = patchVersion;
    emit patchVersionChanged(patchVersion);
}

QDiscordQml::DiscordLibraryVersion::operator QDiscordLibraryVersion() const
{
    return _libraryVersion;
}

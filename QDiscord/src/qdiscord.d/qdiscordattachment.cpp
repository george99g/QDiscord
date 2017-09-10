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

#include "qdiscordattachment.hpp"

QSharedPointer<QDiscordAttachment>
QDiscordAttachment::fromJson(const QJsonObject& object)
{
    QSharedPointer<QDiscordAttachment> attachment(new QDiscordAttachment());
    attachment->deserialize(object);
    return attachment;
}

QDiscordAttachment::QDiscordAttachment(const QJsonObject& object)
{
    deserialize(object);

#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordAttachment(" << this << ") constructed";
#endif
}

QDiscordAttachment::QDiscordAttachment()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordAttachment(" << this << ") constructed";
#endif
}

QDiscordAttachment::~QDiscordAttachment()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordAttachment(" << this << ") destroyed";
#endif
}

void QDiscordAttachment::deserialize(const QJsonObject& object)
{
    _id = QDiscordID(object["id"].toString());
    _filename = object["filename"].toString();
    _size = object["size"].toInt();
    _url = object["url"].toString();
    _proxyUrl = object["proxy_url"].toString();
    if(object.contains("height"))
        _height = object["height"].toInt();
    if(object.contains("width"))
        _width = object["width"].toInt();
}

QJsonObject QDiscordAttachment::serialize() const
{
    QJsonObject object;

    object["id"] = _id ? _id.toString() : QJsonValue();
    object["filename"] = _filename;
    object["size"] = _size;
    object["url"] = _url;
    object["proxy_url"] = _proxyUrl;
    if(_height.has_value())
        object["height"] = _height.value();
    if(_width.has_value())
        object["width"] = _width.value();

    return object;
}

bool QDiscordAttachment::operator==(const QDiscordAttachment& other) const
{
    return _id == other._id;
}

bool QDiscordAttachment::operator!=(const QDiscordAttachment& other) const
{
    return !operator==(other);
}

bool QDiscordAttachment::operator<(const QDiscordAttachment& other) const
{
    return _id < other._id;
}

bool QDiscordAttachment::operator>(const QDiscordAttachment& other) const
{
    return _id > other._id;
}

bool QDiscordAttachment::operator<=(const QDiscordAttachment& other) const
{
    return _id <= other._id;
}

bool QDiscordAttachment::operator>=(const QDiscordAttachment& other) const
{
    return _id >= other._id;
}

QDiscordAttachment::operator bool() const
{
    return _id;
}

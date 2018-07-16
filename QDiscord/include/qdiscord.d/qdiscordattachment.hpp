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

#ifndef QDISCORDATTACHMENT_HPP
#define QDISCORDATTACHMENT_HPP

#include "qdiscord.d/external/optional/optional.hpp"
#include "qdiscord.d/qdiscordid.hpp"
#include <QJsonObject>

class QDiscordAttachment
{
public:
    static QSharedPointer<QDiscordAttachment>
    fromJson(const QJsonObject& object);

    QDiscordAttachment(const QJsonObject& object);
    QDiscordAttachment();
    ~QDiscordAttachment();

    void deserialize(const QJsonObject& object);
    QJsonObject serialize() const;

    QDiscordID id() const { return _id; }
    void setId(QDiscordID id) { _id = id; }
    QString filename() const { return _filename; }
    void setFilename(const QString& filename) { _filename = filename; }
    qint64 size() const { return _size; }
    void setSize(qint64 size) { _size = size; }
    QString url() const { return _url; }
    void setUrl(const QString& url) { _url = url; }
    QString proxyUrl() const { return _proxyUrl; }
    void setProxyUrl(const QString& proxyUrl) { _proxyUrl = proxyUrl; }
    std::experimental::optional<int> height() const { return _height; }
    void setHeight(int height) { _height = height; }
    void resetHeight() { _height.reset(); }
    std::experimental::optional<int> width() const { return _width; }
    void setWidth(int width) { _width = width; }
    void resetWidth() { _width.reset(); }

    bool isNull() const { return _id.isNull(); }
    operator bool() const;

    bool operator==(const QDiscordAttachment& other) const;
    bool operator!=(const QDiscordAttachment& other) const;
    bool operator<(const QDiscordAttachment& other) const;
    bool operator>(const QDiscordAttachment& other) const;
    bool operator<=(const QDiscordAttachment& other) const;
    bool operator>=(const QDiscordAttachment& other) const;

private:
    QDiscordID _id;
    QString _filename;
    qint64 _size = -1;
    QString _url;
    QString _proxyUrl;
    std::experimental::optional<int> _height;
    std::experimental::optional<int> _width;
};

Q_DECLARE_METATYPE(QDiscordAttachment)

#endif // QDISCORDATTACHMENT_HPP

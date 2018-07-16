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

#ifndef QDISCORDGAME_HPP
#define QDISCORDGAME_HPP

#include <QDebug>
#include <QJsonObject>

///\brief Represents a game object in the Discord API.
class QDiscordGame
{
public:
    static QSharedPointer<QDiscordGame> fromJson(const QJsonObject& object);
    /*!
     * \brief An enum holding different game types.
     *
     * Usually set when streaming. If an enum is not contained here,
     * UnknownType will be set.
     */
    enum class GameType : qint8
    {
        Default = 0,
        Streaming = 1,
        Unknown = -1
    };
    /*!
     * \brief Manual constructor for a game object. Defaults to an empty object.
     * \param name The game you wish to display for the status.
     * \param url The game URL for your status. Usually only used when
     * streaming.
     * \param type The game type. Set this if you wish to show a streaming
     * status.
     */
    QDiscordGame(QString name,
                 QString url = QString(),
                 GameType type = GameType::Default);
    QDiscordGame();
    ///\brief Creates an instance from the provided JSON object.
    QDiscordGame(const QJsonObject& object);
    ~QDiscordGame();
    void deserialize(const QJsonObject& object);
    QJsonObject serialize() const;
    ///\brief Returns the game name of this object.
    QString name() const { return _name; }
    void setName(const QString& name) { _name = name; }
    ///\brief Returns the URL of this game object.
    QString url() const { return _url; }
    void setUrl(const QString& url) { _url = url; }
    ///\brief Returns the type of this game object.
    GameType type() const { return _type; }
    void setType(GameType type) { _type = type; }
    bool isNull() const;
    operator bool() const;
    bool operator==(const QDiscordGame& other) const;
    bool operator!=(const QDiscordGame& other) const;
    bool operator<(const QDiscordGame& other) const;
    bool operator>(const QDiscordGame& other) const;
    bool operator<=(const QDiscordGame& other) const;
    bool operator>=(const QDiscordGame& other) const;

private:
    QString _name;
    QString _url;
    GameType _type;
};

Q_DECLARE_METATYPE(QDiscordGame)

#endif // QDISCORDGAME_HPP

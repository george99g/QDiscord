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

#ifndef QDISCORDMESSAGE_HPP
#define QDISCORDMESSAGE_HPP

#include "qdiscord.d/external/optional/optional.hpp"
#include "qdiscord.d/qdiscordattachment.hpp"
#include "qdiscord.d/qdiscordchannel.hpp"
#include "qdiscord.d/qdiscordguild.hpp"
#include "qdiscord.d/qdiscordmember.hpp"
#include <QFileInfo>
#include <functional>

class QDiscordRest;

/*!
 * \brief Represents a message in the Discord API.
 */
class QDiscordMessage
{
public:
    static QSharedPointer<QDiscordMessage> fromJson(const QJsonObject& object);

    struct TTS
    {
        TTS(bool b)
            : _b(b)
        {
        }
        operator bool() { return _b; }

    private:
        bool _b;
    };

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QJsonObject& data,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QString& content,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QString& content,
                       const QDiscordID& nonce,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QString& content,
                       TTS tts,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QString& content,
                       const QDiscordID& nonce,
                       TTS tts,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QString& content,
                       const QDiscordID& nonce,
                       TTS tts = false);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QString& content,
                       TTS tts = false);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QJsonObject& data);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QFileInfo& file);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QFileInfo& file,
                       const QJsonObject& data);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QFileInfo& file,
                       const QString& content,
                       const QDiscordID& nonce,
                       TTS tts = false);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QFileInfo& file,
                       const QString& content,
                       TTS tts = false);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QByteArray& file,
                       const QString& filename);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QByteArray& file,
                       const QString& filename,
                       const QJsonObject& data);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QByteArray& file,
                       const QString& filename,
                       const QString& content,
                       const QDiscordID& nonce,
                       TTS tts = false);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QByteArray& file,
                       const QString& filename,
                       const QString& content,
                       TTS tts = false);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QFileInfo& file,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QFileInfo& file,
                       const QJsonObject& data,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QFileInfo& file,
                       const QString& content,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QFileInfo& file,
                       const QString& content,
                       const QDiscordID& nonce,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QFileInfo& file,
                       const QString& content,
                       TTS tts,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QFileInfo& file,
                       const QString& content,
                       const QDiscordID& nonce,
                       TTS tts,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QByteArray& file,
                       const QString& filename,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QByteArray& file,
                       const QString& filename,
                       const QJsonObject& data,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QByteArray& file,
                       const QString& filename,
                       const QString& content,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QByteArray& file,
                       const QString& filename,
                       const QString& content,
                       const QDiscordID& nonce,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QByteArray& file,
                       const QString& filename,
                       const QString& content,
                       TTS tts,
                       std::function<void(QDiscordMessage)> callback);

    static void create(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QByteArray& file,
                       const QString& filename,
                       const QString& content,
                       const QDiscordID& nonce,
                       TTS tts,
                       std::function<void(QDiscordMessage)> callback);

    void send();

    void send(std::function<void(QDiscordMessage)> callback);

    static void edit(QDiscordRest& rest,
                     const QDiscordID& channel,
                     const QDiscordID& message,
                     const QString& newContent);

    static void edit(QDiscordRest& rest,
                     const QDiscordID& channel,
                     const QDiscordID& message,
                     const QJsonObject& data);

    static void edit(QDiscordRest& rest,
                     const QDiscordID& channel,
                     const QDiscordID& message,
                     const QString& newContent,
                     std::function<void(QDiscordMessage)> callback);

    static void edit(QDiscordRest& rest,
                     const QDiscordID& channel,
                     const QDiscordID& message,
                     const QJsonObject& data,
                     std::function<void(QDiscordMessage)> callback);

    void edit(const QString& newContent);

    void edit(const QString& newContent,
              std::function<void(QDiscordMessage)> callback);

    static void remove(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QDiscordID& message);

    static void remove(QDiscordRest& rest,
                       const QDiscordID& channel,
                       const QDiscordID& message,
                       std::function<void(bool)> callback);

    void remove();
    void remove(std::function<void(bool)> callback);

    static void bulkRemove(QDiscordRest& rest,
                           const QDiscordID& channel,
                           const QList<QDiscordID>& messages);

    static void bulkRemove(QDiscordRest& rest,
                           const QDiscordID& channel,
                           const QList<QDiscordID>& messages,
                           std::function<void(bool)> callback);

    static void get(QDiscordRest& rest,
                    const QDiscordID& channel,
                    const QDiscordID& message,
                    std::function<void(QDiscordMessage)> callback);

    static void ack(QDiscordRest& rest,
                    const QDiscordID& channel,
                    const QDiscordID& message);
    static void ack(QDiscordRest& rest,
                    const QDiscordID& channel,
                    const QDiscordID& message,
                    std::function<void(bool)> callback);

    void ack();
    void ack(std::function<void(bool)> callback);

    QDiscordMessage(const QJsonObject& object);
    QDiscordMessage();
    ~QDiscordMessage();
    void deserialize(const QJsonObject& object);
    QJsonObject serialize();
    ///\brief Returns the message's ID.
    QDiscordID id() const { return _id; }
    void setId(QDiscordID id) { _id = id; }
    ///\brief Returns the ID of the channel this message was sent in.
    QDiscordID channelId() const { return _channelId; }
    void setChannelId(QDiscordID id) { _id = id; }
    ///\brief Returns a pointer to the user that sent this message.
    QDiscordUser author() const { return _author; }
    void setAuthor(QDiscordUser author) { _author = author; }
    ///\brief Returns the message's contents.
    QString content() const { return _content; }
    void setContent(const QString& content) { _content = content; }
    ///\brief Returns the date at which the message was created.
    QDateTime timestamp() const { return _timestamp; }
    void setTimestamp(const QDateTime& timestamp) { _timestamp = timestamp; }
    std::experimental::optional<QDateTime> editedTimestamp() const
    {
        return _editedTimestamp;
    }
    void setEditedTimestamp(QDateTime editedTimestamp)
    {
        _editedTimestamp = editedTimestamp;
    }
    void resetEditedTimestamp() { _editedTimestamp.reset(); }
    ///\brief Returns whether the message will use text to speech.
    bool tts() const { return _tts; }
    void setTts(bool tts) { _tts = tts; }
    ///\brief Returns whether the message successfully mentioned everyone.
    bool mentionEveryone() const { return _mentionEveryone; }
    void setMentionEveryone(bool mentionEveryone)
    {
        _mentionEveryone = mentionEveryone;
    }
    ///\brief Returns a list of users mentioned in this message.
    QList<QDiscordUser> mentions() const { return _mentions; }
    void setMentions(QList<QDiscordUser> mentions) { _mentions = mentions; }
    QList<QDiscordAttachment> attachments() const { return _attachments; }
    void setAttachments(const QList<QDiscordAttachment>& attachments)
    {
        _attachments = attachments;
    }
    QDiscordID nonce() const { return _nonce; }
    void setNonce(QDiscordID nonce) { _nonce = nonce; }
    bool pinned() const { return _pinned; }
    void setPinned(bool pinned) { _pinned = pinned; }
    ///\brief Returns a pointer to the channel this message was sent in.
    QSharedPointer<QDiscordChannel> channel() const { return _channel; }
    void setChannel(QSharedPointer<QDiscordChannel> channel)
    {
        _channel = channel;
    }
    /*!
     * \brief Returns a pointer to the guild this message was sent in using
     * the channel parameter provided in the class' constructor.
     * \returns `nullptr` if the message was sent in a private channel and thus
     * the channel has no guild or if a channel was not provided in the class'
     * constructor.
     */
    QSharedPointer<QDiscordGuild> guild() const;
    QDiscordRest* rest() const { return _rest; }
    void setRest(QDiscordRest* rest) { _rest = rest; }
    bool isNull() const { return _id.isNull(); }
    operator bool() const;
    bool operator==(const QDiscordMessage& other) const;
    bool operator!=(const QDiscordMessage& other) const;
    bool operator>(const QDiscordMessage& other) const;
    bool operator<(const QDiscordMessage& other) const;
    bool operator<=(const QDiscordMessage& other) const;
    bool operator>=(const QDiscordMessage& other) const;

private:
    QDiscordID _id;
    QDiscordID _channelId;
    QDiscordUser _author;
    QString _content;
    QDateTime _timestamp;
    std::experimental::optional<QDateTime> _editedTimestamp;
    bool _tts = false;
    bool _mentionEveryone = false;
    QList<QDiscordUser> _mentions;
    QList<QDiscordAttachment> _attachments;
    QDiscordID _nonce;
    bool _pinned = false;
    QSharedPointer<QDiscordChannel> _channel;
    QDiscordRest* _rest = nullptr;
};

Q_DECLARE_METATYPE(QDiscordMessage)

#endif // QDISCORDMESSAGE_HPP

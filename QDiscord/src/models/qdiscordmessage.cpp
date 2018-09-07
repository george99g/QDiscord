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

#include "qdiscord.d/models/qdiscordmessage.hpp"
#include "qdiscord.d/qdiscordrest.hpp"
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QMimeDatabase>

QSharedPointer<QDiscordMessage>
QDiscordMessage::fromJson(const QJsonObject& object)
{
    QSharedPointer<QDiscordMessage> message(new QDiscordMessage());
    message->deserialize(object);
    return message;
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QJsonObject& data,
                             std::function<void(QDiscordMessage)> callback)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::sendMessage(channel),
                 data,
                 [&rest, callback](QNetworkReply* reply) {
                     QDiscordMessage m;
                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(m);
                         return;
                     }
                     m.deserialize(
                         QJsonDocument::fromJson(reply->readAll()).object());
                     m.setRest(&rest);
                     callback(m);
                 });
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QString& content,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", content}};
    create(rest, channel, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QString& content,
                             const QDiscordID& nonce,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", content}, {"nonce", nonce.toString()}};
    create(rest, channel, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QString& content,
                             TTS tts,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", content}, {"tts", static_cast<bool>(tts)}};
    create(rest, channel, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QString& content,
                             const QDiscordID& nonce,
                             TTS tts,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", content},
                        {"nonce", nonce.toString()},
                        {"tts", static_cast<bool>(tts)}};
    create(rest, channel, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QString& content,
                             const QDiscordID& nonce,
                             TTS tts)
{
    QJsonObject data = {{"content", content},
                        {"nonce", nonce.toString()},
                        {"tts", static_cast<bool>(tts)}};
    create(rest, channel, data);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QString& content,
                             TTS tts)
{
    QJsonObject data = {{"content", content}, {"tts", static_cast<bool>(tts)}};
    create(rest, channel, data);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QJsonObject& data)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::sendMessage(channel),
                 data);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QFileInfo& file)
{
    QFile* fileDevice = new QFile(file.canonicalFilePath());
    if(!fileDevice->open(QFile::ReadOnly))
    {
        delete fileDevice;
        return;
    }

    QHttpMultiPart* multiPart =
        new QHttpMultiPart(QHttpMultiPart::FormDataType);
    fileDevice->setParent(multiPart);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       "form-data; name=\"file\"; filename=\""
                           + QUrl::toPercentEncoding(file.fileName()) + "\"");
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QMimeDatabase().mimeTypeForFile(file).name());
    filePart.setBodyDevice(fileDevice);
    multiPart->append(filePart);

    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::sendMessage(channel),
                 multiPart,
                 [multiPart](QNetworkReply* reply) {
                     Q_UNUSED(reply);

                     delete multiPart;
                 });
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QFileInfo& file,
                             const QJsonObject& data)
{
    QFile* fileDevice = new QFile(file.canonicalFilePath());
    if(!fileDevice->open(QFile::ReadOnly))
    {
        delete fileDevice;
        return;
    }

    QHttpMultiPart* multiPart =
        new QHttpMultiPart(QHttpMultiPart::FormDataType);
    fileDevice->setParent(multiPart);

    QHttpPart payloadPart;
    payloadPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                          "form-data; name=\"payload_json\"");
    payloadPart.setHeader(QNetworkRequest::ContentTypeHeader,
                          "application/json");
    payloadPart.setBody(QJsonDocument(data).toJson());
    multiPart->append(payloadPart);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       "form-data; name=\"file\"; filename=\""
                           + QUrl::toPercentEncoding(file.fileName()) + "\"");
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QMimeDatabase().mimeTypeForFile(file).name());
    filePart.setBodyDevice(fileDevice);
    multiPart->append(filePart);

    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::sendMessage(channel),
                 multiPart,
                 [multiPart](QNetworkReply* reply) {
                     Q_UNUSED(reply);

                     delete multiPart;
                 });
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QFileInfo& file,
                             const QString& content,
                             const QDiscordID& nonce,
                             QDiscordMessage::TTS tts)
{
    QJsonObject data = {{"content", content},
                        {"nonce", nonce.toString()},
                        {"tts", static_cast<bool>(tts)}};

    QDiscordMessage::create(rest, channel, file, data);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QFileInfo& file,
                             const QString& content,
                             QDiscordMessage::TTS tts)
{
    QJsonObject data = {{"content", content}, {"tts", static_cast<bool>(tts)}};

    QDiscordMessage::create(rest, channel, file, data);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QByteArray& file,
                             const QString& filename)
{
    QHttpMultiPart* multiPart =
        new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       "form-data; name=\"file\"; filename=\""
                           + QUrl::toPercentEncoding(filename) + "\"");
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QMimeDatabase().mimeTypeForData(file).name());
    filePart.setBody(file);
    multiPart->append(filePart);

    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::sendMessage(channel),
                 multiPart,
                 [multiPart](QNetworkReply* reply) {
                     Q_UNUSED(reply);

                     delete multiPart;
                 });
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QByteArray& file,
                             const QString& filename,
                             const QJsonObject& data)
{
    QHttpMultiPart* multiPart =
        new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart payloadPart;
    payloadPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                          "form-data; name=\"payload_json\"");
    payloadPart.setHeader(QNetworkRequest::ContentTypeHeader,
                          "application/json");
    payloadPart.setBody(QJsonDocument(data).toJson());
    multiPart->append(payloadPart);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       "form-data; name=\"file\"; filename=\""
                           + QUrl::toPercentEncoding(filename) + "\"");
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QMimeDatabase().mimeTypeForData(file).name());
    filePart.setBody(file);
    multiPart->append(filePart);

    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::sendMessage(channel),
                 multiPart,
                 [multiPart](QNetworkReply* reply) {
                     Q_UNUSED(reply);

                     delete multiPart;
                 });
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QByteArray& file,
                             const QString& filename,
                             const QString& content,
                             const QDiscordID& nonce,
                             QDiscordMessage::TTS tts)
{
    QJsonObject data = {{"content", content},
                        {"nonce", nonce.toString()},
                        {"tts", static_cast<bool>(tts)}};

    QDiscordMessage::create(rest, channel, file, filename, data);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QByteArray& file,
                             const QString& filename,
                             const QString& content,
                             QDiscordMessage::TTS tts)
{
    QJsonObject data = {{"content", content}, {"tts", static_cast<bool>(tts)}};

    QDiscordMessage::create(rest, channel, file, filename, data);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QFileInfo& file,
                             std::function<void(QDiscordMessage)> callback)
{
    QFile* fileDevice = new QFile(file.canonicalFilePath());
    if(!fileDevice->open(QFile::ReadOnly))
    {
        delete fileDevice;

        callback(QDiscordMessage());

        return;
    }

    QHttpMultiPart* multiPart =
        new QHttpMultiPart(QHttpMultiPart::FormDataType);
    fileDevice->setParent(multiPart);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       "form-data; name=\"file\"; filename=\""
                           + QUrl::toPercentEncoding(file.fileName()) + "\"");
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QMimeDatabase().mimeTypeForFile(file).name());
    filePart.setBodyDevice(fileDevice);
    multiPart->append(filePart);

    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::sendMessage(channel),
                 multiPart,
                 [multiPart, callback](QNetworkReply* reply) {
                     delete multiPart;

                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(QDiscordMessage());
                         return;
                     }

                     callback(QDiscordMessage(
                         QJsonDocument::fromJson(reply->readAll()).object()));
                 });
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QFileInfo& file,
                             const QJsonObject& data,
                             std::function<void(QDiscordMessage)> callback)
{
    QFile* fileDevice = new QFile(file.canonicalFilePath());
    if(!fileDevice->open(QFile::ReadOnly))
    {
        delete fileDevice;

        callback(QDiscordMessage());

        return;
    }

    QHttpMultiPart* multiPart =
        new QHttpMultiPart(QHttpMultiPart::FormDataType);
    fileDevice->setParent(multiPart);

    QHttpPart payloadPart;
    payloadPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                          "form-data; name=\"payload_json\"");
    payloadPart.setHeader(QNetworkRequest::ContentTypeHeader,
                          "application/json");
    payloadPart.setBody(QJsonDocument(data).toJson());
    multiPart->append(payloadPart);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       "form-data; name=\"file\"; filename=\""
                           + QUrl::toPercentEncoding(file.fileName()) + "\"");
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QMimeDatabase().mimeTypeForFile(file).name());
    filePart.setBodyDevice(fileDevice);
    multiPart->append(filePart);

    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::sendMessage(channel),
                 multiPart,
                 [multiPart, callback](QNetworkReply* reply) {
                     delete multiPart;

                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(QDiscordMessage());
                         return;
                     }

                     callback(QDiscordMessage(
                         QJsonDocument::fromJson(reply->readAll()).object()));
                 });
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QFileInfo& file,
                             const QString& content,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", content}};

    QDiscordMessage::create(rest, channel, file, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QFileInfo& file,
                             const QString& content,
                             const QDiscordID& nonce,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {
        {"content", content},
        {"nonce", nonce.toString()},
    };

    QDiscordMessage::create(rest, channel, file, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QFileInfo& file,
                             const QString& content,
                             QDiscordMessage::TTS tts,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", content}, {"tts", static_cast<bool>(tts)}};

    QDiscordMessage::create(rest, channel, file, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QFileInfo& file,
                             const QString& content,
                             const QDiscordID& nonce,
                             QDiscordMessage::TTS tts,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", content},
                        {"nonce", nonce.toString()},
                        {"tts", static_cast<bool>(tts)}};

    QDiscordMessage::create(rest, channel, file, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QByteArray& file,
                             const QString& filename,
                             std::function<void(QDiscordMessage)> callback)
{
    QHttpMultiPart* multiPart =
        new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       "form-data; name=\"file\"; filename=\""
                           + QUrl::toPercentEncoding(filename) + "\"");
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QMimeDatabase().mimeTypeForData(file).name());
    filePart.setBody(file);
    multiPart->append(filePart);

    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::sendMessage(channel),
                 multiPart,
                 [multiPart, callback](QNetworkReply* reply) {
                     delete multiPart;

                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(QDiscordMessage());
                         return;
                     }

                     callback(QDiscordMessage(
                         QJsonDocument::fromJson(reply->readAll()).object()));
                 });
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QByteArray& file,
                             const QString& filename,
                             const QJsonObject& data,
                             std::function<void(QDiscordMessage)> callback)
{
    QHttpMultiPart* multiPart =
        new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart payloadPart;
    payloadPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                          "form-data; name=\"payload_json\"");
    payloadPart.setHeader(QNetworkRequest::ContentTypeHeader,
                          "application/json");
    payloadPart.setBody(QJsonDocument(data).toJson());
    multiPart->append(payloadPart);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       "form-data; name=\"file\"; filename=\""
                           + QUrl::toPercentEncoding(filename) + "\"");
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QMimeDatabase().mimeTypeForData(file).name());
    filePart.setBody(file);
    multiPart->append(filePart);

    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::sendMessage(channel),
                 multiPart,
                 [multiPart, callback](QNetworkReply* reply) {
                     delete multiPart;

                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(QDiscordMessage());
                         return;
                     }

                     callback(QDiscordMessage(
                         QJsonDocument::fromJson(reply->readAll()).object()));
                 });
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QByteArray& file,
                             const QString& filename,
                             const QString& content,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", content}};

    QDiscordMessage::create(rest, channel, file, filename, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QByteArray& file,
                             const QString& filename,
                             const QString& content,
                             const QDiscordID& nonce,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", content}, {"nonce", nonce.toString()}};

    QDiscordMessage::create(rest, channel, file, filename, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QByteArray& file,
                             const QString& filename,
                             const QString& content,
                             QDiscordMessage::TTS tts,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", content}, {"tts", static_cast<bool>(tts)}};

    QDiscordMessage::create(rest, channel, file, filename, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QByteArray& file,
                             const QString& filename,
                             const QString& content,
                             const QDiscordID& nonce,
                             QDiscordMessage::TTS tts,
                             std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", content},
                        {"nonce", nonce.toString()},
                        {"tts", static_cast<bool>(tts)}};

    QDiscordMessage::create(rest, channel, file, filename, data, callback);
}

void QDiscordMessage::send()
{
    if(!_rest || _content.isEmpty())
        return;

    if(!_channelId)
    {
        if(_channel)
            _channelId = _channel->id();
        else
            return;
    }

    QJsonObject data = {{"content", _content}};
    if(_nonce)
        data["nonce"] = _nonce.toString();
    if(_tts)
        data["tts"] = _tts;

    QDiscordMessage::create(*_rest, _channelId, data);
}

void QDiscordMessage::send(std::function<void(QDiscordMessage)> callback)
{
    if(!_rest || _content.isEmpty())
    {
        callback(QDiscordMessage());
        return;
    }

    if(!_channelId)
    {
        if(_channel)
            _channelId = _channel->id();
        else
        {
            callback(QDiscordMessage());
            return;
        }
    }

    QJsonObject data = {{"content", _content}};
    if(_nonce)
        data["nonce"] = _nonce.toString();
    if(_tts)
        data["tts"] = _tts;

    QDiscordMessage::create(*_rest, _channelId, data, callback);
}

void QDiscordMessage::edit(QDiscordRest& rest,
                           const QDiscordID& channel,
                           const QDiscordID& message,
                           const QString& newContent)
{
    QJsonObject data = {{"content", newContent}};
    edit(rest, channel, message, data);
}

void QDiscordMessage::edit(QDiscordRest& rest,
                           const QDiscordID& channel,
                           const QDiscordID& message,
                           const QJsonObject& data)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::editMessage(channel, message),
                 data);
}

void QDiscordMessage::edit(QDiscordRest& rest,
                           const QDiscordID& channel,
                           const QDiscordID& message,
                           const QString& newContent,
                           std::function<void(QDiscordMessage)> callback)
{
    QJsonObject data = {{"content", newContent}};
    edit(rest, channel, message, data, callback);
}

void QDiscordMessage::edit(QDiscordRest& rest,
                           const QDiscordID& channel,
                           const QDiscordID& message,
                           const QJsonObject& data,
                           std::function<void(QDiscordMessage)> callback)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::editMessage(channel, message),
                 data,
                 [&rest, callback](QNetworkReply* reply) {
                     QDiscordMessage m;
                     if(reply->error() != QNetworkReply::NoError)
                     {
                         callback(m);
                         return;
                     }
                     m.deserialize(
                         QJsonDocument::fromJson(reply->readAll()).object());
                     m.setRest(&rest);
                     callback(m);
                 });
}

void QDiscordMessage::edit(const QString& newContent)
{
    if(!_rest || !_id)
        return;

    if(!_channelId)
    {
        if(_channel)
            _channelId = _channel->id();
        else
            return;
    }

    QDiscordMessage::edit(*_rest, _channelId, _id, newContent);
}

void QDiscordMessage::edit(const QString& newContent,
                           std::function<void(QDiscordMessage)> callback)
{
    if(!_rest || !_id)
    {
        callback(QDiscordMessage());
        return;
    }

    if(!_channelId)
    {
        if(_channel)
            _channelId = _channel->id();
        else
        {
            callback(QDiscordMessage());
            return;
        }
    }

    QDiscordMessage::edit(*_rest, _channelId, _id, newContent, callback);
}

void QDiscordMessage::remove(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QDiscordID& message)
{
    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::deleteMessage(channel, message));
}

void QDiscordMessage::remove(QDiscordRest& rest,
                             const QDiscordID& channel,
                             const QDiscordID& message,
                             std::function<void(bool)> callback)
{
    rest.request(
        QNetworkRequest(),
        QDiscordRoutes::Messages::deleteMessage(channel, message),
        [callback](QNetworkReply* reply) { callback(reply->error() == 204); });
}

void QDiscordMessage::remove()
{
    if(!_rest || !_id)
        return;

    if(!_channelId)
    {
        if(_channel)
            _channelId = _channel->id();
        else
            return;
    }

    QDiscordMessage::remove(*_rest, _channelId, _id);
}

void QDiscordMessage::remove(std::function<void(bool)> callback)
{
    if(!_rest || !_id)
    {
        callback(false);
        return;
    }

    if(!_channelId)
    {
        if(_channel)
            _channelId = _channel->id();
        else
        {
            callback(false);
            return;
        }
    }

    QDiscordMessage::remove(*_rest, _channelId, _id, callback);
}

void QDiscordMessage::bulkRemove(QDiscordRest& rest,
                                 const QDiscordID& channel,
                                 const QList<QDiscordID>& messages)
{
    QJsonObject data;

    QJsonArray array;
    for(const QDiscordID& message : messages)
        array.append(message.toString());
    data["messages"] = array;

    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::deleteMessages(channel),
                 data);
}

void QDiscordMessage::bulkRemove(QDiscordRest& rest,
                                 const QDiscordID& channel,
                                 const QList<QDiscordID>& messages,
                                 std::function<void(bool)> callback)
{
    QJsonObject data;

    QJsonArray array;
    for(const QDiscordID& message : messages)
        array.append(message.toString());
    data["messages"] = array;

    rest.request(
        QNetworkRequest(),
        QDiscordRoutes::Messages::deleteMessages(channel),
        data,
        [callback](QNetworkReply* reply) { callback(reply->error() == 204); });
}

void QDiscordMessage::get(QDiscordRest& rest,
                          const QDiscordID& channel,
                          const QDiscordID& message,
                          std::function<void(QDiscordMessage)> callback)
{
    rest.request(
        QNetworkRequest(),
        QDiscordRoutes::Messages::getMessage(channel, message),
        [&rest, callback](QNetworkReply* reply) {
            QDiscordMessage m;
            if(reply->error() != QNetworkReply::NoError)
                callback(m);
            else
            {
                m.deserialize(
                    QJsonDocument::fromJson(reply->readAll()).object());

                m.setRest(&rest);
                callback(m);
            }
        });
}

void QDiscordMessage::ack(QDiscordRest& rest,
                          const QDiscordID& channel,
                          const QDiscordID& message)
{
    QJsonObject data;

    if(rest.lastAckToken().isEmpty())
        data["token"] = QJsonValue();
    else
        data["token"] = rest.lastAckToken().rawToken();

    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::ackMessage(channel, message),
                 data,
                 [&rest](QNetworkReply* reply) {
                     if(reply->error() == QNetworkReply::NoError)
                     {
                         rest.setLastAckToken(QDiscordToken(
                             QJsonDocument::fromJson(reply->readAll())
                                 .object()["token"]
                                 .toString(),
                             QDiscordToken::Type::None));
                     }

                 });
}

void QDiscordMessage::ack(QDiscordRest& rest,
                          const QDiscordID& channel,
                          const QDiscordID& message,
                          std::function<void(bool)> callback)
{
    QJsonObject data;

    if(rest.lastAckToken().isEmpty())
        data["token"] = QJsonValue();
    else
        data["token"] = rest.lastAckToken().rawToken();

    rest.request(QNetworkRequest(),
                 QDiscordRoutes::Messages::ackMessage(channel, message),
                 data,
                 [&rest, callback](QNetworkReply* reply) {
                     if(reply->error() == QNetworkReply::NoError)
                     {
                         rest.setLastAckToken(QDiscordToken(
                             QJsonDocument::fromJson(reply->readAll())
                                 .object()["token"]
                                 .toString(),
                             QDiscordToken::Type::None));
                         callback(true);
                     }
                     else
                         callback(false);

                 });
}

void QDiscordMessage::ack()
{
    if(!_rest || !_id || !_channelId)
        return;

    QDiscordMessage::ack(*_rest, _channelId, _id);
}

void QDiscordMessage::ack(std::function<void(bool)> callback)
{
    if(!_rest || !_id || !_channelId)
    {
        callback(false);

        return;
    }

    QDiscordMessage::ack(*_rest, _channelId, _id, callback);
}

QDiscordMessage::QDiscordMessage(const QJsonObject& object)
{
    deserialize(object);

#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << "QDiscordMessage(" << this << ") constructed";
#endif
}

QDiscordMessage::QDiscordMessage()
{
#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << "QDiscordMessage(" << this << ") constructed";
#endif
}

QDiscordMessage::~QDiscordMessage()
{
#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << "QDiscordMessage(" << this << ") destroyed";
#endif
}

void QDiscordMessage::deserialize(const QJsonObject& object)
{
    deserializeJson(object);
    /* The channel pointer is handled by the calling class */
}

QJsonObject QDiscordMessage::serialize()
{
    return serializeJson();
}

QSharedPointer<QDiscordGuild> QDiscordMessage::guild() const
{
    return _channel ? _channel->guild() : QSharedPointer<QDiscordGuild>();
}

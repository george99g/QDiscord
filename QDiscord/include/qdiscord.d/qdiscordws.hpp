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

#ifndef QDISCORDWS_HPP
#define QDISCORDWS_HPP

#include "qdiscord.d/qdiscordabstractstate.hpp"
#include "qdiscord.d/qdiscordjsondecoder.hpp"
#include "qdiscord.d/qdiscordtoken.hpp"
#include "qdiscord.d/qdiscorduseragent.hpp"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QSysInfo>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QWebSocket>

class QDiscordRest;

class QDiscordWs : public QObject
{
    Q_OBJECT
public:
    enum class GatewayOp : int
    {
        Dispatch = 0,
        Heartbeat = 1,
        Identify = 2,
        StatusUpdate = 3,
        VoiceStateUpdate = 4,
        VoiceServerPing = 5,
        Resume = 6,
        Reconnect = 7,
        RequestGuildMembers = 8,
        InvalidSession = 9,
        Hello = 10,
        HeartbeatAck = 11
    };
    enum class Encoding : quint8
    {
        JSON = 0,
        ETF = 1
    };
    enum class ConnectionState : quint8
    {
        Disconnected = 0,
        UnexpetedlyDisconnected = 1,
        Connecting = 2,
        Connected = 3,
        HelloReceived = 4,
        IdentifySent = 5,
        ResumeSent = 6,
        Authenticated = 7,
        Disconnecting = 8
    };
    enum class Error : quint8
    {
        NoError = 0,
        AlreadyConnected = 1,
        NotConnected = 2,
        EncodingNotSupported = 3,
        NoToken = 4,
        WebSocketError = 5,
        UnknownError = 255
    };

    static void getGateway(QDiscordRest& rest,
                           std::function<void(QString)> callback);

    explicit QDiscordWs(QDiscordAbstractState* state = nullptr,
                        QObject* parent = nullptr);
    bool open(QString endpoint, QDiscordToken token = QDiscordToken());
    bool open(QUrl endpoint, QDiscordToken token = QDiscordToken());
    void close(QWebSocketProtocol::CloseCode closeCode =
                   QWebSocketProtocol::CloseCodeNormal);
    void abort();
    void reconnect();
    Error error() const { return _error; }
    QString errorString() const;
    quint8 version() const { return _version; }
    bool setVersion(quint8 version);
    Encoding encoding() const { return _encoding; }
    bool setEncoding(Encoding encoding);
    int maxReconnectTime() const { return _maxReconnectTime; }
    void setMaxReconnectTime(int maxReconnectTime)
    {
        _maxReconnectTime = maxReconnectTime;
    }
    int reconnectTime() const { return _reconnectTime; }
    int maxReconnectAttempts() const { return _maxReconnectAttempts; }
    void setMaxReconnectAttempts(int maxReconnectAttempts)
    {
        _maxReconnectAttempts = maxReconnectAttempts;
    }
    int reconnectAttempt() const { return _reconnectAttempt; }
    QDiscordToken token() const { return _token; }
    bool setToken(const QDiscordToken& token);
    QString sessionId() const { return _sessionId; }
    quint32 latestSequence() const { return _latestSequence; }
    QDiscordAbstractState* state() { return _state; }
    void setState(QDiscordAbstractState* state);
    ConnectionState connectionState() const { return _cState; }
    QWebSocket& webSocket() { return _ws; }

    QDiscordUserAgent userAgent() const { return _userAgent; }
    void setUserAgent(const QDiscordUserAgent& userAgent)
    {
        _userAgent = userAgent;
    }
signals:
    void error(Error error);
    void loggedIn();
    void authFail();
    void connectionStateChanged(ConnectionState state);
    void disconnected();

private:
    void setCState(ConnectionState state);
    void wsConnected();
    void wsDisconnected();
    void wsError(QAbstractSocket::SocketError);
    void wsMessage(const QString& message);
    void dispatchHelloJson(const QJsonObject& object);
    void dispatchAck();
    void dispatchReconnect();
    void dispatchDispatchJson(const QJsonObject& d, const QString& t);
    void dispatchInvalidSession();
    void heartbeatTick();
    void sendIdentify();
    void sendResume();
    Error _error;
    quint8 _version = 6;
    Encoding _encoding = Encoding::JSON;
    QUrl _endpoint;
    QDiscordToken _token;
    QString _sessionId;
    qint32 _latestSequence = -1;
    QDiscordAbstractState* _state;
    QDiscordJsonDecoder _jsonDecoder;
    // QDiscordEtfDecoder _etfDecoder;
    QDiscordUserAgent _userAgent;
    ConnectionState _cState = ConnectionState::Disconnected;
    ConnectionState _lastCState = _cState;
    QWebSocket _ws;
    QTimer _heartbeatTimer;
    int _reconnectTime = 100;
    int _maxReconnectTime = 60000;
    int _reconnectAttempt = 0;
    int _maxReconnectAttempts = -1;
    bool _ackReceived = true;
};

#endif // QDISCORDWS_HPP

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

#include "qdiscordws.hpp"
#include "qdiscorduseragent.hpp"
#include "qdiscordrest.hpp"

namespace {
	const QMap<QString, void (QDiscordAbstractState::*)(const QJsonObject&)> jsonDispatchTable =
	{
		{"READY", &QDiscordAbstractState::readyReceived},
		{"CHANNEL_CREATE", &QDiscordAbstractState::channelCreateReceived},
		{"CHANNEL_UPDATE", &QDiscordAbstractState::channelUpdateReceived},
		{"CHANNEL_DELETE", &QDiscordAbstractState::channelDeleteReceived},
		{"GUILD_CREATE", &QDiscordAbstractState::guildCreateReceived},
		{"GUILD_UPDATE", &QDiscordAbstractState::guildUpdateReceived},
		{"GUILD_DELETE", &QDiscordAbstractState::guildDeleteReceived},
		{"GUILD_BAN_ADD", &QDiscordAbstractState::guildBanAddReceived},
		{"GUILD_BAN_REMOVE", &QDiscordAbstractState::guildBanRemoveReceived},
		{"GUILD_EMOJIS_UPDATE",
			&QDiscordAbstractState::guildEmojisUpdateReceived},
		{"GUILD_INTEGRATIONS_UPDATE",
			&QDiscordAbstractState::guildIntegrationsUpdateReceived},
		{"GUILD_MEMBER_ADD",
			&QDiscordAbstractState::guildMemberAddReceived},
		{"GUILD_MEMBER_REMOVE",
			&QDiscordAbstractState::guildMemberRemoveReceived},
		{"GUILD_MEMBER_UPDATE",
			&QDiscordAbstractState::guildMemberUpdateReceived},
		{"GUILD_MEMBERS_CHUNK",
			&QDiscordAbstractState::guildMembersChunkReceived},
		{"GUILD_ROLE_CREATE", &QDiscordAbstractState::guildRoleCreateReceived},
		{"GUILD_ROLE_UPDATE", &QDiscordAbstractState::guildRoleUpdateReceived},
		{"GUILD_ROLE_DELETE", &QDiscordAbstractState::guildRoleDeleteReceived},
		{"MESSAGE_CREATE", &QDiscordAbstractState::messageCreateReceived},
		{"MESSAGE_UPDATE", &QDiscordAbstractState::messageUpdateReceived},
		{"MESSAGE_DELETE", &QDiscordAbstractState::messageDeleteReceived},
		{"MESSSAGE_DELETE_BULK",
			&QDiscordAbstractState::messageDeleteBulkReceived},
		{"PRESENCE_UPDATE", &QDiscordAbstractState::presenceUpdateReceived},
		{"TYPING_START", &QDiscordAbstractState::typingStartReceived},
		{"USER_UPDATE", &QDiscordAbstractState::userUpdateReceived},
		{"VOICE_STATE_UPDATE",
			&QDiscordAbstractState::voiceStateUpdateReceived},
		{"VOICE_SERVER_UPDATE",
			&QDiscordAbstractState::voiceServerUpdateReceived},
	};
	//TODO: Add a map for ETF support here
}

void QDiscordWs::getGateway(QDiscordRest& rest,
							 std::function<void (QString)> callback)
{
	rest.request(
				QNetworkRequest(),
				QDiscordRoutes::Self::gateway(),
				[callback](QNetworkReply* reply)
	{
		if(!callback)
			return;
		if(reply->error() != QNetworkReply::NoError)
		{
			callback(QString());
			return;
		}

		callback(QJsonDocument::fromJson(reply->readAll())
				 .object()["url"].toString());
	}
	);
}

QDiscordWs::QDiscordWs(QDiscordAbstractState* state, QObject* parent)
: QObject(parent), _state(state)
{
	connect(&_ws, &QWebSocket::connected, this, &QDiscordWs::wsConnected);
	connect(&_ws, &QWebSocket::disconnected, this, &QDiscordWs::wsDisconnected);
	connect(&_ws, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
			this, &QDiscordWs::wsError);
	connect(&_ws, &QWebSocket::textMessageReceived,
			this, &QDiscordWs::wsMessage);
	_heartbeatTimer.stop(); //Being explicit here because timers are finicky
	_heartbeatTimer.setSingleShot(false);
	connect(&_heartbeatTimer, &QTimer::timeout,
			this, &QDiscordWs::heartbeatTick);
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"constructed";
#endif
}

bool QDiscordWs::open(QString endpoint, QDiscordToken token)
{
	if(_ws.state() != QAbstractSocket::UnconnectedState)
	{
		_error = Error::AlreadyConnected;
		emit error(Error::AlreadyConnected);
		return false;
	}
	if(!token.isEmpty())
		_token = token;
	if(_token.isEmpty())
	{
		_error = Error::NoToken;
		emit error(Error::NoToken);
		return false;
	}
	if(!endpoint.contains('?')) //A little bit hacky, but it should work
	{
		if(!endpoint.endsWith('/'))
			endpoint.append('/');
		endpoint.append("?v=").append(QString::number(_version));
		endpoint.append("&encoding=");
		switch(_encoding)
		{
		default:
		case Encoding::JSON:
			endpoint.append("json");
			break;
		case Encoding::ETF:
			endpoint.append("etf");
			break;
		}
	}
	_endpoint = endpoint;
	setCState(ConnectionState::Connecting);
	_ws.open(QUrl(endpoint));
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"WebSocket connecting to"<<endpoint;
#endif
	return true;
}

void QDiscordWs::close(QWebSocketProtocol::CloseCode closeCode)
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"WebSocket closing";
#endif
	setCState(ConnectionState::Disconnecting);
	_ws.close(closeCode);
}

void QDiscordWs::abort()
{
	setCState(ConnectionState::Disconnected);
	_ws.abort();
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"WebSocket aborted";
#endif
}

void QDiscordWs::reconnect()
{
	_ws.close(QWebSocketProtocol::CloseCodeAbnormalDisconnection);
}

QString QDiscordWs::errorString() const
{
	switch(_error)
	{
	case Error::NoError:
		return "No error occurred.";
	case Error::AlreadyConnected:
		return "The WebSocket is already connected. Disconnect first.";
	case Error::NotConnected:
		return "The WebSocket is not connected. Connect first.";
	case Error::EncodingNotSupported:
		return "The encoding you requested is not supported.";
	case Error::NoToken:
		return "No token was provided.";
	case Error::WebSocketError:
		return "An error occurred with the WebSocket.";
	case Error::UnknownError:
	default:
		return "Unknown error.";
	}
}

bool QDiscordWs::setVersion(quint8 version)
{
	if(_cState != ConnectionState::Disconnected)
	{
		_error = Error::AlreadyConnected;
		emit error(Error::AlreadyConnected);
		return false;
	}
	_version = version;
	return true;
}

bool QDiscordWs::setEncoding(Encoding encoding)
{
	if(_cState != ConnectionState::Disconnected)
	{
		_error = Error::AlreadyConnected;
		emit error(Error::AlreadyConnected);
		return false;
	}
	switch(encoding)
	{
	case Encoding::JSON:
		_encoding = encoding;
		return true;
	case Encoding::ETF:
	default:
		_error = Error::EncodingNotSupported;
		emit error(Error::EncodingNotSupported);
		return false;
	}
}

bool QDiscordWs::setToken(const QDiscordToken& token)
{
	if(_cState != ConnectionState::Disconnected)
	{
		_error = Error::AlreadyConnected;
		emit error(Error::AlreadyConnected);
		return false;
	}
	_token = token;
	return true;
}

void QDiscordWs::setCState(QDiscordWs::ConnectionState state)
{
	_lastCState = _cState;
	_cState = state;
	emit connectionStateChanged(state);
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"State changed. Previous state:"
			<<static_cast<int>(_lastCState)
			<<"Current state:"<<static_cast<int>(_cState);
#endif
	switch(_cState)
	{
	case ConnectionState::Disconnected:
		_sessionId.clear();;
		_endpoint.clear();
		_token.clear();
		_latestSequence = -1;
		_heartbeatTimer.stop();
		_ackReceived = true;
		_heartbeatTimer.stop();
		_reconnectTime = 100;
		_reconnectAttempt = 0;
		emit disconnected();
		break;
	case ConnectionState::UnexpetedlyDisconnected:
		_ackReceived = true;
		_heartbeatTimer.stop();
		QTimer::singleShot(_reconnectTime, [this]()
		{
			if(_maxReconnectAttempts > -1)
			{
				if(_reconnectAttempt >= _maxReconnectAttempts)
					abort();
			}
			if(_maxReconnectTime / 5 <= _reconnectTime)
				_reconnectTime = _maxReconnectTime;
			else
				_reconnectTime *= 5;
#ifdef QDISCORD_LIBRARY_DEBUG
			qDebug()<<this<<"Attempting reconnect"<<_reconnectAttempt + 1
					<< "out of" << _maxReconnectAttempts
					<<"Next attempt in "<<_reconnectTime/1000.<<"seconds";
#endif
			open(_endpoint, _token);
		});
		break;
	case ConnectionState::HelloReceived:
		if(_sessionId.isEmpty() || _latestSequence < 0)
			sendIdentify();
		else
			sendResume();
		break;
	case ConnectionState::Authenticated:
		_reconnectAttempt = 0;
		_reconnectTime = 100;
	default:
		break;
	}
}

void QDiscordWs::wsConnected()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"WebSocket connected.";
#endif
	setCState(ConnectionState::Connected);
}

void QDiscordWs::wsDisconnected()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"WebSocket disconnected. Close code:"<<_ws.closeCode()
			<<"Close reason:"<<_ws.closeReason();
#endif
	if(_ws.closeCode() == 4004)
	{
		setCState(ConnectionState::Disconnected);
		emit authFail();
	}
	if(_cState == ConnectionState::Disconnecting)
		setCState(ConnectionState::Disconnected);
	else
		setCState(ConnectionState::UnexpetedlyDisconnected);
}

void QDiscordWs::wsError(QAbstractSocket::SocketError)
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"WebSocket error:"<<_ws.errorString();
#endif
	_error = Error::WebSocketError;
	emit error(Error::WebSocketError);
}

void QDiscordWs::wsMessage(const QString& message)
{
	if(_encoding == Encoding::JSON)
	{
		QJsonObject obj = QJsonDocument::fromJson(message.toUtf8()).object();
		if(obj.isEmpty())
		{
#ifdef QDISCORD_LIBRARY_DEBUG
			qDebug()<<this<<"Invalid JSON received."<<"Message:"<<message;
#endif
		}
		switch(static_cast<GatewayOp>(obj["op"].toInt()))
		{
		case GatewayOp::Hello:
			dispatchHelloJson(obj["d"].toObject());
			return;
		case GatewayOp::Reconnect:
			dispatchReconnect();
			return;
		case GatewayOp::HeartbeatAck:
			dispatchAck();
			return;
		case GatewayOp::InvalidSession:
			dispatchInvalidSession();
			return;
		case GatewayOp::Dispatch:
			if(obj.contains("s"))
				_latestSequence = obj["s"].toInt(-1);
			dispatchDispatchJson(obj["d"].toObject(), obj["t"].toString());
			return;
		default:
#ifdef QDISCORD_LIBRARY_DEBUG
			qDebug()<<this<<"Unknown operation received. OP:"
				   <<obj["d"].toString();
#endif
			return;
		}
	}
	//TODO: Add ETF handler
}

void QDiscordWs::dispatchHelloJson(const QJsonObject& object)
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"Hello received.";
#endif
	_heartbeatTimer.start(object["heartbeat_interval"].toInt());
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"Beating every"<<
			  _heartbeatTimer.interval()/1000.<<"seconds.";
#endif
	setCState(ConnectionState::HelloReceived);
}

void QDiscordWs::dispatchAck()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"Received ACK";
#endif
	_ackReceived = true;
}

void QDiscordWs::dispatchReconnect()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"Reconnect received, reconnecting";
#endif
	reconnect();
}

void QDiscordWs::dispatchDispatchJson(const QJsonObject& d, const QString& t)
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"Received Dispatch. t:" << t;
#endif

	if(t == "READY")
	{
		if(_state)
			_state->reset();
		setCState(ConnectionState::Authenticated);
		emit loggedIn();
		_sessionId = d["session_id"].toString();
	}
	else if(t == "RESUMED")
		setCState(ConnectionState::Authenticated);
	if(jsonDispatchTable.keys().contains(t))
	{
		if(_state)
			(_state->*jsonDispatchTable[t])(d);
	}
	else
	{
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this<<"No dispatch table entry found for " << t;
#endif
	}
}

void QDiscordWs::dispatchInvalidSession()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"Received Invalid Session";
#endif
	_sessionId.clear();
	_latestSequence = -1;
	QTimer::singleShot(5000, [this]()
	{
		sendIdentify();
	});
}

void QDiscordWs::heartbeatTick()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"Heartbeat tick";
#endif
	if(!_ws.isValid())
	{
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this<<"WebSocket is not valid, stopping timer";
#endif
		_heartbeatTimer.stop();
		return;
	}
	if(_ackReceived)
		_ackReceived = false;
	else
	{
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this<<"No ACK to previous heartbeat, reconnecting";
#endif
		reconnect();
		return;
	}
	if(_encoding == Encoding::JSON)
	{
		QJsonObject heartbeatObject =
		{
			{"op", static_cast<int>(GatewayOp::Heartbeat)},
			{"d", _latestSequence < 0 ? QJsonValue() : _latestSequence}
		};
		_ws.sendTextMessage(QJsonDocument(heartbeatObject).toJson());
		_ws.flush();
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this<<"Sent heartbeat";
#endif
	}
	//TODO: Add ETF support
}

void QDiscordWs::sendIdentify()
{
	if(_token.isEmpty())
	{
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this<<"No token specified for sendIdentify";
#endif
		abort();
		return;
	}
	if(_encoding == Encoding::JSON)
	{
		QJsonObject obj = {
			{"op", static_cast<int>(GatewayOp::Identify)},
			{"d", QJsonObject({
				{"token", _token.fullToken()},
				{"properties", QJsonObject({
					{"$os", QSysInfo::kernelType()},
					{"$browser", QDiscordUserAgent::global().libraryName()},
					{"$device", QDiscordUserAgent::global().libraryName()},
					{"$referrer", ""},
					{"$referring_domain", ""}
				})},
				{"compress", false},
				{"large_threshold", 250}
			})}
		};
		setCState(ConnectionState::IdentifySent);
		_ws.sendTextMessage(QJsonDocument(obj).toJson());
		_ws.flush();
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this<<"Sent identify";
#endif
	}
	//TODO: Add ETF support
}

void QDiscordWs::sendResume()
{
	if(_token.isEmpty())
	{
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this<<"No token specified for sendResume";
#endif
		reconnect();
		return;
	}
	if(_sessionId.isEmpty())
	{
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this<<"No session ID specified for sendResume";
#endif
		reconnect();
		return;
	}
	if(_latestSequence < 0)
	{
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this<<"Invalid sequence specified for sendResume";
#endif
		reconnect();
		return;
	}

	if(_encoding == Encoding::JSON)
	{
		QJsonObject obj = {
			{"op", static_cast<int>(GatewayOp::Resume)},
			{"d", QJsonObject({
				{"token", _token.fullToken()},
				{"session_id", _sessionId},
				{"seq", _latestSequence}
			})}
		};
		setCState(ConnectionState::ResumeSent);
		_ws.sendTextMessage(QJsonDocument(obj).toJson());
		_ws.flush();
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this<<"Sent resume";
#endif
	}
	//TODO: Add ETF support
}

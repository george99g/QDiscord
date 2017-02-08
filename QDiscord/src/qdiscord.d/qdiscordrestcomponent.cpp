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

#include "qdiscordrestcomponent.hpp"
#include <QBuffer>

QDiscordRestComponent::QDiscordRestComponent(QObject* parent) : QObject(parent)
{
	_self = QSharedPointer<QDiscordUser>();
	_loggedIn = false;

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"constructed";
#endif
}

QDiscordRestComponent::~QDiscordRestComponent()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"destroyed";
#endif
}

void QDiscordRestComponent::login(const QString& email, const QString& password)
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"acquiring token via email and password";
#endif
	qWarning()<<"Logging in via email and password is deprecated";
	qWarning()<<"Please use a token instead";
	qWarning()<<"See the following link for more information:";
	qWarning()<<"https://github.com/hammerandchisel/discord-api-docs/issues/69";
	if(!_authorization.isEmpty())
	{
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this
		<<"attempted to acquire a token while one is already stored";
#endif
		return;
	}
	QJsonObject object;
	object["email"] = email;
	object["password"] = password;
	doRequest(QDiscordRoutes::Self::login(),
	[this](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			_authorization.clear();
			_loggedIn = false;
			emit loginFailed(reply->error());
			return;
		}
		QString tokenString =
				QJsonDocument::fromJson(
					reply->readAll()
					).object().value("token").toString();
		_authorization = QDiscordToken(tokenString, QDiscordToken::Type::None);
		_loggedIn = true;
		emit tokenVerified(_authorization);
	});
}

void QDiscordRestComponent::login(const QDiscordToken& token)
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"verifying token";
#endif
	if(!_authorization.isEmpty())
	{
#ifdef QDISCORD_LIBRARY_DEBUG
		qDebug()<<this
		<<"attempted to verify a token while one is already stored";
#endif
		return;
	}
	_authorization = token;
	doRequest(QDiscordRoutes::Self::login(),
	[this, token](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			_authorization.clear();
			_loggedIn = false;
			emit loginFailed(reply->error());
			return;
		}
		_loggedIn = true;
		emit tokenVerified(token);
	});
}

void QDiscordRestComponent::sendMessage(const QString& content,
										QSharedPointer<QDiscordChannel> channel,
										bool tts)
{
	if(!_loggedIn)
		return;

	if(!channel)
		return;

	QDiscordID id = channel->id();
	QJsonObject object;
	object["content"] = content;

	if(tts)
		object["tts"] = true;

	doRequest(object, QDiscordRoutes::Messages::sendMessage(id),
	[this, channel](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			emit messageSendFailed(reply->error());
			return;
		}
		QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
		QJsonObject object = document.object();
		QDiscordMessage message(object, channel);
		emit messageSent(message);
	});
}

void QDiscordRestComponent::sendMessage(const QString& content,
										const QDiscordID& channelId,
										bool tts)
{
	if(!_loggedIn)
		return;

	QJsonObject object;
	object["content"] = content;

	if(tts)
		object["tts"] = true;

	doRequest(object, QDiscordRoutes::Messages::sendMessage(channelId),
	[this](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			emit messageSendFailed(reply->error());
			return;
		}
		QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
		QJsonObject object = document.object();
		QDiscordMessage message(object, QSharedPointer<QDiscordChannel>());
		emit messageSent(message);
	});
}

void QDiscordRestComponent::deleteMessage(QDiscordMessage message)
{
	deleteMessage(message.channelId(), message.id());
}

void QDiscordRestComponent::deleteMessage(const QDiscordID& channelId,
										  const QDiscordID& messageId)
{
	if(!_loggedIn)
		return;

	doRequest(QDiscordRoutes::Messages::deleteMessage(channelId, messageId),
	[this, messageId](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			emit messageDeleteFailed(reply->error());
			return;
		}
		emit messageDeleted(messageId);
	});
}

void QDiscordRestComponent::deleteMessages(
		const QList<QDiscordMessage>& messages)
{
	QList<QDiscordID> ids;
	QDiscordID channel;
	for(const QDiscordMessage& message : messages)
	{
		ids.append(message.id());
		if(!channel && message.channelId())
			channel = message.channelId();
	}
	deleteMessages(ids, channel);
}

void QDiscordRestComponent::deleteMessages(QList<QDiscordID> messages,
										   QDiscordID channel)
{
	QJsonArray messageIDArray;

	for(const QDiscordID& message : messages)
		messageIDArray.append(message.toString());

	QJsonObject object;
	object["messages"] = messageIDArray;

	doRequest(object, QDiscordRoutes::Messages::deleteMessages(channel),
	[this, messages, channel](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			emit messagesDeleteFailed(messages, channel);
			return;
		}
		emit messagesDeleted(messages, channel);
	});
}

void QDiscordRestComponent::editMessage(const QString& newContent,
										QDiscordMessage message)
{
	editMessage(newContent, message.channelId(), message.id());
}

void QDiscordRestComponent::editMessage(const QString& newContent,
										const QDiscordID& channelId,
										const QDiscordID& messageId)
{
	if(!_loggedIn)
		return;
	QJsonObject object;
	object["content"] = newContent;

	doRequest(object,
			  QDiscordRoutes::Messages::editMessage(channelId, messageId),
	[this](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			emit messageEditFailed(reply->error());
			return;
		}
		QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
		QJsonObject object = document.object();
		QDiscordMessage newMessage(object,
								   QSharedPointer<QDiscordChannel>());
		emit messageEdited(newMessage);
	});
}

void QDiscordRestComponent::logout()
{
	if(_authorization.isEmpty())
		return;
	if(!_loggedIn)
		return;
	_self.reset();
	if(_authorization.type() != QDiscordToken::Type::None)
	{
		_authorization.clear();
		_loggedIn = false;
		emit loggedOut();
		return;
	}
	QJsonObject object;
	object["token"] = _authorization.fullToken();
	_authorization.clear();
	_loggedIn = false;
	doRequest(object, QDiscordRoutes::Self::logout(),
	[this](QNetworkReply*)
	{
		emit loggedOut();
	});
}

void QDiscordRestComponent::getEndpoint()
{
	if(!_loggedIn)
		return;
	doRequest(QDiscordRoutes::Self::gateway(),
	[this](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			emit endpointAcquireFailed(reply->error());
			return;
		}
		emit endpointAcquired(
					QJsonDocument::fromJson(
						reply->readAll()
						).object().value("url").toString()
					);
	});
}

void
QDiscordRestComponent::setChannelName(const QString& name,
										QSharedPointer<QDiscordChannel> channel)
{
	if(!_loggedIn)
		return;

	if(!channel)
		return;

	setChannelName(name, channel->id());
}

void QDiscordRestComponent::setChannelName(const QString& name,
										   const QDiscordID& channelId)
{
	if(!_loggedIn)
		return;

	QJsonObject object;
	object["name"] = name;

	doRequest(object, QDiscordRoutes::Channels::modifyChannel(channelId),
	[this](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			emit channelUpdateFailed(reply->error());
			return;
		}
		QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
		QJsonObject object = document.object();
		QDiscordChannel updatedChannel(object);
		emit channelUpdated(updatedChannel);
	});
}

void QDiscordRestComponent::setChannelPosition(
			int position,
			QSharedPointer<QDiscordChannel> channel
		)
{
	if(!_loggedIn)
		return;

	if(!channel)
		return;

	setChannelPosition(position, channel->id());
}

void QDiscordRestComponent::setChannelPosition(int position,
											   const QDiscordID& channelId)
{
	if(!_loggedIn)
		return;

	QJsonObject object;
	object["position"] = position;

	doRequest(object, QDiscordRoutes::Channels::modifyChannel(channelId),
	[this](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			emit channelUpdateFailed(reply->error());
			return;
		}
		QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
		QJsonObject object = document.object();
		QDiscordChannel updatedChannel(object);
		emit channelUpdated(updatedChannel);
	});
}

void QDiscordRestComponent::setChannelTopic(
			const QString& topic,
			QSharedPointer<QDiscordChannel> channel
		)
{
	if(!_loggedIn)
		return;

	if(!channel)
		return;

	if(channel->type() != QDiscordChannel::ChannelType::Text)
		return;

	setChannelTopic(topic, channel->id());
}

void QDiscordRestComponent::setChannelTopic(const QString& topic,
											const QDiscordID& channelId)
{
	if(!_loggedIn)
		return;

	QJsonObject object;
	object["topic"] = topic;

	doRequest(object, QDiscordRoutes::Channels::modifyChannel(channelId),
	[this](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			emit channelUpdateFailed(reply->error());
			return;
		}
		QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
		QJsonObject object = document.object();
		QDiscordChannel updatedChannel(object);
		emit channelUpdated(updatedChannel);
	});
}

void QDiscordRestComponent::setChannelBitrate(
			int bitrate,
			QSharedPointer<QDiscordChannel> channel
		)
{
	if(!_loggedIn)
		return;

	if(!channel)
		return;

	if(channel->type() != QDiscordChannel::ChannelType::Voice)
		return;

	setChannelBitrate(bitrate, channel->id());
}

void QDiscordRestComponent::setChannelBitrate(int bitrate,
											  const QDiscordID& channelId)
{
	if(!_loggedIn)
		return;

	QJsonObject object;
	object["bitrate"] = bitrate;

	doRequest(object, QDiscordRoutes::Channels::modifyChannel(channelId),
	[this](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			emit channelUpdateFailed(reply->error());
			return;
		}
		QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
		QJsonObject object = document.object();
		QDiscordChannel updatedChannel(object);
		emit channelUpdated(updatedChannel);
	});
}

void QDiscordRestComponent::setChannelUserLimit(
		int limit,
		QSharedPointer<QDiscordChannel> channel
		)
{
	if(!_loggedIn)
		return;

	if(!channel)
		return;

	if(channel->type() != QDiscordChannel::ChannelType::Voice)
		return;

	setChannelUserLimit(limit, channel->id());
}

void QDiscordRestComponent::setChannelUserLimit(int limit,
												const QDiscordID& channelId)
{
	if(!_loggedIn)
		return;

	QJsonObject object;
	object["user_limit"] = limit;

	doRequest(object, QDiscordRoutes::Channels::modifyChannel(channelId),
	[this](QNetworkReply* reply)
	{
		if(reply->error() != QNetworkReply::NoError)
		{
			emit channelUpdateFailed(reply->error());
			return;
		}
		QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
		QJsonObject object = document.object();
		QDiscordChannel updatedChannel(object);
		emit channelUpdated(updatedChannel);
	});
}

void QDiscordRestComponent::setSelf(QSharedPointer<QDiscordUser> self)
{
	_self = self;
}

template<class Functor>
void QDiscordRestComponent::doRequest(const QDiscordRoute& url,
									  Functor function)
{
	QNetworkRequest request(QUrl(url.fullUrl()));
	if(!_authorization.isEmpty())
	{
		request.setRawHeader("Authorization",
					_authorization.fullToken().toUtf8());
	}
	request.setHeader(QNetworkRequest::UserAgentHeader,
					  QDiscordUtilities::userAgent());
	QNetworkReply* reply;
	switch(url.method())
	{
	case QDiscordRoute::Method::DELETE:
		reply = _manager.deleteResource(request);
		break;
	case QDiscordRoute::Method::GET:
		reply = _manager.get(request);
		break;
	case QDiscordRoute::Method::PATCH:
	{
		QBuffer* buffer = new QBuffer();
		buffer->open(QBuffer::ReadWrite);
		request.setHeader(QNetworkRequest::ContentLengthHeader, 0);
		reply = _manager.sendCustomRequest(request, "PATCH", buffer);
		connect(reply, &QNetworkReply::finished, buffer, &QBuffer::deleteLater);
	}
		break;
	case QDiscordRoute::Method::POST:
		request.setHeader(QNetworkRequest::ContentLengthHeader, 0);
		reply = _manager.post(request, "");
		break;
	case QDiscordRoute::Method::PUT:
		request.setHeader(QNetworkRequest::ContentLengthHeader, 0);
		reply = _manager.put(request, "");
		break;
	default:
		return;
	}
	connect(reply, &QNetworkReply::finished, this, [this, function](){
		QNetworkReply* reply = static_cast<QNetworkReply*>(sender());

		if(!reply)
			return;

		function(reply);

		reply->deleteLater();
	});
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"did"<<url;
#endif
}

template<class Functor>
void QDiscordRestComponent::doRequest(const QJsonObject& object,
									  const QDiscordRoute& url,
									  Functor function)
{
	QNetworkRequest request(QUrl(url.fullUrl()));
	if(!_authorization.isEmpty())
	{
		request.setRawHeader("Authorization",
							 _authorization.fullToken().toUtf8());
	}
	request.setHeader(QNetworkRequest::UserAgentHeader,
					  QDiscordUtilities::userAgent());
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	QNetworkReply* reply;
	QJsonDocument document;
	switch(url.method())
	{
	case QDiscordRoute::Method::DELETE:
		reply = _manager.deleteResource(request);
		break;
	case QDiscordRoute::Method::GET:
		reply = _manager.get(request);
		break;
	case QDiscordRoute::Method::PATCH:
	{
		QBuffer* buffer = new QBuffer();
		buffer->open(QBuffer::ReadWrite);

		document.setObject(object);
		buffer->write(document.toJson(QJsonDocument::Compact));
		buffer->seek(0);
		reply = _manager.sendCustomRequest(request, "PATCH", buffer);
		connect(reply, &QNetworkReply::finished, buffer, &QBuffer::deleteLater);
	}
		break;
	case QDiscordRoute::Method::POST:
		document.setObject(object);
		reply = _manager.post(request, document.toJson(QJsonDocument::Compact));
		break;
	case QDiscordRoute::Method::PUT:
		document.setObject(object);
		reply = _manager.put(request, document.toJson(QJsonDocument::Compact));
		break;
	default:
		return;
	}
	connect(reply, &QNetworkReply::finished, this, [this, function](){
		QNetworkReply* reply = static_cast<QNetworkReply*>(sender());

		if(!reply)
			return;

		function(reply);

		reply->deleteLater();
	});
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"did"<<url;
#endif
}

template<class Functor>
void QDiscordRestComponent::doRequest(const QJsonArray& array,
									  const QDiscordRoute& url,
									  Functor function)
{
	QNetworkRequest request(QUrl(url.fullUrl()));
	if(!_authorization.isEmpty())
	{
		request.setRawHeader("Authorization",
							 _authorization.fullToken().toUtf8());
	}
	request.setHeader(QNetworkRequest::UserAgentHeader,
					  QDiscordUtilities::userAgent());
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	QNetworkReply* reply;
	QJsonDocument document;
	switch(url.method())
	{
	case QDiscordRoute::Method::DELETE:
		reply = _manager.deleteResource(request);
		break;
	case QDiscordRoute::Method::GET:
		reply = _manager.get(request);
		break;
	case QDiscordRoute::Method::PATCH:
	{
		QBuffer* buffer = new QBuffer();
		buffer->open(QBuffer::ReadWrite);
		document.setArray(array);
		buffer->write(document.toJson(QJsonDocument::Compact));
		buffer->seek(0);
		reply = _manager.sendCustomRequest(request, "PATCH", buffer);
		connect(reply, &QNetworkReply::finished, buffer, &QBuffer::deleteLater);
	}
		break;
	case QDiscordRoute::Method::POST:
		document.setArray(array);
		reply = _manager.post(request, document.toJson(QJsonDocument::Compact));
		break;
	case QDiscordRoute::Method::PUT:
		document.setArray(array);
		reply = _manager.put(request, document.toJson(QJsonDocument::Compact));
		break;
	default:
		return;
	}
	connect(reply, &QNetworkReply::finished, this, [this, function](){
		QNetworkReply* reply = static_cast<QNetworkReply*>(sender());

		if(!reply)
			return;

		function(reply);

		reply->deleteLater();
	});
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<this<<"did"<<url;
#endif
}

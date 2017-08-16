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

#include "qdiscordmessage.hpp"
#include "qdiscordrest.hpp"

QSharedPointer<QDiscordMessage> QDiscordMessage::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordMessage> message(new QDiscordMessage());
	message->deserialize(object);
	return message;
}

void QDiscordMessage::create(QDiscordRest& rest,
							 const QDiscordID& channel,
							 const QJsonObject& data,
							 std::function<void (QDiscordMessage)> callback)
{
	rest.request(
				QNetworkRequest(),
				QDiscordRoutes::Messages::sendMessage(channel),
				data,
				[&rest, callback](QNetworkReply* reply)
	{
		if(!callback)
			return;
		QDiscordMessage m;
		if(reply->error() != QNetworkReply::NoError)
		{
			callback(m);
			return;
		}
		m.deserialize(QJsonDocument::fromJson(reply->readAll()).object());
		m.setRest(&rest);
		callback(m);
	}
	);
}

void QDiscordMessage::create(QDiscordRest& rest,
							 const QDiscordID& channel,
							 const QString& content,
							 std::function<void(QDiscordMessage)> callback)
{
	QJsonObject data = {
		{"content", content}
	};
	create(rest, channel, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
							 const QDiscordID& channel,
							 const QString& content,
							 const QDiscordID& nonce,
							 std::function<void(QDiscordMessage)> callback)
{
	QJsonObject data = {
		{"content", content},
		{"nonce", nonce.toString()}
	};
	create(rest, channel, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
							 const QDiscordID& channel,
							 const QString& content,
							 TTS tts,
							 std::function<void(QDiscordMessage)> callback)
{
	QJsonObject data = {
		{"content", content},
		{"tts", static_cast<bool>(tts)}
	};
	create(rest, channel, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
							 const QDiscordID& channel,
							 const QString& content,
							 const QDiscordID& nonce,
							 TTS tts,
							 std::function<void(QDiscordMessage)> callback)
{
	QJsonObject data = {
		{"content", content},
		{"nonce", nonce.toString()},
		{"tts", static_cast<bool>(tts)}
	};
	create(rest, channel, data, callback);
}

void QDiscordMessage::create(QDiscordRest& rest,
							 const QDiscordID& channel,
							 const QString& content,
							 const QDiscordID& nonce,
							 TTS tts)
{
	QJsonObject data = {
		{"content", content},
		{"nonce", nonce.toString()},
		{"tts", static_cast<bool>(tts)}
	};
	create(rest, channel, data);
}

void QDiscordMessage::create(QDiscordRest& rest,
							 const QDiscordID& channel,
							 const QString& content,
							 TTS tts)
{
	QJsonObject data = {
		{"content", content},
		{"tts", static_cast<bool>(tts)}
	};
	create(rest, channel, data);
}

void QDiscordMessage::create(QDiscordRest& rest,
							 const QDiscordID& channel,
							 const QJsonObject& data)
{
	rest.request(
				QNetworkRequest(),
				QDiscordRoutes::Messages::sendMessage(channel),
				data
				);
}

void QDiscordMessage::send()
{
	if(!_rest)
		return;

	if(_content.isEmpty())
		return;

	if(!_channelId)
	{
		if(_channel)
			_channelId = _channel->id();
		else
			return;
	}

	QJsonObject data = {
		{"content", _content}
	};
	if(_nonce)
		data["nonce"] = _nonce.toString();
	if(_tts)
		data["tts"]	= _tts;

	QDiscordMessage::create(*_rest, _channelId, data);
}

void QDiscordMessage::send(std::function<void(QDiscordMessage)> callback)
{
	if(!_rest)
		return;

	if(_content.isEmpty())
	{
		if(callback)
			callback(QDiscordMessage());
		return;
	}

	if(!_channelId)
	{
		if(_channel)
			_channelId = _channel->id();
		else
		{
			if(callback)
				callback(QDiscordMessage());
			return;
		}
	}

	QJsonObject data = {
		{"content", _content}
	};
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
	QJsonObject data = {
		{"content", newContent}
	};
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
						   std::function<void (QDiscordMessage)> callback)
{
	QJsonObject data = {
		{"content", newContent}
	};
	edit(rest, channel, message, data, callback);
}

void QDiscordMessage::edit(QDiscordRest& rest,
						   const QDiscordID& channel,
						   const QDiscordID& message,
						   const QJsonObject& data,
						   std::function<void (QDiscordMessage)> callback)
{
	rest.request(
				QNetworkRequest(),
				QDiscordRoutes::Messages::editMessage(channel, message),
				data,
				[&rest, callback](QNetworkReply* reply)
	{
		if(!callback)
			return;
		QDiscordMessage m;
		if(reply->error() != QNetworkReply::NoError)
		{
			callback(m);
			return;
		}
		m.deserialize(QJsonDocument::fromJson(reply->readAll()).object());
		m.setRest(&rest);
		callback(m);
	}
	);
}

void QDiscordMessage::edit(const QString& newContent)
{
	if(!_rest)
		return;

	if(!_id)
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
						   std::function<void (QDiscordMessage)> callback)
{
	if(!_rest)
		return;

	if(!_id)
	{
		if(callback)
			callback(QDiscordMessage());
		return;
	}

	if(!_channelId)
	{
		if(_channel)
			_channelId = _channel->id();
		else
		{
			if(callback)
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
							 std::function<void (bool)> callback)
{
	rest.request(
				QNetworkRequest(),
				QDiscordRoutes::Messages::deleteMessage(channel, message),
				[callback](QNetworkReply* reply)
	{
		if(callback)
			callback(reply->error() ==204);
	}
	);
}

void QDiscordMessage::remove()
{
	if(!_rest)
		return;

	if(!_id)
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

void QDiscordMessage::remove(std::function<void (bool)> callback)
{
	if(!_rest)
		return;

	if(!_id)
	{
		if(callback)
			callback(false);
		return;
	}

	if(!_channelId)
	{
		if(_channel)
			_channelId = _channel->id();
		else
		{
			if(callback)
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
								 std::function<void (bool)> callback)
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
				[callback](QNetworkReply* reply)
	{
		if(callback)
			callback(reply->error() == 204);
	}
	);
}

void QDiscordMessage::get(QDiscordRest& rest,
						  const QDiscordID& channel,
						  const QDiscordID& message,
						  std::function<void (QDiscordMessage)> callback)
{
	rest.request(
				QNetworkRequest(),
				QDiscordRoutes::Messages::getMessage(channel, message),
				[&rest, callback](QNetworkReply* reply)
	{
		if(callback)
		{
			QDiscordMessage m;
			if(reply->error() != QNetworkReply::NoError)
				callback(m);
			else
			{
				m.deserialize(
							QJsonDocument::fromJson(reply->readAll()).object()
							);

				m.setRest(&rest);
				callback(m);
			}
		}
	}
	);
}

QDiscordMessage::QDiscordMessage(const QJsonObject& object)
{
	deserialize(object);

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordMessage("<<this<<") constructed";
#endif
}

QDiscordMessage::QDiscordMessage()
{
	_mentionEveryone = false;
	_tts = false;
	_pinned = false;
	_rest = nullptr;

#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordMessage("<<this<<") constructed";
#endif
}

QDiscordMessage::~QDiscordMessage()
{
#ifdef QDISCORD_LIBRARY_DEBUG
	qDebug()<<"QDiscordMessage("<<this<<") destroyed";
#endif
}

void QDiscordMessage::deserialize(const QJsonObject& object)
{
	_id = QDiscordID(object["id"].toString());
	_channelId = QDiscordID(object["channel_id"].toString());
	_author = QDiscordUser(object["author"].toObject());
	_content = object["content"].toString();
	_timestamp = QDateTime::fromString(object["timestamp"].toString(),
			Qt::ISODateWithMs);
	if(!object["edited_timestamp"].isNull())
	{
		_editedTimestamp =
				QDateTime::fromString(object["edited_timestamp"].toString(),
										Qt::ISODateWithMs);
	}
	_tts = object["tts"].toBool(false);
	_mentionEveryone = object["mention_everyone"].toBool(false);
	_nonce = QDiscordID(object["nonce"].toString());
	QJsonArray mentionsArray = object["mentions"].toArray();
	for(const QJsonValue item : mentionsArray)
	{
		_mentions.append(QDiscordUser(item.toObject()));
	}
	_pinned = object["pinned"].toBool(false);
	/* The channel pointer is handled by the calling class */
}

QJsonObject QDiscordMessage::serialize()
{
	QJsonObject object;

	object["id"] = _id.toString();
	object["channel_id"] = _channelId.toString();
	{
		QJsonObject user = _author.serialize();

		if(user["bot"].toBool(false) == false)
			user.remove("bot");
		if(user["mfa_enabled"].toBool(false) == false)
			user.remove("mfa_enabled");

		object["author"] = user;
	}
	object["content"] = _content;
	{
		object["timestamp"] = _timestamp.toTimeSpec(Qt::OffsetFromUTC)
										.toString(Qt::ISODateWithMs);
	}
	if(_editedTimestamp.has_value())
	{
		object["edited_timestamp"] =
				_editedTimestamp.value()
								.toTimeSpec(Qt::OffsetFromUTC)
								.toString(Qt::ISODateWithMs);
	}
	else
		object["edited_timestamp"] = QJsonValue();
	object["tts"] = _tts;
	object["mention_everyone"] = _mentionEveryone;
	QJsonArray mentions;
	for(const QDiscordUser& u : _mentions)
	{
		mentions.append(u.serialize());
	}
	object["mentions"] = mentions;
	if(_nonce.isNull())
		object["nonce"] = QJsonValue();
	else
		object["nonce"] = _nonce.toString();
	object["pinned"] = _pinned;

	return object;
}

QSharedPointer<QDiscordGuild> QDiscordMessage::guild() const
{
	return _channel ? _channel->guild() : QSharedPointer<QDiscordGuild>();
}

bool QDiscordMessage::operator ==(const QDiscordMessage& other) const
{
	if(isNull() || other.isNull())
		return false;
	return _id == other._id;
}

bool QDiscordMessage::operator !=(const QDiscordMessage& other) const
{
	return !operator==(other);
}

bool QDiscordMessage::operator >(const QDiscordMessage& other) const
{
	return _id > other._id;
}

bool QDiscordMessage::operator <(const QDiscordMessage& other) const
{
	return _id < other._id;
}

bool QDiscordMessage::operator <=(const QDiscordMessage& other) const
{
	return _id <= other._id;
}

bool QDiscordMessage::operator >=(const QDiscordMessage& other) const
{
	return _id >= other._id;
}

QDiscordMessage::operator bool() const
{
	return _id;
}

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

#ifndef QDISCORDJSONDECODER_HPP
#define QDISCORDJSONDECODER_HPP

#include "qdiscord.d/qdiscordabstractstate.hpp"
#include "qdiscord.d/qdiscordchannel.hpp"
#include "qdiscord.d/qdiscordmember.hpp"
#include "qdiscord.d/qdiscordmessage.hpp"
#include "qdiscord.d/qdiscorduser.hpp"
#include <QObject>

class QDiscordJsonDecoder : QObject
{
    Q_OBJECT
public:
    QDiscordJsonDecoder(QObject* parent = nullptr);

    QDiscordAbstractState* state() const { return _state; }
    void setState(QDiscordAbstractState* state) { _state = state; }

    void input(const QJsonObject& d, const QString& t);

private:
    void readyReceived(const QJsonObject& object);
    void channelCreateReceived(const QJsonObject& object);
    void channelUpdateReceived(const QJsonObject& object);
    void channelDeleteReceived(const QJsonObject& object);
    void guildCreateReceived(const QJsonObject& object);
    void guildUpdateReceived(const QJsonObject& object);
    void guildDeleteReceived(const QJsonObject& object);
    void guildBanAddReceived(const QJsonObject& object);
    void guildBanRemoveReceived(const QJsonObject& object);
    void guildEmojisUpdateReceived(const QJsonObject& object);
    void guildIntegrationsUpdateReceived(const QJsonObject& object);
    void guildMemberAddReceived(const QJsonObject& object);
    void guildMemberRemoveReceived(const QJsonObject& object);
    void guildMemberUpdateReceived(const QJsonObject& object);
    void guildMembersChunkReceived(const QJsonObject& object);
    void guildRoleCreateReceived(const QJsonObject& object);
    void guildRoleUpdateReceived(const QJsonObject& object);
    void guildRoleDeleteReceived(const QJsonObject& object);
    void messageCreateReceived(const QJsonObject& object);
    void messageUpdateReceived(const QJsonObject& object);
    void messageDeleteReceived(const QJsonObject& object);
    void messageDeleteBulkReceived(const QJsonObject& object);
    void presenceUpdateReceived(const QJsonObject& object);
    void typingStartReceived(const QJsonObject& object);
    void userUpdateReceived(const QJsonObject& object);
    void voiceStateUpdateReceived(const QJsonObject& object);
    void voiceServerUpdateReceived(const QJsonObject& object);

    static const QMap<QString,
                      void (QDiscordJsonDecoder::*)(const QJsonObject&)>
        _dispatchTable;

    QDiscordAbstractState* _state = nullptr;
};

#endif // QDISCORDJSONDECODER_HPP

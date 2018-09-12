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

#ifndef QDISCORD_HPP
#define QDISCORD_HPP

#include "qdiscord.d/qdiscordrest.hpp"
#include "qdiscord.d/qdiscordstate.hpp"
#include "qdiscord.d/qdiscordws.hpp"
#include <QDebug>
#include <QObject>

class QDiscord : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDiscordToken token READ token WRITE setToken)
    Q_PROPERTY(bool isConnecting READ isConnecting STORED false)
    Q_PROPERTY(bool isConnected READ isConnected STORED false)

    Q_PROPERTY(QDiscordRest* rest READ restPtr)
    Q_PROPERTY(QDiscordWs* ws READ wsPtr)
    Q_PROPERTY(QDiscordState* state READ statePtr)

public:
    explicit QDiscord(QObject* parent = 0);

    Q_INVOKABLE void login(const QDiscordToken& token);
    void login(const QDiscordToken& token,
               const std::function<void(bool)>& callback);

    Q_INVOKABLE void logout();
    void logout(const std::function<void()>& callback);

    bool isConnecting() const;
    bool isConnected() const;

    QDiscordToken token() const { return _rest.token(); }
    void setToken(const QDiscordToken& token);

    QDiscordRest& rest() { return _rest; }
    QDiscordRest* restPtr() { return &_rest; }
    QDiscordWs& ws() { return _ws; }
    QDiscordWs* wsPtr() { return &_ws; }
    QDiscordState& state() { return _state; }
    QDiscordState* statePtr() { return &_state; }
signals:
    void loginFailed();
    void loggedIn();
    void loggedOut();

private:
    void wsConnectFailed();
    void wsDisconnected();
    void wsConnectSuccess();
    bool _tokenSet;
    bool _connected;
    std::function<void(bool)> _loginCallback;
    std::function<void()> _logoutCallback;
    QDiscordRest _rest;
    QDiscordWs _ws;
    QDiscordState _state;
};

#endif // QDISCORD_HPP

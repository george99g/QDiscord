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

#include "qdiscord.d/qdiscord.hpp"

QDiscord::QDiscord(QObject* parent)
    : QObject(parent)
{
#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << this << "constructed";
#endif
    _tokenSet = false;
    _connected = false;

    _ws.setState(&_state);
    _state.setRest(&_rest);

    connect(&_ws, &QDiscordWs::loggedIn, this, &QDiscord::wsConnectSuccess);
    connect(&_ws, &QDiscordWs::authFail, this, &QDiscord::wsConnectFailed);
    connect(&_ws, &QDiscordWs::disconnected, this, &QDiscord::wsDisconnected);
}

QDiscord::~QDiscord()
{
#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << this << "destroyed";
#endif
}

void QDiscord::login(const QDiscordToken& token)
{
    if(isConnected() || isConnecting())
        return;
    setToken(token);
    QDiscordWs::getGateway(_rest, [this](QString endpoint) {
        if(endpoint.isEmpty())
        {
            wsConnectFailed();
            return;
        }

        _ws.open(endpoint);
    });
}

void QDiscord::login(const QDiscordToken& token,
                     std::function<void(bool)> callback)
{
    if(isConnected() || isConnecting())
        return;
    _loginCallback = callback;
    login(token);
}

void QDiscord::logout()
{
    if(!isConnected() && !isConnecting())
        return;
    _ws.close();
    setToken(QDiscordToken());
}

void QDiscord::logout(std::function<void()> callback)
{
    if(!isConnected() && !isConnecting())
        return;
    _logoutCallback = callback;
    logout();
}

bool QDiscord::isConnecting() const
{
    return _tokenSet && !_connected;
}

bool QDiscord::isConnected() const
{
    return _connected;
}

void QDiscord::setToken(const QDiscordToken& token)
{
    _tokenSet = !token.isEmpty();
    _ws.setToken(token);
    _rest.setToken(token);
}

void QDiscord::wsConnectFailed()
{
    setToken(QDiscordToken());
    _connected = false;

    if(_loginCallback)
    {
        _loginCallback(false);
        _loginCallback = std::function<void(bool)>();
    }

    emit loginFailed();
}

void QDiscord::wsDisconnected()
{
    setToken(QDiscordToken());
    _connected = false;

    if(_logoutCallback)
    {
        _logoutCallback();
        _logoutCallback = std::function<void()>();
    }

    emit loggedOut();
}

void QDiscord::wsConnectSuccess()
{
    _connected = true;

    if(_loginCallback)
    {
        _loginCallback(true);
        _loginCallback = std::function<void(bool)>();
    }

    emit loggedIn();
}

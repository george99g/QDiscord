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

#include <QObject>
#include <QDebug>
#include "qdiscordrestcomponent.hpp"
#include "qdiscordwscomponent.hpp"
#include "qdiscordstatecomponent.hpp"

/*!
 * \brief This class helps the user interface with %QDiscord's components.
 *
 * It has helper methods for interfacing with the contained components.\n
 * It also handles communication between the components, allowing each component
 * to not be coupled to any other component.
 * \section example Example usage
 * As a start, you can log into Discord using QDiscord::login.\n
 * You can check whether the login was successful by using the
 * QDiscord::loginSuccess and QDiscord::loginFailed signals.\n
 * Once connected, you might be interested in some events. Call QDiscord::ws to
 * get a pointer to the state component, which will emit signals that might
 * interest you.\n
 * If you want to send some messages to Discord, call QDiscord::rest to get a
 * pointer to the REST component, which will give you some useful methods.\n
 * If you want to set your status or do something else which requires a
 * WebSocket connection, call QDiscord::ws to get a pointer to the WebSocket
 * component.\n
 * Once you're done, call QDiscord::logout to safely log out of Discord. The
 * QDiscord::loggedOut signal will be emitted once %QDiscord has logged out.
 * \see QDiscordRestComponent
 * \see QDiscordWsComponent
 * \see QDiscordStateComponent
 */
class QDiscord : public QObject
{
	Q_OBJECT
public:
	explicit QDiscord(QObject* parent = 0);
	~QDiscord();
	/*!
	 * \brief Automatically calls all component functions required to handle a
	 * standard Discord login via username and password.
	 *
	 * This might cause issues if you are manually interfacing with the
	 * components, in which case it is recommended to not call this and instead
	 * log in manually.
	 * \param email The Discord account to be used's e-mail.
	 * \param password The password to the supplied e-mail.
	 * \deprecated This method has been deprecated for bot usage by Discord.\n
	 * See https://discordapp.com/developers/docs/topics/oauth2#bot-vs-user-accounts\n
	 * and https://github.com/hammerandchisel/discord-api-docs/issues/69
	 */
	void login(const QString& email, const QString& password);
	/*!
	 * \brief Automatically calls all component functions required to handle a
	 * standard Discord login via a token.
	 *
	 * This might cause issues if you are manually interfacing with the
	 * components, in which case it is recommended to not call this and instead
	 * log in manually.
	 * \param token The token to use.
	 * \see QDiscordToken
	 */
	void login(const QDiscordToken& token);
	/*!
	 * \brief Handles logging out of the Discord API and destroying any state
	 * information in memory.
	 *
	 * The QDiscord::loggedOut signal will be emitted when everything has safely
	 * logged out.
	 */
	void logout();
	/*!
	 * \brief Returns a pointer to the REST component.
	 * \see QDiscordRestComponent
	 */
	QDiscordRestComponent* rest() {return &_rest;}
	/*!
	 * \brief Returns a pointer to the WebSocket component.
	 * \see QDiscordWsComponent
	 */
	QDiscordWsComponent* ws() {return &_ws;}
	/*!
	 * \brief Returns a pointer to the state component.
	 * \see QDiscordStateComponent
	 */
	QDiscordStateComponent* state() {return &_state;}
	///\brief Returns whether %QDiscord is connected.
	bool isConnected() const
	{return _connectionStatus == ConnectionStatus::Connected;}
	///\brief Returns whether %QDiscord is currently connecting.
	bool isConnecting() const;
	///\brief Returns whether %QDiscord is currently disconnected.
	bool isDisconnected() const
	{return _connectionStatus == ConnectionStatus::Disconnected;}
signals:
	/*!
	 * \brief Emitted when logging in has failed.
	 *
	 * Connect to component signals in order to get more information about the
	 * error that caused this.
	 */
	void loginFailed();
	///\brief Emitted when logging in is completed and successful.
	void loginSuccess();
	///\brief Emitted when logging out has finished.
	void loggedOut();
	/*!
	 * \brief Emitted when the WebSocket has disconnected.
	 *
	 * It should automatically reconnect, so error-handling code is not
	 * required here.
	 * \see QDiscordWsComponent
	 */
	void disconnected();
private:
	void tokenVerfified(QDiscordToken token);
	void endpointAcquired(const QString& endpoint);
	void connectComponents();
	void connectDiscordSignals();
	void disconnectDiscordSignals();
	void logoutFinished();
	void loginSuccessRecevied();
	void loginFailedReceived();
	QDiscordToken _token;
	QDiscordRestComponent _rest;
	QDiscordWsComponent _ws;
	QDiscordStateComponent _state;
	bool _signalsConnected;
	enum class ConnectionStatus {
		Disconnected, TokenVerifying, WsConnecting, Connected
	} _connectionStatus;
};

#endif // QDISCORD_HPP

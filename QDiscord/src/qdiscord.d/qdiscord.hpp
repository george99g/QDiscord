/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016 george99g
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
#include "qdiscord_global.hpp"
#include "qdiscordrestcomponent.hpp"
#include "qdiscordwscomponent.hpp"
#include "qdiscordstatecomponent.hpp"

/*!
 * \brief This class represents a single connection to the Discord API.
 *
 * It has helper methods for interfacing with the contained components.\n
 * It also handles communication between the components, allowing each
 * component to not be coupled to any other component.
 */
class QDISCORD_API QDiscord : public QObject
{
	Q_OBJECT
public:
	/*!
	 * \brief Standard QObject constructor.
	 * \param parent
	 */
	explicit QDiscord(QObject* parent = 0);
	/*!
	 * \brief Automatically calls all component functions required to handle a standard Discord login.
	 *
	 * This might cause issues if you are manually interfacing with the components, in which case
	 * it is recommended to not call this and instead log in manually.
	 * \param email The Discord account to be used's e-mail.
	 * \param password The password to the supplied e-mail.
	 * \deprecated This method is deprecated for bot usage.\n
	 * See https://discordapp.com/developers/docs/topics/oauth2#bot-vs-user-accounts
	 */
	void login(const QString& email, const QString& password);
	/*!
	 * \brief Automatically calls all component functions required to handle a standard Discord login.
	 *
	 * This might cause issues if you are manually interfacing with the components, in which case
	 * it is recommended to not call this and instead log in manually.
	 * \param token The token to use.
	 */
	void login(const QString& token);
	///\brief Handles logging out from the Discord API and destroying any state information in memory.
	void logout();
	///\brief Returns a pointer to the REST component.
	QDiscordRestComponent* rest() {return &_rest;}
	///\brief Returns a pointer to the WebSocket component.
	QDiscordWsComponent* ws() {return &_ws;}
	///\brief Returns a pointer to the state component.
	QDiscordStateComponent* state() {return &_state;}
signals:
	/*!
	 * \brief Emitted when logging in has failed.
	 *
	 * Connect to component signals in order to get more information about the error that caused this.
	 */
	void loginFailed();
	///\brief Emitted when logging in is completed and successful.
	void loginSuccess();
	///\brief Emitted when logging out has finished.
	void loggedOut();
	/*!
	 * \brief Emitted when the WebSocket has disconnected.
	 *
	 * It should automatically reconnect, so error-handling code is not required here.
	 */
	void disconnected();
private:
	void tokenVerfified(const QString& token);
	void endpointAcquired(const QString& endpoint);
	void connectComponents();
	void connectDiscordSignals();
	void disconnectDiscordSignals();
	void logoutFinished();
	void loginSuccessRecevied();
	void loginFailedReceived();
	QString _token;
	QDiscordRestComponent _rest;
	QDiscordWsComponent _ws;
	QDiscordStateComponent _state;
	bool _signalsConnected;
};

#endif // QDISCORD_HPP

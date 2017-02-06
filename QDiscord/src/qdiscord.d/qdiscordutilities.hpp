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

#ifndef QDISCORDUTILITIES_HPP
#define QDISCORDUTILITIES_HPP

#include <QString>
#include <QNetworkReply>
#include <QDateTime>
#include "qdiscordtokentype.hpp"

/*!
 * \brief A namespace containing configuration variables and functions used in
 * %QDiscord.
 */
namespace QDiscordUtilities
{
	///\brief A struct used for storing the Discord API endpoints.
	struct EndPoints
	{
		QString base;	  ///<\brief The base Discord endpoint.
		QString apiBase;  ///<\brief The base Discord API endpoint.
		QString gateway;  ///<\brief The gateway endpoint.
		QString users;	  ///<\brief The users endpoint.
		QString me;		  ///<\brief The users/\@me endpoint.
		QString guilds;   ///<\brief THe guilds endpoint.
		QString auth;	  ///<\brief The auth endpoint.
		QString register_;///<\brief The registration endpoint.
		QString login;	  ///<\brief The auth/login endpoint.
		QString logout;	  ///<\brief The auth/logout endpoint.
		QString servers;  ///<\brief The servers endpoint.
		QString channels; ///<\brief The channels endpoint.
	};
	extern const EndPoints endPoints;
	/*!
	 * \brief Converts network errors to a human-readable string based on
	 * Discord documentation.
	 *
	 * See https://discordapp.com/developers/docs/topics/response-codes
	 * \param error The network error returned by a failed method.
	 */
	QString networkErrorToString(QNetworkReply::NetworkError error);
	///\brief Returns the DateTime a Discord snowflake was generated.
	QDateTime snowflakeTime(QString snowflake);
	///\brief Converts the specified token to a token of type `tokenType`
	QString convertTokenToType(QString token, QDiscordTokenType tokenType);
	///\brief Generates a user-agent from the information in this namespace.
	QString userAgent();
	///\brief Discord's epoch value for snowflake generation.
	extern const qlonglong discordEpoch;
	/*!
	 * \brief The library name.
	 *
	 * This should always be QDiscord, unless you fork the project and change
	 * the name.\n
	 * Change it in `src/config`.
	 */
	extern const QString libName;
	/*!
	 * \brief The name of the bot this library will be used for.
	 *
	 * This should always be changed to your bot's name.\n
	 * Change it in `src/config`.
	 */
	extern const QString botName;
	///\brief The major version of the library.
	extern const QString libMajor;
	/*!
	 * \brief The minor version of the library.
	 *
	 * This should be incremented with each update of the library.
	 */
	extern const QString libMinor;
	///\brief A link to where the library repository is located.
	extern const QString libLink;
	///\brief The Discord API version in use.
	extern const QString apiVersion;
}

#endif // QDISCORDUTILITIES_HPP

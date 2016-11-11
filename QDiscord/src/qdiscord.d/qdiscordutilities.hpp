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

#ifndef QDISCORDUTILITIES_HPP
#define QDISCORDUTILITIES_HPP

#include <QString>
#include <QNetworkReply>
#include <stdlib.h>
#include "qdiscord_global.hpp"

///\brief A class containing configuration variables and static functions used in QDiscord.
class QDISCORD_API QDiscordUtilities
{
public:
	///\brief A struct used for storing the Discord API endpoints.
	struct EndPoints
	{
		QString base;	  ///<\brief The base Discord endpoint.
		QString apiBase;  ///<\brief The base Discord API endpoint.
		QString gateway;  ///<\brief The gateway endpoint.
		QString users;	  ///<\brief The users endpoint.
		QString me;		  ///<\brief The user/\@me endpoint.
		QString register_;///<\brief The registration endpoint.
		QString login;	  ///<\brief The auth/login endpoint.
		QString logout;	  ///<\brief The auth/logout endpoint.
		QString servers;  ///<\brief The servers endpoint.
		QString channels; ///<\brief The channels endpoint.
	};
	const static EndPoints endPoints;
	/*!
	 * \brief Converts network errors to a human-readable string based on Discord documentation.
	 *
	 * See https://discordapp.com/developers/docs/topics/response-codes
	 * \param error The network error returned by a failed method.
	 * \return A human-readable string to help explain the reason for failure.
	 */
	static QString networkErrorToString(QNetworkReply::NetworkError error);
	/*!
	 * \brief The library name.
	 *
	 * This should always be QDiscord, unless you fork the project and change the name.
	 */
	const static QString libName;
	/*!
	 * \brief The name of the bot this library will be used for.
	 *
	 * This should always be changed to your bot's name.
	 */
	static QString botName;
	///\brief The major version of the library.
	const static QString libMajor;
	/*!
	 * \brief The minor version of the library.
	 *
	 * This should be incremented with each update of the library.
	 */
	const static QString libMinor;
	///\brief A link to where the library repository is located.
	const static QString libLink;
	const static bool debugMode;
};

#endif // QDISCORDUTILITIES_HPP

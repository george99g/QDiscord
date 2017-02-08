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

#ifndef QDISCORDID_HPP
#define QDISCORDID_HPP

#include <QMetaType>
#include <QString>
#include <QDateTime>
#include "qdiscordutilities.hpp"

class QDiscordID
{
public:
	QDiscordID();
	QDiscordID(quint64 id);
	QDiscordID(const QString& id);
	QString toString() const;
	quint64 value() const;
	QDateTime createdAt() const;
	operator bool() const;
	bool operator !() const;
	bool operator ==(const QDiscordID& other) const;
	bool operator !=(const QDiscordID& other) const;
	bool operator > (const QDiscordID& other) const;
	bool operator < (const QDiscordID& other) const;
	bool operator <=(const QDiscordID& other) const;
	bool operator >=(const QDiscordID& other) const;
	bool operator ==(quint64 other) const;
	bool operator !=(quint64 other) const;
	bool operator > (quint64 other) const;
	bool operator < (quint64 other) const;
	bool operator <=(quint64 other) const;
	bool operator >=(quint64 other) const;
private:
	quint64 _id;
};

Q_DECLARE_METATYPE(QDiscordID)

#endif // QDISCORDID_HPP

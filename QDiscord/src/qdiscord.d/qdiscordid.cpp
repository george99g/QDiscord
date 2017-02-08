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

#include "qdiscordid.hpp"

QDiscordID::QDiscordID()
{
	_id = 0;
}

QDiscordID::QDiscordID(quint64 id)
{
	_id = id;
}

QDiscordID::QDiscordID(const QString& id)
{
	bool ok;
	_id = id.toULongLong(&ok);
	if(!ok)
		_id = 0;
}

QString QDiscordID::toString() const
{
	return QString::number(_id);
}

quint64 QDiscordID::value() const
{
	return _id;
}

QDateTime QDiscordID::createdAt() const
{
#if QT_VERSION_MAJOR >= 5 && QT_VERSION_MINOR >= 8
	return QDateTime::fromSecsSinceEpoch(
#else
	return QDateTime::fromTime_t(
#endif
		((_id >> 22) + QDiscordUtilities::discordEpoch) / 1000
				);
}

bool QDiscordID::operator !() const
{
	return _id == 0;
}

QDiscordID::operator bool() const
{
	return _id != 0;
}

bool QDiscordID::operator ==(const QDiscordID& other) const
{
	return _id == other._id;
}

bool QDiscordID::operator !=(const QDiscordID& other) const
{
	return _id != other._id;
}

bool QDiscordID::operator >(const QDiscordID& other) const
{
	return _id > other._id;
}

bool QDiscordID::operator <(const QDiscordID& other) const
{
	return _id < other._id;
}

bool QDiscordID::operator <=(const QDiscordID& other) const
{
	return _id <= other._id;
}

bool QDiscordID::operator >=(const QDiscordID& other) const
{
	return _id >= other._id;
}

bool QDiscordID::operator ==(quint64 other) const
{
	return _id == other;
}

bool QDiscordID::operator !=(quint64 other) const
{
	return _id != other;
}

bool QDiscordID::operator >(quint64 other) const
{
	return _id > other;
}

bool QDiscordID::operator <(quint64 other) const
{
	return _id < other;
}

bool QDiscordID::operator <=(quint64 other) const
{
	return _id <= other;
}

bool QDiscordID::operator >=(quint64 other) const
{
	return _id >= other;
}

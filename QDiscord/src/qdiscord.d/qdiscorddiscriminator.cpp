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

#include "qdiscorddiscriminator.hpp"

QDiscordDiscriminator::QDiscordDiscriminator()
{
	_discriminator = -1;
}

QDiscordDiscriminator::QDiscordDiscriminator(qint16 discriminator)
{
	_discriminator = discriminator;
}

QDiscordDiscriminator::QDiscordDiscriminator(const QString& discriminator)
{
	bool ok;
	_discriminator = discriminator.toShort(&ok);
	if(!ok)
		_discriminator = -1;
}

QString QDiscordDiscriminator::toString() const
{
	return QString::number(_discriminator);
}

qint16 QDiscordDiscriminator::value() const
{
	return _discriminator;
}

bool QDiscordDiscriminator::operator !() const
{
	return _discriminator == -1;
}

QDiscordDiscriminator::operator bool() const
{
	return _discriminator != -1;
}

bool
QDiscordDiscriminator::operator ==(const QDiscordDiscriminator& other) const
{
	return _discriminator == other._discriminator;
}

bool
QDiscordDiscriminator::operator !=(const QDiscordDiscriminator& other) const
{
	return _discriminator != other._discriminator;
}

bool
QDiscordDiscriminator::operator >(const QDiscordDiscriminator& other) const
{
	return _discriminator > other._discriminator;
}

bool
QDiscordDiscriminator::operator <(const QDiscordDiscriminator& other) const
{
	return _discriminator < other._discriminator;
}

bool
QDiscordDiscriminator::operator <=(const QDiscordDiscriminator& other) const
{
	return _discriminator <= other._discriminator;
}

bool
QDiscordDiscriminator::operator >=(const QDiscordDiscriminator& other) const
{
	return _discriminator >= other._discriminator;
}

bool QDiscordDiscriminator::operator ==(qint16 other) const
{
	return _discriminator == other;
}

bool QDiscordDiscriminator::operator !=(qint16 other) const
{
	return _discriminator != other;
}

bool QDiscordDiscriminator::operator >(qint16 other) const
{
	return _discriminator > other;
}

bool QDiscordDiscriminator::operator <(qint16 other) const
{
	return _discriminator < other;
}

bool QDiscordDiscriminator::operator <=(qint16 other) const
{
	return _discriminator <= other;
}

bool QDiscordDiscriminator::operator >=(qint16 other) const
{
	return _discriminator >= other;
}

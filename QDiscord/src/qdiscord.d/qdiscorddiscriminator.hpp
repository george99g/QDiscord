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

#ifndef QDISCORDDISCRIMINATOR_HPP
#define QDISCORDDISCRIMINATOR_HPP

#include <QMetaType>
#include <QString>

class QDiscordDiscriminator
{
public:
	QDiscordDiscriminator();
	QDiscordDiscriminator(qint16 discriminator);
	QDiscordDiscriminator(const QString& discriminator);
	QString toString() const;
	qint16 value() const;
	operator bool() const;
	bool operator !() const;
	bool operator ==(const QDiscordDiscriminator& other) const;
	bool operator !=(const QDiscordDiscriminator& other) const;
	bool operator > (const QDiscordDiscriminator& other) const;
	bool operator < (const QDiscordDiscriminator& other) const;
	bool operator <=(const QDiscordDiscriminator& other) const;
	bool operator >=(const QDiscordDiscriminator& other) const;
	bool operator ==(qint16 other) const;
	bool operator !=(qint16 other) const;
	bool operator > (qint16 other) const;
	bool operator < (qint16 other) const;
	bool operator <=(qint16 other) const;
	bool operator >=(qint16 other) const;
private:
	qint16 _discriminator;
};

Q_DECLARE_METATYPE(QDiscordDiscriminator)

#endif // QDISCORDDISCRIMINATOR_HPP

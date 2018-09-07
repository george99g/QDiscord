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

#include "qdiscord.d/models/qdiscordmodel.hpp"
#include <QDateTime>

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action,
                          QString& value,
                          const QString& name)
{
    value = action.data()[name].toString();
}

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action,
                          std::experimental::optional<QString>& value,
                          const QString& name)
{
    if(action.data().contains(name))
        value = action.data()[name].toString();
}

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action,
                          double& value,
                          const QString& name)
{
    value = action.data()[name].toDouble();
}

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action,
                          std::experimental::optional<double>& value,
                          const QString& name)
{
    if(action.data().contains(name))
        value = action.data()[name].toDouble();
}

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action,
                          bool& value,
                          const QString& name)
{
    value = action.data()[name].toBool();
}

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action,
                          std::experimental::optional<bool>& value,
                          const QString& name)
{
    if(action.data().contains(name))
        value = action.data()[name].toBool();
}

template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action,
                          const QString& value,
                          const QString& name)
{
    action.data().insert(name, value);
}

template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action,
                          const std::experimental::optional<QString>& value,
                          const QString& name)
{
    if(value.has_value())
        action.data().insert(name, value.value());
}

template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action,
                          const double& value,
                          const QString& name)
{
    action.data().insert(name, value);
}

template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action,
                          const std::experimental::optional<double>& value,
                          const QString& name)
{
    if(value.has_value())
        action.data().insert(name, value.value());
}

template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action,
                          const bool& value,
                          const QString& name)
{
    action.data().insert(name, value);
}

template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action,
                          const std::experimental::optional<bool>& value,
                          const QString& name)
{
    if(value.has_value())
        action.data().insert(name, value.value());
}

template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action,
                          const QDateTime& value,
                          const QString& name)
{
    action.data().insert(
        name, value.toTimeSpec(Qt::OffsetFromUTC).toString(Qt::ISODateWithMs));
}

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action,
                          QDateTime& value,
                          const QString& name)
{
    value = QDateTime::fromString(action.data()[name].toString(),
                                  Qt::ISODateWithMs);
}

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action,
                          std::experimental::optional<QDateTime>& value,
                          const QString& name)
{
    if(action.data().contains(name))
    {
        value = QDateTime::fromString(action.data()[name].toString(),
                                      Qt::ISODateWithMs);
    }
}

template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action,
                          const std::experimental::optional<QDateTime>& value,
                          const QString& name)
{
    if(value.has_value())
    {
        action.data().insert(name, value.value().toString(Qt::ISODateWithMs));
    }
}

template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action,
                          QStringList& value,
                          const QString& name)
{
    for(const QJsonValue& v : action.data()[name].toArray())
        value.append(v.toString());
}

template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action,
                          const QStringList& value,
                          const QString& name)
{
    QJsonArray array;

    for(const QString& string : value)
        array.append(string);

    action.data().insert(name, array);
}

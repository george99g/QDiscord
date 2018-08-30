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

#ifndef QDISCORDMODEL_HPP
#define QDISCORDMODEL_HPP

#include "qdiscord.d/external/optional/optional.hpp"
#include <QJsonArray>
#include <QJsonObject>
#include <QSharedPointer>
#include <string>

class QDateTime;

namespace QDiscordModel {
    template<class Action, typename T>
    void field(Action& action, T& value, const QString& name);

    class SerializeJsonAction
    {
    public:
        SerializeJsonAction(){};
        QJsonObject& data() { return _data; }

    private:
        QJsonObject _data;
    };

    class DeserializeJsonAction
    {
    public:
        DeserializeJsonAction(const QJsonObject& data)
            : _data(data){};
        const QJsonObject& data() const { return _data; }

    private:
        const QJsonObject& _data;
    };

}; // namespace QDiscordModel

template<class T>
class QDiscordModelBase
{
public:
    void deserializeJson(const QJsonObject& object)
    {
        QDiscordModel::DeserializeJsonAction deserializeAction(object);
        static_cast<T*>(this)->map(deserializeAction);
    }

    QJsonObject serializeJson() const
    {
        QDiscordModel::SerializeJsonAction serializeAction;
        static_cast<const T*>(this)->map(serializeAction);
        return serializeAction.data();
    }

private:
};

namespace QDiscordModel {
    template<class T>
    void field(QDiscordModel::DeserializeJsonAction& action,
               T& value,
               const QString& name)
    {
        T newVal;
        newVal.deserializeJson(action.data()[name].toObject());
        value = newVal;
    }

    template<>
    void field(QDiscordModel::DeserializeJsonAction& action,
               QString& value,
               const QString& name);

    template<>
    void field(QDiscordModel::DeserializeJsonAction& action,
               std::experimental::optional<QString>& value,
               const QString& name);

    template<>
    void field(QDiscordModel::DeserializeJsonAction& action,
               double& value,
               const QString& name);

    template<>
    void field(QDiscordModel::DeserializeJsonAction& action,
               std::experimental::optional<double>& value,
               const QString& name);

    template<>
    void field(QDiscordModel::DeserializeJsonAction& action,
               bool& value,
               const QString& name);

    template<>
    void field(QDiscordModel::DeserializeJsonAction& action,
               std::experimental::optional<bool>& value,
               const QString& name);

    template<>
    void field(QDiscordModel::DeserializeJsonAction& action,
               int& value,
               const QString& name);

    template<>
    void field(QDiscordModel::DeserializeJsonAction& action,
               std::experimental::optional<int>& value,
               const QString& name);

    template<>
    void field(QDiscordModel::DeserializeJsonAction& action,
               QDateTime& value,
               const QString& name);

    template<>
    void field(QDiscordModel::DeserializeJsonAction& action,
               std::experimental::optional<QDateTime>& value,
               const QString& name);

    template<typename T>
    void field(QDiscordModel::DeserializeJsonAction& action,
               QList<T>& value,
               const QString& name)
    {
        value.clear();
        for(const QJsonValue& i : action.data()[name].toArray())
        {
            T item;
            item.deserializeJson(i.toObject());
            value.append(item);
        }
    }

    template<typename T>
    void field(QDiscordModel::DeserializeJsonAction& action,
               QLinkedList<T>& value,
               const QString& name)
    {
        value.clear();
        for(const QJsonValue& i : action.data()[name].toArray())
        {
            T item;
            item.deserializeJson(i.toObject());
            value.append(item);
        }
    }

    template<typename T>
    void field(QDiscordModel::DeserializeJsonAction& action,
               QVector<T>& value,
               const QString& name)
    {
        value.clear();
        for(const QJsonValue& i : action.data()[name].toArray())
        {
            T item;
            item.deserializeJson(i.toObject());
            value.append(item);
        }
    }

    template<typename T>
    void field(QDiscordModel::DeserializeJsonAction& action,
               QList<QSharedPointer<T>>& value,
               const QString& name)
    {
        value.clear();
        for(const QJsonValue& i : action.data()[name].toArray())
        {
            QSharedPointer<T> item = QSharedPointer<T>(new T());
            item->deserializeJson(i.toObject());
            value.append(item);
        }
    }

    template<typename T>
    void field(QDiscordModel::DeserializeJsonAction& action,
               QLinkedList<QSharedPointer<T>>& value,
               const QString& name)
    {
        value.clear();
        for(const QJsonValue& i : action.data()[name].toArray())
        {
            QSharedPointer<T> item = QSharedPointer<T>(new T());
            item->deserializeJson(i.toObject());
            value.append(item);
        }
    }

    template<typename T>
    void field(QDiscordModel::DeserializeJsonAction& action,
               QVector<QSharedPointer<T>>& value,
               const QString& name)
    {
        value.clear();
        for(const QJsonValue& i : action.data()[name].toArray())
        {
            QSharedPointer<T> item = QSharedPointer<T>(new T());
            item->deserializeJson(i.toObject());
            value.append(item);
        }
    }

    // ---

    template<class T>
    void field(QDiscordModel::SerializeJsonAction& action,
               T& value,
               const QString& name)
    {
        action.data()[name] = value.serializeJson();
    }

    template<>
    void field(QDiscordModel::SerializeJsonAction& action,
               const QString& value,
               const QString& name);

    template<>
    void field(QDiscordModel::SerializeJsonAction& action,
               const std::experimental::optional<QString>& value,
               const QString& name);

    template<>
    void field(QDiscordModel::SerializeJsonAction& action,
               const double& value,
               const QString& name);

    template<>
    void field(QDiscordModel::SerializeJsonAction& action,
               const std::experimental::optional<double>& value,
               const QString& name);

    template<>
    void field(QDiscordModel::SerializeJsonAction& action,
               const bool& value,
               const QString& name);

    template<>
    void field(QDiscordModel::SerializeJsonAction& action,
               const std::experimental::optional<bool>& value,
               const QString& name);

    template<>
    void field(QDiscordModel::SerializeJsonAction& action,
               const int& value,
               const QString& name);

    template<>
    void field(QDiscordModel::SerializeJsonAction& action,
               const std::experimental::optional<int>& value,
               const QString& name);

    template<>
    void field(QDiscordModel::SerializeJsonAction& action,
               const QDateTime& value,
               const QString& name);

    template<>
    void field(QDiscordModel::SerializeJsonAction& action,
               const std::experimental::optional<QDateTime>& value,
               const QString& name);

    template<typename T>
    void field(QDiscordModel::SerializeJsonAction& action,
               const QList<T>& value,
               const QString& name)
    {
        QJsonArray output;

        for(const T& i : value)
            output.append(i.serializeJson());

        action.data().insert(name, output);
    }

    template<typename T>
    void field(QDiscordModel::SerializeJsonAction& action,
               const QLinkedList<T>& value,
               const QString& name)
    {
        QJsonArray output;

        for(const T& i : value)
            output.append(i.serializeJson());

        action.data().insert(name, output);
    }

    template<typename T>
    void field(QDiscordModel::SerializeJsonAction& action,
               const QVector<T>& value,
               const QString& name)
    {
        QJsonArray output;

        for(const T& i : value)
            output.append(i.serializeJson());

        action.data().insert(name, output);
    }

    template<typename T>
    void field(QDiscordModel::SerializeJsonAction& action,
               const QList<QSharedPointer<T>>& value,
               const QString& name)
    {
        QJsonArray output;

        for(const QSharedPointer<T>& i : value)
            output.append(i->serializeJson());

        action.data().insert(name, output);
    }

    template<typename T>
    void field(QDiscordModel::SerializeJsonAction& action,
               const QLinkedList<QSharedPointer<T>>& value,
               const QString& name)
    {
        QJsonArray output;

        for(const QSharedPointer<T>& i : value)
            output.append(i->serializeJson());

        action.data().insert(name, output);
    }

    template<typename T>
    void field(QDiscordModel::SerializeJsonAction& action,
               const QVector<QSharedPointer<T>>& value,
               const QString& name)
    {
        QJsonArray output;

        for(const QSharedPointer<T>& i : value)
            output.append(i->serializeJson());

        action.data().insert(name, output);
    }
} // namespace QDiscordModel

#endif // QDISCORDMODEL_HPP

#include "qdiscordrole.hpp"
#include "qdiscordguild.hpp"
#include "qdiscordrest.hpp"

QSharedPointer<QDiscordRole> QDiscordRole::fromJson(const QJsonObject& object)
{
    QSharedPointer<QDiscordRole> role(new QDiscordRole());
    role->deserialize(object);
    return role;
}

QDiscordRole::QDiscordRole(const QJsonObject& object)
{
    deserialize(object);

#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordRole(" << this << ") constructed";
#endif
}

QDiscordRole::QDiscordRole()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordRole(" << this << ") constructed";
#endif
}

QDiscordRole::~QDiscordRole()
{
#ifdef QDISCORD_LIBRARY_DEBUG
    qDebug() << "QDiscordRole(" << this << ") destroyed";
#endif
}

void QDiscordRole::deserialize(const QJsonObject& object)
{
    _id = QDiscordID(object["id"].toString());
    _name = object["name"].toString();
    _color = object["color"].toVariant().toUInt();
    _hoist = object["hoist"].toBool();
    _position = object["position"].toInt(-1);
    _permissions =
        QDiscordPermission(object["permissions"].toVariant().toULongLong());
    _managed = object["managed"].toBool();
    _mentionable = object["mentionable"].toBool();
}

QJsonObject QDiscordRole::serialize() const
{
    QJsonObject object;

    object["id"] = _id.toString();
    object["name"] = _name;
    object["color"] = static_cast<qint32>(_color);
    object["hoist"] = _hoist;
    object["position"] = _position;
    object["permissions"] = QString::number(_permissions.value());
    object["managed"] = _managed;
    object["mentionable"] = _mentionable;

    return object;
}

bool QDiscordRole::isEveryone() const
{
    QSharedPointer<QDiscordGuild> guild = _guild.lock();
    if(!guild)
        return false;
    if(guild->id() == _id)
        return true;
    return false;
}

QString QDiscordRole::mention() const
{
    return "<@&" + _id.toString() + ">";
}

bool QDiscordRole::operator==(const QDiscordRole& other) const
{
    return _id == other._id;
}

bool QDiscordRole::operator!=(const QDiscordRole& other) const
{
    return !operator==(other);
}

bool QDiscordRole::operator>(const QDiscordRole& other) const
{
    return _position > other._position;
}

bool QDiscordRole::operator<(const QDiscordRole& other) const
{
    return _position < other._position;
}

bool QDiscordRole::operator>=(const QDiscordRole& other) const
{
    return _position >= other._position;
}

bool QDiscordRole::operator<=(const QDiscordRole& other) const
{
    return _position <= other._position;
}

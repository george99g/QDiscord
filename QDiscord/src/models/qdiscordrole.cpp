#include "qdiscord.d/models/qdiscordrole.hpp"
#include "qdiscord.d/qdiscordguild.hpp"
#include "qdiscord.d/qdiscordrest.hpp"

QSharedPointer<QDiscordRole> QDiscordRole::fromJson(const QJsonObject& object)
{
    QSharedPointer<QDiscordRole> role(new QDiscordRole());
    role->deserialize(object);
    return role;
}

QDiscordRole::QDiscordRole(const QJsonObject& object)
{
    deserialize(object);

#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << "QDiscordRole(" << this << ") constructed";
#endif
}

QDiscordRole::QDiscordRole()
{
#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << "QDiscordRole(" << this << ") constructed";
#endif
}

QDiscordRole::~QDiscordRole()
{
#ifdef QDISCORD_PRINT_DEBUG
    qDebug() << "QDiscordRole(" << this << ") destroyed";
#endif
}

void QDiscordRole::deserialize(const QJsonObject& object)
{
    deserializeJson(object);
}

QJsonObject QDiscordRole::serialize() const
{
    return serializeJson();
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

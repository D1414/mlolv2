#include "champion.h"

Champion::Champion(QObject *parent)
    : QObject(parent), m_id(0), m_level(0), m_points(0)
{}

Champion::Champion(int id,
        QString name,
        QString icon,
        int level,
        int points,
        QObject *parent)
    : QObject(parent),
        m_id(id),
        m_name(name),
        m_icon(icon),
        m_level(level),
        m_points(points){}

int Champion::id() const {
    return m_id;
}

QString Champion::name() const {
    return m_name;
}

QString Champion::icon() const {
    return m_icon;
}

int Champion::level() const {
    return m_level;
}

int Champion::points() const {
    return m_points;
}

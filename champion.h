#ifndef CHAMPION_H
#define CHAMPION_H

#include <QObject>
#include <QtQml/qqml.h>

class Champion : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString icon READ icon CONSTANT)
    Q_PROPERTY(int level READ level CONSTANT)
    Q_PROPERTY(int points READ points CONSTANT)

public:
    explicit Champion(QObject *parent = nullptr);
    Champion(int id,
             QString name,
             QString icon,
             int level,
             int points,
             QObject *parent = nullptr);

    int id() const;
    QString name() const;
    QString icon() const;
    int level() const;
    int points() const;
private:
    int m_id;
    QString m_name;
    QString m_icon;
    int m_level;
    int m_points;
};

#endif // CHAMPION_H

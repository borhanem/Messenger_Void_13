#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "user.h"
class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);
    Message();
    Message(QString txt,QString time,QString sender);
private:
    QString m_text;
    QString m_time;
    QString m_sender;
signals:

};

#endif // MESSAGE_H

#ifndef SERIALMGR_H
#define SERIALMGR_H

#include <QObject>

class SerialMgr : public QObject
{
    Q_OBJECT
public:
    explicit SerialMgr(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SERIALMGR_H
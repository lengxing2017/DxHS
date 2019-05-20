#ifndef LISMGR_H
#define LISMGR_H

#include <QObject>

class LisMgr : public QObject
{
    Q_OBJECT
public:
    explicit LisMgr(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LISMGR_H
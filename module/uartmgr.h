#ifndef UARTMGR_H
#define UARTMGR_H

#include <QObject>

class UartMgr : public QObject
{
    Q_OBJECT
public:
    explicit UartMgr(QObject *parent = nullptr);

signals:

public slots:
};

#endif // UARTMGR_H
#ifndef PRINTMGR_H
#define PRINTMGR_H
#include <QQmlEngine>
#include <qdebug.h>
#include <QObject>
#include <QPrinter>
class PrinterMgr : public QObject
{
    Q_OBJECT
public:
    explicit PrinterMgr(QObject *parent = nullptr);

    Q_INVOKABLE void printDocument(QPrinter *printer);

signals:

public slots:
};

static PrinterMgr * printermgrinstance;

static QObject *printermgr_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    if(printermgrinstance == nullptr)
    {
        qDebug()<<"inner printermgrinstance is nullptr";
    }
    else
    {
        qDebug()<<"inner printermgrinstance is not nullptr";
    }
    return printermgrinstance;
}

#endif // PRINTMGR_H

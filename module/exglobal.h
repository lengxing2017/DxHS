#ifndef EXGLOBAL_H
#define EXGLOBAL_H

#include <QObject>
#include <QQmlEngine>

class ExGlobal : public QObject
{
    Q_OBJECT
public:
    explicit ExGlobal(QObject *parent = nullptr);
    Q_INVOKABLE void exInit();
    static QString panelCode;
signals:

public slots:
private:
    QString tCode;
};

static QObject *exglobal_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    ExGlobal *exGlobal = new ExGlobal();
    return exGlobal;
}
#endif // EXGLOBAL_H

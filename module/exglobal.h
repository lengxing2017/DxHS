#ifndef EXGLOBAL_H
#define EXGLOBAL_H

#include <QObject>
#include <QQmlEngine>

class ExGlobal : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString user READ user WRITE setUser)
    Q_PROPERTY(QString panelName READ panelName)
    Q_PROPERTY(QString panelCode READ panelCodeEx)
    //Q_PROPERTY(QString panelCodeEx READ panelCodeEx)
    Q_PROPERTY(QString sampleCode READ sampleCode)
    Q_PROPERTY(QString sampleInfo READ sampleInfo)
public:
    explicit ExGlobal(QObject *parent = nullptr);
    Q_INVOKABLE void exInit();

    static QString user() {return t_user;}
    static void setUser(const QString &user){t_user = user;}
    static QString panelName(){return t_panelName;}
    static void setPanelName(const QString &panelName){t_panelName = panelName;}
    static QString panelCode(){return t_panelCode;}
    static QString panelCodeEx(){return "Lot# "+t_panelCode;}
    static void setPanelCode(const QString &panelCode){t_panelCode = panelCode;}
    static QString sampleCode(){return t_sampleCode;}
    static void setSampleCode(const QString &sampleCode){t_sampleCode = sampleCode;}
    static QString sampleInfo(){return t_sampleInfo;}
    static void setSampleInfo(const QString &sampleInfo){t_sampleInfo = sampleInfo;}

signals:

public slots:

private:
    static QString t_panelCode;
    static QString t_panelName;
    static QString t_sampleCode;
    static QString t_sampleInfo;
    static QString t_user;
};

static QObject *exglobal_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    ExGlobal *exGlobal = new ExGlobal();
    return exGlobal;
}
#endif // EXGLOBAL_H

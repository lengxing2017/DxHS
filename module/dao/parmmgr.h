#ifndef PARMMGR_H
#define PARMMGR_H
#include <QQmlEngine>
#include <qlist.h>
#include "../sqlitemgr.h"
#include "../entity/Param.h"

class ParmMgr: public QObject
{
    Q_OBJECT
public:

    Q_INVOKABLE void init();

    Q_INVOKABLE QString get(QString key);

    Q_INVOKABLE bool update(QString key, QString value);
};

static ParmMgr * parmmgrinstance = nullptr;

static QObject * parmmgr_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return parmmgrinstance ;
}

#endif // PARMMGR_H

#ifndef LOGMGR_H
#define LOGMGR_H
#include <qlist.h>
#include "../sqlitemgr.h"
#include "../entity/Log.h"
class LogMgr : public QObject
{
    Q_OBJECT
public:

    Q_INVOKABLE QList<Log> getAll();

    Q_INVOKABLE bool insert(Log* log);

    Q_INVOKABLE bool clear();
};

static LogMgr * logmgrinstance = nullptr;

static QObject * logmgr_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return logmgrinstance   ;
}

#endif // LOGMGR_H

#ifndef ASSAYMGR_H
#define ASSAYMGR_H
#include "../sqlitemgr.h"
#include <qlist.h>
#include "../entity/Assay.h"
class AssayMgr : public QObject
{
    Q_OBJECT
public:
   Q_INVOKABLE QList<Assay> Get(int panelid);

signals:

public slots:
};

static AssayMgr * assaymgrinstance = nullptr;

static QObject * assaymgr_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return assaymgrinstance   ;
}

#endif // ASSAYMGR_H

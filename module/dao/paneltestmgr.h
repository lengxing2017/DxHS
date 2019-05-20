#ifndef PANELTESTMGR_H
#define PANELTESTMGR_H
#include <qlist.h>
#include "../sqlitemgr.h"
#include "../entity/PanelTest.h"

class PanelTestMgr: public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE bool insert(PanelTest* panelTest);

    Q_INVOKABLE QList<PanelTest> getAll();

    Q_INVOKABLE bool update(PanelTest* panelTest);
};

static PanelTestMgr * paneltestmgrinstance = nullptr;

static QObject * paneltestmgr_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return paneltestmgrinstance  ;
}

#endif // PANELTESTMGR_H

#ifndef PANELMGR_H
#define PANELMGR_H

#include <qlist.h>
#include "../sqlitemgr.h"
#include "../entity/Panel.h"
class PanelMgr : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE Panel* get(QString panelCode);
signals:

public slots:
};

static PanelMgr * panelmgrinstance = nullptr;

static QObject * panelmgr_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return panelmgrinstance   ;
}

#endif // PANELMGR_H

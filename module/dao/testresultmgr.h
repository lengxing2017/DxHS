#ifndef TESTRESULTMGR_H
#define TESTRESULTMGR_H
#include <qlist.h>
#include "../sqlitemgr.h"
#include "../entity/TestResult.h"

class TestResultMgr : public QObject
{
    Q_OBJECT

public:

    Q_INVOKABLE bool insert(TestResult* testResult);

    Q_INVOKABLE QList<TestResult> getAll(int testid);

    Q_INVOKABLE bool clear();
};

static TestResultMgr * testresultmgrinstance = nullptr;

static QObject * testresultmgr_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return testresultmgrinstance ;
}

#endif // TESTRESULTMGR_H

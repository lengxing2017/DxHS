#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include "module/sqlitemgr.h"
#include "module/exglobal.h"
#include "module/sequence.h"
#include "module/dao/AssayMgr.h"
#include "module/dao/panelmgr.h"
#include "module/dao/paneltestmgr.h"
#include "module/dao/parmmgr.h"
#include "module/dao/testresultmgr.h"
#include "module/dao/usermgr.h"
#include "module/dao/logmgr.h"
#include "module/printermgr.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    sqlitemgrinstance = new SqliteMgr();
    sqlitemgrinstance->conn(QCoreApplication::applicationDirPath() + "/data.db","sa","123456");
    //init dao manager
    //sqlitemgrinstance->init();
    assaymgrinstance= new AssayMgr();
    logmgrinstance = new LogMgr();
    panelmgrinstance = new PanelMgr();
    paneltestmgrinstance = new PanelTestMgr();
    parmmgrinstance = new ParmMgr();
    testresultmgrinstance = new TestResultMgr();
    usermgrinstance = new UserMgr();
    printermgrinstance = new PrinterMgr();


    if(sqlitemgrinstance == nullptr)
    {
        qDebug()<<"main sqlitemgrinstance is nullptr";
    }
    else
    {
        qDebug()<<"main sqlitemgrinstance is not nullptr";
    }


    qmlRegisterSingletonType<SqliteMgr>("Dx.SqliteMgr",1,0,"SqliteMgr",sqlitemgr_provider);

    qmlRegisterSingletonType<AssayMgr>("Dx.AssayMgr",1,0,"AssayMgr",assaymgr_provider);
    qmlRegisterSingletonType<PanelMgr>("Dx.PanelMgr",1,0,"PanelMgr",panelmgr_provider);
    qmlRegisterSingletonType<PanelTestMgr>("Dx.PanelTestMgr",1,0,"PanelTestMgr",paneltestmgr_provider);
    qmlRegisterSingletonType<ParmMgr>("Dx.ParmMgr",1,0,"ParmMgr",parmmgr_provider);
    qmlRegisterSingletonType<TestResultMgr>("Dx.TestResultMgr",1,0,"TestResultMgr",testresultmgr_provider);
    qmlRegisterSingletonType<UserMgr>("Dx.UserMgr",1,0,"UserMgr",usermgr_provider);
    qmlRegisterSingletonType<LogMgr>("Dx.LogMgr",1,0,"LogMgr",logmgr_provider);
    qmlRegisterSingletonType<PrinterMgr>("Dx.PrinterMgr",1,0,"PrinterMgr",printermgr_provider);

    qmlRegisterSingletonType<ExGlobal>("Dx.Global",1,0,"ExGlobal",exglobal_provider);
    qmlRegisterSingletonType<Sequence>("Dx.Sequence",1,0,"Sequence",sequence_provider);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

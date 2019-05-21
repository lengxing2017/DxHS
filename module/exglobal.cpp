#include "exglobal.h"
#include "dao/AssayMgr.h"
#include "dao/logmgr.h"
#include "dao/panelmgr.h"
#include "dao/paneltestmgr.h"
#include "dao/parmmgr.h"
#include "dao/testresultmgr.h"
#include "dao/usermgr.h"

#include <QDebug>
#include "sqlitemgr.h"
#include <QCoreApplication>

QString ExGlobal::t_panelCode = "Lot# 0180435";
QString ExGlobal::t_panelName = "PanelNameInit";
QString ExGlobal::t_sampleCode = "";
QString ExGlobal::t_sampleInfo = "";
QString ExGlobal::t_user = "";


ExGlobal::ExGlobal(QObject *parent) : QObject(parent)
{
    qDebug()<<"ExGlobal";
}

void ExGlobal::exInit()
{

    qDebug()<<"ExInit";
    t_panelCode = "lxText";

    if(sqlitemgrinstance == nullptr)
    {
        qDebug()<<"global sqlitemgrinstance is nullptr";
    }
    else
    {
        qDebug()<<"global sqlitemgrinstance is not nullptr";
    }

}

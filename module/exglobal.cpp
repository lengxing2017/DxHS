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
QString ExGlobal::panelCode = "";

ExGlobal::ExGlobal(QObject *parent) : QObject(parent)
{
    qDebug()<<"ExGlobal";
}

void ExGlobal::exInit()
{

    qDebug()<<"ExInit";
    panelCode = "lxText";

    if(sqlitemgrinstance == nullptr)
    {
        qDebug()<<"global sqlitemgrinstance is nullptr";
    }
    else
    {
        qDebug()<<"global sqlitemgrinstance is not nullptr";
    }

}

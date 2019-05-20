#include "parmmgr.h"
#include <QtDebug>

void ParmMgr::init(){
    sqlitemgrinstance->clear("Parm");
    sqlitemgrinstance->execute("INSERT INTO Parm (ParmKey, ParmValue) VALUES ('SysName', 'HS')");
    sqlitemgrinstance->execute("INSERT INTO Parm (ParmKey, ParmValue) VALUES ('Language', 'CHN')");
    sqlitemgrinstance->execute("INSERT INTO Parm (ParmKey, ParmValue) VALUES ('ResetCount', '0')");
    sqlitemgrinstance->execute("INSERT INTO Parm (ParmKey, ParmValue) VALUES ('LisAddress', '127.0.0.1')");
    sqlitemgrinstance->execute("INSERT INTO Parm (ParmKey, ParmValue) VALUES ('SoftwareVersion', '1.0.0.0')");
    sqlitemgrinstance->execute("INSERT INTO Parm (ParmKey, ParmValue) VALUES ('DrvVersion', '1.0.0.0')");
    sqlitemgrinstance->execute("INSERT INTO Parm (ParmKey, ParmValue) VALUES ('TmpVersion', '1.0.0.0')");
}

QString ParmMgr::get(QString key)
{
    QString sql = "SELECT * FROM Parm WHERE ParmKey = '"+key+"'";
    QSqlQuery query = sqlitemgrinstance->select(sql);

    QString result = "";
    while(query.next())
    {
        result = query.value(2).toString();
        break;
    }
    return result;
}

bool ParmMgr::update(QString key, QString value){
    QString sql = "UPDATE Parm SET ParmValue = '"+ value+"' WHERE ParmValue = '"+ key +"'";
    return sqlitemgrinstance->execute(sql);
}

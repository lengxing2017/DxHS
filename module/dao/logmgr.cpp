#include "logmgr.h"

QList<Log> LogMgr::getAll()
{
    QString sql = "SELECT * FROM Log";
    QSqlQuery query = sqlitemgrinstance->select(sql);
    QList<Log> ql;

    while(query.next())
    {
        Log log;
        log.Logid = query.value(0).toInt();
        log.LogTime = query.value(1).toDateTime();
        log.UserName= query.value(2).toString();
        log.LogType= query.value(3).toInt();
        log.Parm= query.value(4).toString();
        ql << log;
    }
    return ql;


}
bool LogMgr::insert(Log* log)
{
    QString sql = "INSERT INTO Log (LogTime, UserName, LogType, Parm) VALUES ('"+log->LogTime.toString() +"','"+log->UserName+"',"+QString::number(log->LogType)+",'"+log->Parm+"')";
    return sqlitemgrinstance->execute(sql);
}

bool LogMgr::clear()
{
    QString sqlDelete = "DELETE FROM Log";
    QString sqlUpdate ="UPDATE sqlite_sequence SET seq = 0 WHERE name ='Log'";
    return sqlitemgrinstance->execute(sqlDelete) && sqlitemgrinstance->execute(sqlUpdate);
}

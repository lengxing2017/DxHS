#include "testresultmgr.h"

bool TestResultMgr::insert(TestResult* testResult)
{
    QString sql = "INSERT INTO TestResult (Testid, Itemid, ResultIndex, ResultValue)";
    sql += "VALUES ("+QString::number(testResult->Testid) +","+QString::number(testResult->Itemid)+","+QString::number(testResult->ResultIndex)+","+QString::number(testResult->ResultValue)+")";
    return sqlitemgrinstance->execute(sql);
}

QList<TestResult> TestResultMgr::getAll(int testid)
{
    QString sql = "SELECT * FROM Parm WHERE Testid = "+QString::number(testid);
    QSqlQuery query = sqlitemgrinstance->select(sql);
    QList<TestResult> ql;
    QString result = "";
    while(query.next())
    {
        TestResult tr;
        tr.Resultid=query.value(0).toInt();
        tr.Testid=query.value(1).toInt();
        tr.Itemid=query.value(2).toInt();
        tr.ResultIndex=query.value(3).toInt();
        tr.ResultValue=query.value(4).toInt();
        ql<<tr;
    }
    return ql;
}

bool TestResultMgr::clear()
{
    QString sqlDelete ="DELETE FROM TestResult";
    QString sqlUpdate ="UPDATE sqlite_sequence SET seq = 0 WHERE name ='TestResult'";
    return sqlitemgrinstance->execute(sqlDelete) && sqlitemgrinstance->execute(sqlUpdate);
}

#include "paneltestmgr.h"

bool PanelTestMgr::insert(PanelTest* panelTest)
{
    QString sql = "INSERT INTO PanelTest (PanelCode, SerialNo, ExpirationDate, SampleCode, SampleInfo, TestTime, UserName, ResultType)";
    sql += "VALUES ('"+panelTest->PanelCode +"','"+panelTest->SerialNo+"','"+panelTest->ExpirationDate.toString()+"','"+panelTest->SampleCode+"','"+panelTest->SampleInfo+"','"+panelTest->TestTime.toString()+"','"+panelTest->UserName+"','"+ QString::number(panelTest->ResultType)+"')";
    return sqlitemgrinstance->execute(sql);
}

QList<PanelTest> PanelTestMgr::getAll()
{
    QString sql = "SELECT * FROM PanelTest";
    QSqlQuery query = sqlitemgrinstance->select(sql);
    QList<PanelTest> ql;

    while(query.next())
    {
        PanelTest pt;
        pt.Testid = query.value(0).toInt();
        pt.PanelCode= query.value(1).toString();
        pt.SerialNo= query.value(2).toString();
        pt.ExpirationDate = query.value(3).toDateTime();
        pt.SampleCode= query.value(4).toString();
        pt.SampleInfo= query.value(5).toString();
        pt.TestTime= query.value(6).toDateTime();
        pt.UserName= query.value(7).toString();
        pt.ResultType= query.value(8).toInt();
        ql << pt;
    }
    return ql;
}

bool PanelTestMgr::update(PanelTest* panelTest)
{
    QString sql = "UPDATE PanelTest SET PanelCode = '"+ panelTest->PanelCode+"', SerialNo = '"+panelTest->SerialNo+"', ExpirationDate = '"+panelTest->ExpirationDate.toString()+"', SampleCode = '"+panelTest->SampleCode+"', SampleInfo = '"+panelTest->SampleInfo+"', TestTime = '"+panelTest->TestTime.toString()+"', UserName = '"+panelTest->UserName+"', ResultType = "+QString::number(panelTest->ResultType)+")";
    return sqlitemgrinstance->execute(sql);
}

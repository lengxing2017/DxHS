#include "AssayMgr.h"

QList<Assay> AssayMgr::Get(int panelid)
{
    QString sql = "SELECT * FROM Assay WHERE panelid = "+QString::number(panelid);
    QSqlQuery query = sqlitemgrinstance->select(sql);
    QList<Assay> ql;

    while(query.next())
    {
        Assay assay;
        assay.Assayid = query.value(0).toInt();
        assay.Panelid = query.value(1).toInt();
        assay.AssayName= query.value(2).toString();
        ql << assay;
    }
    return ql;
}

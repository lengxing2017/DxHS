#include "panelmgr.h"

Panel* PanelMgr::get(QString panelCode)
{
    QString sql = "SELECT * FROM Panel WHERE PanelCode = '"+ panelCode +"'";
    QSqlQuery query = sqlitemgrinstance->select(sql);
    Panel *panel = nullptr;

    while(query.next())
    {
        panel->Panelid = query.value(0).toInt();
        panel->PanelName = query.value(1).toString();
        panel->PanelCode= query.value(2).toString();
        break;
    }
    return panel;
}

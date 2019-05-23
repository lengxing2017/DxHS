#include "sequence.h"
#include <QDebug>

#include "exglobal.h"

Sequence::Sequence(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(SequenceTimeout()));
}

void Sequence::sequenceDo(SequenceId id)
{        
    this->currSequenceId = id;
    if (id == SequenceId::Sequence_Test)
    {
        if (!ReadTestProcess(QCoreApplication::applicationDirPath()+"/P0180415cn"))
            emit sequenceFinish(SequenceResult::Result_Test_DataErr);
        else
            FindAction(false);

        return;
    }
    timer->start(1000);
}

void Sequence::sequenceCancel()
{
    timer->stop();
    currSequenceId = SequenceId::Sequence_Idle;
}

void Sequence::SequenceTimeout()
{
    qDebug()<<"SequenceTimeout,SequenceId:"<<this->currSequenceId;
    if (this->currSequenceId == Sequence::SequenceId::Sequence_SelfCheck)
        emit sequenceFinish(SequenceResult::Result_SelfCheck_ok);
    else if(this->currSequenceId==Sequence::SequenceId::Sequence_OpenBox){        
        ExGlobal::setSampleCode("SLX 01079");
        ExGlobal::setSampleInfo("华山11");
        emit sequenceFinish(SequenceResult::Result_OpenBox_ok);
    }
    else if(this->currSequenceId==Sequence::SequenceId::Sequence_Test){        
        FindAction(true);
    }
}

bool Sequence::ReadTestProcess(QString panel)
{
    QFile xmlfile(panel+".xml");
    qDebug("ReadTestProcess");
    if (!xmlfile.open(QFile::ReadOnly))
    {
        qDebug()<<"file err:"<<xmlfile.error()<<",string:"<<xmlfile.errorString()<<",file:"<<xmlfile.fileName()<<",dir:"<<QDir::currentPath()<<",apppath:"<<QCoreApplication::applicationDirPath();
        return false;
    }

    if (!doc.setContent(&xmlfile))
    {
        xmlfile.close();
        return  false;
    }
    xmlfile.close();

    if (!FormatAction())
        return false;

    WriteTestProcess(panel+"U");
    return true;
}

bool Sequence::WriteTestProcess(QString panel)
{
    QFile xmlfile(panel+".xml");

    if (!xmlfile.open(QFile::WriteOnly|QFile::Truncate))
        return false;
    QTextStream out(&xmlfile);
    doc.save(out,4);
    xmlfile.close();
    return true;
}

bool Sequence::DoAction(QDomElement action)
{    
    int nDuration = action.attribute("Duration").toInt();

    timer->start(1000*nDuration);
    return true;
}

QString Sequence::sequenceMessage(){
    return message;
}
bool Sequence::FindAction(bool bFinishAction)
{
    QDomElement root = doc.documentElement();
    int totalStep = root.attribute("steps").toInt();
    int currStep = root.attribute("currstep").toInt();
    int nTotalTime = root.attribute("Duration").toInt();
    QDomNode node = root.firstChild();

    while (!node.isNull()) {
        QDomElement e = node.toElement();
        if (!e.isNull() && e.hasAttribute("No") && e.attribute("No").toInt() == currStep){

            if (e.tagName() == "Action"){
                if (!bFinishAction)
                    return DoAction(e);
                else if(currStep == totalStep)
                {
                    emit processFinish(nTotalTime,nTotalTime);
                    return true;
                }
                else
                {
                    currStep++;
                    root.setAttribute("currstep",currStep);
                    return FindAction(false);
                }
            }else if(e.tagName() == "Actions"){
                int nCycle = e.attribute("cycle").toInt();
                int nCurrCycle = e.attribute("currcycle").toInt();
                int nChildCurrStep = e.attribute("currstep").toInt();
                int nChildTotalStep = e.attribute("steps").toInt();
                QDomNodeList list = e.childNodes();
                for (int i = 0; i<list.count();i++)
                {
                    QDomNode n = list.at(i);
                    if (n.isElement()){
                        QDomElement ne = n.toElement();
                        if (ne.tagName() == "Action"){
                            if (!bFinishAction)
                                return DoAction(ne);
                            else if(nChildCurrStep == nChildTotalStep){
                                if (nCurrCycle == nCycle){
                                    if (currStep == totalStep){
                                        emit processFinish(nTotalTime,nTotalTime);
                                        return true;
                                    }
                                    else{
                                        currStep++;
                                        root.setAttribute("currstep",currStep);
                                    }
                                }
                                else {
                                    nChildCurrStep = 1;
                                    nCurrCycle++;
                                    e.setAttribute("currstep",nChildCurrStep);
                                    e.setAttribute("currcycle",nCurrCycle);
                                }
                            }
                            else
                            {
                                nChildCurrStep++;
                                e.setAttribute("currstep",nChildCurrStep);
                            }
                            return FindAction(false);
                        }
                    }
                }
            }
        }
    }

    return true;
}

int Sequence::CalSteps(QDomElement element)
{
    int nStep = 0;
    QDomNode node = element.firstChild();
    while(!node.isNull())
    {
        QDomElement e = node.toElement();
        if (!e.isNull() && (e.tagName()=="Action"||e.tagName()=="Actions"))
            nStep++;
        node = node.nextSibling();
    }
    return nStep;
}

bool Sequence::FormatAction(){
    bool result = false;
    QDomElement root = doc.documentElement();
    root.setAttribute("currstep",1);
    int totalStep = CalSteps(root);
    int nFinishTime = 0;
    root.setAttribute("steps",totalStep);

    ExGlobal::setPanelName(root.attribute("PanelName"));
    ExGlobal::setPanelCode(root.attribute("PanelCode"));

    for (int i = 1; i <= totalStep; i++){
        QDomNode node = root.firstChild();
        while (!node.isNull()) {
            QDomElement e = node.toElement();
            if (!e.isNull()&& e.hasAttribute("No") && e.attribute("No").toInt() == i){
                e.setAttribute("pretime",nFinishTime);
                if (e.tagName()=="Action")
                {
                    nFinishTime += e.attribute("Duration").toInt();
                }
                else if(e.tagName()=="Actions"){
                    int childTotalStep = CalSteps(e);
                    e.setAttribute("steps",childTotalStep);
                    int cycle = e.attribute("cycle").toInt();
                    int nChildFinshTime = 0;
                    for (int j = 1; j <= childTotalStep; j++)
                    {
                        QDomNode cnode = e.firstChild();
                        bool cresult = false;
                        e.setAttribute("currcycle",1);
                        e.setAttribute("currstep",1);
                        while(!cnode.isNull())
                        {
                            QDomElement ce = cnode.toElement();
                            if (!ce.isNull()&& ce.hasAttribute("No") && ce.attribute("No").toInt() == j){
                                ce.setAttribute("pretime",nChildFinshTime);
                                nChildFinshTime += ce.attribute("Duration").toInt();
                                cresult = true;
                                break;
                            }
                            cnode = cnode.nextSibling();
                        }
                        if (!cresult)
                            return false;
                    }
                    e.setAttribute("Duration",nChildFinshTime);
                    nFinishTime += cycle*nChildFinshTime;
                }
                result = true;
                break;
            }
            node = node.nextSibling();
        }
        if (!result)
            return false;
    }
    root.setAttribute("Duration",nFinishTime);
    return true;
}

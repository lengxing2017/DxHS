#include "sequence.h"
#include <QDebug>
#include <QtXml>
#include "exglobal.h"

Sequence::Sequence(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(SequenceTimeout()));
}

void Sequence::sequenceDo(SequenceId id)
{    
    qDebug()<<ExGlobal::panelCode<<"id:"<<id;
    this->currSequenceId = id;
    if (id == SequenceId::Sequence_Test)
    {
        if (!ReadTestProcess(QCoreApplication::applicationDirPath()+"/Panel4.xml"))
        {
            emit sequenceFinish(SequenceResult::Result_Test_DataErr);
            return;
        }
        Sequence::nFinishCount = 0;
    }
    timer->start(1000);
}

void Sequence::SequenceTimeout()
{
    qDebug()<<"SequenceTimeout";
    if (this->currSequenceId == Sequence::SequenceId::Sequence_SelfCheck)
        emit sequenceFinish(SequenceResult::Result_SelfCheck_ok);
    else if(this->currSequenceId==Sequence::SequenceId::Sequence_OpenBox){
        emit sequenceFinish(SequenceResult::Result_OpenBox_ok);
    }
    else if(this->currSequenceId==Sequence::SequenceId::Sequence_Test){
        nFinishCount++;
        emit processFinish(100,nFinishCount);
        if (nFinishCount < 100)
            timer->start(1000);
    }
}

bool Sequence::ReadTestProcess(QString panel)
{
    QFile xmlfile(panel);
    qDebug("ReadTestProcess");
    if (!xmlfile.open(QFile::ReadOnly))
    {
        qDebug()<<"file err:"<<xmlfile.error()<<",string:"<<xmlfile.errorString()<<",file:"<<xmlfile.fileName()<<",dir:"<<QDir::currentPath()<<",apppath:"<<QCoreApplication::applicationDirPath();
        return false;
    }
    QDomDocument doc;
    if (!doc.setContent(&xmlfile))
    {
        xmlfile.close();
        return  false;
    }
    xmlfile.close();

    QDomElement root = doc.documentElement();
    qDebug()<<root.nodeName()<<"version:"<<root.attribute("version")<<",code:"<<root.attribute("code");
    QDomNode node = root.firstChild();
    while(!node.isNull())
    {
        if (node.isElement())
        {
            QDomElement e = node.toElement();

            if (e.tagName()=="Action")
                qDebug()<<e.tagName()<<",Device:"<<e.attribute("Device")<<",Duration:"<<e.attribute("Duration")<<",ActionValue:"<<e.attribute("ActionValue")<<",ActionParam:"<<e.attribute("ActionParam");
            else if(e.tagName()=="Actions")
            {
                qDebug()<<"cycle:"<<e.attribute("cycle");
                QDomNodeList list = e.childNodes();
                for(int i= 0; i<list.count();i++)
                {
                    QDomNode n = list.at(i);
                    if (n.isElement())
                    {
                        QDomElement ne = n.toElement();
                        if (ne.tagName()=="Action")
                            qDebug()<<ne.tagName()<<",Device:"<<ne.attribute("Device")<<",Duration:"<<ne.attribute("Duration")<<",ActionValue:"<<ne.attribute("ActionValue")<<",ActionParam:"<<ne.attribute("ActionParam");
                    }
                }
            }
            else if(e.tagName()=="PanelName"){
                qDebug()<<"cn:"<<e.attribute("cn");
            }
        }
        node = node.nextSibling();
    }
    return true;
}

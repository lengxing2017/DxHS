#ifndef IHANDLE_H
#define IHANDLE_H

#include <QByteArray>

class IHandle
{
public:
    virtual void display(QString data)=0;
    virtual void Report(QByteArray data, QString message)=0;//TODO:
};

#endif // IHANDLE_H

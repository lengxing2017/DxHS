#ifndef Log_h
#define Log_h
#include <QQmlEngine>
#include <qdatetime.h>
class Log
{
	public:
	
		int Logid;
		
        QDateTime LogTime;
		
        QString UserName;
		
		int LogType;
		
        QString Parm;

};

#endif

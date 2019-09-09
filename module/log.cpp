#include "log.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QCoreApplication>

static QString dirname="";

Log::Log()
{

}

void Log::setDir(QString dirName)
{
    dirName = "/share/"+dirName;
    QDir dir(dirName);
    if (!dir.exists())
        dir.mkpath(dirName);
    dirname = dirName;
}

QString Log::getDir()
{
    if (dirname == "")
    {
        //dirname = QCoreApplication::applicationDirPath();
        dirname = "/share";
    }
    return dirname;
}

void Log::LogWithTime(QString log)
{
    QFile file;

    file.setFileName(getDir()+"/log.txt");
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        qDebug()<<"file open error!";
    }
    QTextStream textStream(&file);

    QDateTime current_time = QDateTime::currentDateTime();
    QString current_time_str = current_time.toString("yyyy-MM-dd hh:mm:ss.zzz ");
    textStream<<current_time_str<<log<<endl;
    textStream.flush();
    file.close();
}

#include "commgr.h"
#include <QDebug>
#include <QDir>
#include <QThread>
#include <QException>
#include <QFile>
ComMgr::ComMgr(QObject *parent) : QObject(parent)
{

}

bool ComMgr::Load( QSerialPort *mserialPort
                    ,QString portname
                    ,int baudrate
                    ,int databits
                    , int stopBits
                    , int parity
                    ,int ackTimeoutMs
                    , int exeTimeoutMs
                    , int receiveDelayMs
                    , int sendDelayMs
                    , IHandle *pHandle)
{
    this->ackTimeoutMs = ackTimeoutMs;
    this->exeTimeoutMs = exeTimeoutMs;
    this->receiveDelayMs = receiveDelayMs;
    this->sendDelayMs = sendDelayMs;
    serialPort = mserialPort;

    serialPort->setPortName(portname);

    if(serialPort->open(QIODevice::ReadWrite) != true)
    {
        return false;
    }

    switch(baudrate)
    {
    case 115200:
    serialPort->setBaudRate(QSerialPort::Baud115200);
        break;
    }

    switch(databits)
    {
    case 8:
        serialPort->setDataBits(QSerialPort::Data8);
        break;
    }

    switch(stopBits)
    {
    case 1:
        serialPort->setStopBits(QSerialPort::OneStop);
        break;
    default:
        break;
    }

    switch (parity)
    {
    case 0:
        serialPort->setParity(QSerialPort::NoParity);
        break;
    default:
        break;
    }

    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    //create com directory,path = file name;
    QDateTime current_date_time = QDateTime::currentDateTime();//获取当前日期
    QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
    QString fileDir = "/home/ComMgrLog/";
    QString fileName = current_date + "ComMgrlog.com";

    createFile(fileDir, fileName);
    path = fileDir+fileName;

    m_pHandle = pHandle;
    qDebug()<<"thread start!";
    //this->start();
    return true;
}

void ComMgr::createFile(QString filepath,QString filename)
{
    QDir tempDir;
    //临时保存程序当前路径
    QString currentDir = tempDir.currentPath();
    //如果filepath路径不存在，创建它
    if(!tempDir.exists(filepath))
    {
        //qDebug()<<QObject::tr("不存在该路径")<<endl;
        tempDir.mkpath(filepath);
    }
    QFile *tempFile = new QFile;
    //将程序的执行路径设置到filepath下
    tempDir.setCurrent(filepath);
    //qDebug()<<tempDir.currentPath();
    //检查filepath路径下是否存在文件filename,如果停止操作。
    if(tempFile->exists(filename))
    {
        //qDebug()<<QObject::tr("文件存在");
        return ;
    }
    //此时，路径下没有filename文件，使用下面代码在当前路径下创建文件
    tempFile->setFileName(filename);
    if(!tempFile->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<QObject::tr("打开失败");
        return ;
    }
    tempFile->close();
    //将程序当前路径设置回原来的路径
    tempDir.setCurrent(currentDir);
    //qDebug()<<tempDir.currentPath();
}

bool ComMgr::TryToStart()
{
    if(IsTestMode)
    {
        return true;
    }
    else if (!serialPort->isOpen())
    {
        if (serialPort->open(QIODevice::ReadWrite))
        {
            //"open success"
            return true;
        }
        else
        {
            //"open failed"
            return false;
        }
    }
    else
    {
        return false;
    }
}

//关闭串口
void ComMgr::closeSerialPort()
{
    if (!IsTestMode && serialPort != NULL)
    {
        //this->quit();
        serialPort->close();
        serialPort = NULL;
        qDebug()<<"thread terminal!";
    }
}

void ComMgr::run()
{
    while (1)
    {
        TimeoutAsync();
    }
}

bool ComMgr::Sends(Frame frame)
{
    if (!IsTestMode && !serialPort->isOpen())
    {
        //"串口未打开"

        return false;
    }
    else if(frame.SendData.size()<9)
    {
        Recorder(frame.SendData,"invalid send data length. (<9)");

        return false;
    }
    else if(Current.IsNull || Current.BufferFrame.FrameStatus == EFrameStatus::Fns)
    {


        QThread::msleep(sendDelayMs);//开发板发串口数据到电脑时需要延时，否则接收数据会被分段接收，由于开发板发送速度没有电脑运行速度快

        Current.BufferFrame.FrameStatus = EFrameStatus::Send;

        //QByteArray packageData = ComMgre::ComMgrLibrary::Package(frame.SendData);//扩展80协议

        //serial->Write(packageData, 0, packageData.length);

        Current.BufferFrame = frame;

        if(!IsTestMode)
        {
                //QByteArray data1("ff");//TEST
                //serialPort->write(data1);//TEST
            serialPort->write(Current.BufferFrame.SendData);//发送
            //serialPort->write(Current.BufferFrame.SendData.toHex());//TEST发送
        }

        //记录日志
        Record(Current.BufferFrame.SendData, true);

        SendDatetime = QTime::currentTime();
        Current.IsNull = false;

        if(!IsTestMode)
        {
            while(Current.BufferFrame.FrameStatus != EFrameStatus::Fns
                  && Current.BufferFrame.FrameStatus != EFrameStatus::Timeout)
            {
                QThread::msleep(10);//毫秒
            }
        }

        bool result = (Current.BufferFrame.FrameStatus == EFrameStatus::Fns);

        return result;
    }
    else
    {
        return false;
    }
}

QByteArray ComMgr::sFrame(QByteArray data)
 {
    if(data.size() < 9)
    {
        return data;
    }
    else
    {
        data[0] = data.size() / 256;
        data[1] = data.size() % 256;
        data[2] = 0x00;
        data[4] = index;
        index = index+1;
        data[7] = (data.size() - 9) / 256;
        data[8] = (data.size() - 9) % 256;
        data[3] = GetCheckSum(data);
        return data;
    }
 }

quint8 ComMgr::GetCheckSum(QByteArray data)
{
    quint8 cs = data[0];

    //循环计算校验和
    for (int i = 1; i < data.size(); i++)
    {
        //跳过校验位
        if (i == 3)
        {
            continue;
        }
        else
        {
            cs = cs ^ data[i];
        }
    }
    return cs;
}

void ComMgr::TestReceive(QByteArray data)
{
    TestReceiveData = data;

    Receive();
}
void ComMgr::Receive()
{
    if(((Current.IsNull==false)&&IsTestMode) || (serialPort->isOpen()&&(Current.IsNull==false)))
    {
        QThread::msleep(receiveDelayMs);

        //通过SerialPort获取接收数据
        QByteArray data;
        quint8 datalegth;
        if(!IsTestMode)
        {
             data = serialPort->read(2);
             datalegth = (quint8)data[1];
             data += serialPort->read(datalegth-2);

             if(data.isEmpty())
             {
                 return;
             }
        }
        else
        {
            data = TestReceiveData;
        }

        if(data.size() >=10)
        {
            if(Current.BufferFrame.SendData[6] == data[6])
            {
                if((quint8)data[9] == 0xBB || (quint8)data[9] == 0xCC)
                {
                    Current.BufferFrame.FrameStatus =  EFrameStatus::Ack;
                    //记录日志
                    Record(data, false);
                    data.clear();
                }
                else if((quint8)data[9] == 0x33 || (quint8)data[9] == 0x55)
                {
                    Current.BufferFrame.ReceiveData = data;

                    Current.BufferFrame.FrameStatus =  EFrameStatus::Fns;

                    //记录日志
                    Record(data, false);
                    data.clear();
                    Current.IsNull=true;
                }
                else
                {
                    //记录日志
                    Recorder(data, "not match ack type. ([9])");
                    data.clear();
                }
            }
            else
            {
                Recorder(data,"not match frame type. ([6])");
                data.clear();
            }

        }
        else if(!data.isEmpty() && data.size()<10)
        {
            Recorder(data,"invalid receive data length (<10)");
            data.clear();
        }
        else
        {
            return;
        }
    }
    else
    {
        //Recorders("serial port is not open during reciving.");
        return;
    }
}

void ComMgr::TimeoutAsync()
{
    try
    {
            QTime currentDatetime = QTime::currentTime();

            if(!Current.IsNull && Current.BufferFrame.FrameStatus!=EFrameStatus::Fns)
            {
                switch(Current.BufferFrame.FrameStatus)
                {
                    case EFrameStatus::Send:
                        if(SendDatetime.msecsTo(currentDatetime) > ackTimeoutMs)
                        {
                            //发布异常
                            //m_pHandle->Report(QByteArray("10050"), QString(Current.BufferFrame.SendData));
                            Recorder(Current.BufferFrame.SendData, "10050:应答超时");
                            Current.BufferFrame.FrameStatus = EFrameStatus::Timeout;

                            Current.IsNull = true;//test
                        }
                    break;
                    case EFrameStatus::Ack:
                        if(SendDatetime.msecsTo(currentDatetime) > exeTimeoutMs)
                        {
                            //m_pHandle->Report(QByteArray("10051"), QString(Current.BufferFrame.SendData));
                            Recorder(Current.BufferFrame.SendData, "10051:执行超时");
                            Current.BufferFrame.FrameStatus = EFrameStatus::Timeout;

                            Current.IsNull = true;//test
                        }
                    break;
                    case EFrameStatus::Fns:
                    break;
                    case EFrameStatus::Timeout:
                    break;
                }
            }

            QThread::msleep(10);
    }
    catch(QException &e)
    {
        Recorders(e.what());
    }
}

void ComMgr::Record(QByteArray data, bool isSend)
{
    QFile outputfile(path);
    QString txtMessage;
    txtMessage = ByteArrayToHexString(data);

    if(!outputfile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug()<<QObject::tr("打开失败");
    }

    QDateTime current_record_time = QDateTime::currentDateTime();//获取当前日期
    QString current_date = current_record_time.toString("yyyy.MM.dd hh:mm:ss");
    QTextStream textStream(&outputfile);

    if(isSend )
    {
        //保存输出相关信息到指定文件
        textStream << current_date << (" SND:") << txtMessage << endl;
    }
    else
    {
        //保存输出相关信息到指定文件
        textStream << current_date << (" RCV:") << txtMessage << endl;
    }
    outputfile.close();
}

void ComMgr::Recorder(QByteArray data, QString message)
{
    QFile outputfile(path);
    QString txtMessage;
    txtMessage = ByteArrayToHexString(data);

    if(!outputfile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug()<<QObject::tr("打开失败");
    }

    QDateTime current_record_time = QDateTime::currentDateTime();//获取当前日期
    QString current_date = current_record_time.toString("yyyy.MM.dd hh:mm:ss");
    QTextStream textStream(&outputfile);

    //保存输出相关信息到指定文件
    textStream << current_date << (" ERR:") << message << (":") << txtMessage << endl;

    outputfile.close();
}

void ComMgr::Recorders(QString message)
{
    QFile outputfile(path);

    if(!outputfile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug()<<QObject::tr("打开失败");
    }

    QDateTime current_record_time = QDateTime::currentDateTime();//获取当前日期
    QString current_date = current_record_time.toString("yyyy.MM.dd hh:mm:ss");
    QTextStream textStream(&outputfile);

    //保存输出相关信息到指定文件
    textStream << current_date << ("ERR:") << message << endl;

    outputfile.close();
}

QString ComMgr::ByteArrayToHexString(QByteArray data)
{
    QString ret(data.toHex());
    int len = ret.length()/2;
    qDebug()<<len;
    for(int i=1;i<len;i++)
    { qDebug()<<i;
        ret.insert(2*i+i-1,"-");
    }
    qDebug()<<ret;
    return ret;
}

QByteArray ComMgr::HexStringToByteArray(QString HexString)
{
    bool ok;
    QByteArray ret;
    HexString = HexString.trimmed();
    HexString = HexString.simplified();
    QStringList sl = HexString.split(" ");

    foreach (QString s, sl) {
    if(!s.isEmpty()) {
         char c = s.toInt(&ok,16)&0xFF;
         if(ok){
             ret.append(c);
         }
         else
         {
             qDebug()<<"invalid hex string"<<s;
         }

        }
    }
    return ret;
}


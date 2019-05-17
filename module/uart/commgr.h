#ifndef COMMGR_H
#define COMMGR_H
#include <QObject>
#include <QQmlEngine>
#include <QByteArray>
#include <QThread>
#include <QTime>
#include <QSerialPort>
#include "framebuffer.h"
#include "frame.h"
#include "ihandle.h"
#include "framestatus.h"


class ComMgr : public QObject
{
    Q_OBJECT

public:

    explicit ComMgr(QObject *parent = nullptr);

    FrameBuffer Current;

    QString path;

    //ONLY TEST USE
    bool IsTestMode = false;

    //ONLY TEST USE
    void TestReceive(QByteArray data);

    void Close();

    bool TryToStart();

    void closeSerialPort();

    bool Sends(Frame frame);

    void Receive();

    QByteArray sFrame(QByteArray data);

    void createFile(QString filepath,QString filename);

    bool Load(QSerialPort *mserialPort
                        ,QString portname
                        ,int baudrate
                        ,int databits
                        , int stopBits
                        , int parity
                        ,int ackTimeoutMs
                        , int exeTimeoutMs
                        , int receiveDelayMs
                        , int sendDelayMs
                        , IHandle *pHandle);

    QString ByteArrayToHexString(QByteArray data);

    QByteArray HexStringToByteArray(QString HexString);

protected:
    void run();

private:
    QByteArray TestReceiveData;

    int sendDelayMs,receiveDelayMs;

    int ackTimeoutMs;

    int exeTimeoutMs;

    quint8 index = 0;

    QTime SendDatetime;

    void TimeoutAsync();

    void ReceivePacket();

    static quint8 GetCheckSum(QByteArray data);

    void Record(QByteArray data, bool isSend);

    void Recorder(QByteArray data, QString message);

    void Recorders(QString message);

private:
        QSerialPort *serialPort;

        IHandle *m_pHandle;

signals:

public slots:

};

#endif // COMMGR_H

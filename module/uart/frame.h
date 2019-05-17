#ifndef FRAME_H
#define FRAME_H


#include <QByteArray>
#include "framestatus.h"
class Frame
{

public:

    QByteArray SendData;

    QByteArray ReceiveData;

    EFrameStatus FrameStatus = EFrameStatus::Fns;

    bool IsSuccess()
    {
        return FrameStatus == EFrameStatus::Fns;
    }
};

#endif // FRAME_H

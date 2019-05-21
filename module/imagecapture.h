#ifndef IMAGECAPTURE_H
#define IMAGECAPTURE_H

#include <QObject>
#include "v4l.h"
class ImageCapture : public QObject
{
    Q_OBJECT
public:
    explicit ImageCapture(QObject *parent = nullptr);

signals:

public slots:

private:
    pass_data pd;
};

#endif // IMAGECAPTURE_H

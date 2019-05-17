#ifndef IMAGECAPTURE_H
#define IMAGECAPTURE_H

#include <QObject>

class ImageCapture : public QObject
{
    Q_OBJECT
public:
    explicit ImageCapture(QObject *parent = nullptr);

signals:

public slots:
};

#endif // IMAGECAPTURE_H
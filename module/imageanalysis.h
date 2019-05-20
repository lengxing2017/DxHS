#ifndef IMAGEANALYSIS_H
#define IMAGEANALYSIS_H

#include <QObject>

class ImageAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit ImageAnalysis(QObject *parent = nullptr);

signals:

public slots:
};

#endif // IMAGEANALYSIS_H
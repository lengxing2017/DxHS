#include "printermgr.h"
#include "QPainter"
#include "QPrinter"
#include <QPrintDialog>
PrinterMgr::PrinterMgr(QObject *parent) : QObject(parent)
{

}

void PrinterMgr::printDocument(QPrinter *printer)
{
    //http://doc.qt.io/qt-5/qpainter.html
    QPainter painter;
    painter.begin(printer);

    QString family("Arial");
    QString style("Normal");

    //
    QFont font(family, 32, 50, false);
    font.setStyleName(style);
    font = QFont(font, painter.device());

    //
    QFontMetricsF fontMetrics(font);
    QRectF rect = fontMetrics.boundingRect(QString("%1 %2").arg(family).arg(style));

    //如果不scale的话，会因为打印的字太小而看不见。
    qreal xScale = printer->pageRect().width() / rect.width();
    qreal yScale = printer->pageRect().height() / rect.height();
    double scale = qMin(xScale, yScale);

    //
    //Saves the current painter state (pushes the state onto a stack).
    painter.save();
    //Translates the coordinate system by the given offset;
    painter.translate(printer->pageRect().width() / 2.0, printer->pageRect().height() / 2.0);
    //Scales the coordinate system by (sX, sY).
    painter.scale(scale, scale);

    //Background x character for assure the bound and string draw orientation.
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(0,0,rect.width()/2,rect.height());
    painter.setBrush(QBrush(Qt::black));
    painter.drawLine(0, 0, rect.width()/2, rect.height());
    painter.drawLine(0, rect.height(), rect.width()/2, 0);

    //Notice string vertical orientation in printer is negative from screen.
    painter.drawText(QPointF(0,0),
                     QString("%1-%2").arg(family).arg(style));

    //Restores the current painter state (pops a saved state off the stack).
    painter.restore();

    //before begin new page.
    //printer->newPage();

    //after all done.
    painter.end();
    printer->setPrinterName("");
    //printer.
}

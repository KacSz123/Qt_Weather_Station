#include "thermometer.h"
#include "QDebug"
Thermometer::Thermometer(QWidget *parent) : QWidget(parent)
{
    wTimer=new QTimer(this);
    wTimer->setObjectName("Timer");

    this->setStyleSheet("background-color: Blue");


    connect(wTimer,SIGNAL(timeout()), this, SLOT(on_Timer_timeout()));
}


void Thermometer::paintEvent(QPaintEvent *)
{

    QPainter p2(this);
    double _Scale;
    _Scale=height()/static_cast<double>(tlo->height());

    p2.scale(_Scale, _Scale);
    p2.drawRect(0,0,width()+1, height()+1);
    p2.drawImage(0,0,*tlo);
    QPen Red((QColor(255,0,0)), 10);
    p2.setPen(Red);


    p2.drawLine(width()/2+35,425,width()/2+35,430-((double)Temp/10.0)*7.45-60);
  //  qDebug()<<scaler<<"   ";
}
void Thermometer :: on_Timer_timeout()
{

    update();
}

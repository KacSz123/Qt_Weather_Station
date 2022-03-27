#include "barometer.h"
#include "QDebug"
#include "math.h"
Barometer::Barometer(QWidget *parent) : QWidget(parent)
{
    wTimer=new QTimer(this);
    wTimer->setObjectName("Timer");



    connect(wTimer,SIGNAL(timeout()), this, SLOT(on_Timer_timeout()));
}


void Barometer::paintEvent(QPaintEvent *)
{

    QPainter p2(this);
    double _Scale;
    _Scale=height()/static_cast<double>(tlo->height());

    p2.scale(_Scale, _Scale);
    p2.drawRect(0,0,width()+1, height()+1);
    p2.drawImage(0,0,*tlo);
    QPen Red((QColor(255,0,255)), 10);
    p2.setPen(Red);


    int wb=this->width();
    int hb=this->height();

    p2.drawLine(wb/2+50,hb/2+50,165-(cos((3.14*Press)/1100))*127, wb/2+50-(sin((3.14*Press)/1100))*127);
    // qDebug()<<ui->Label_pic_2->width()/2+50<<"\n"<<ui->Label_pic_2->height()/2+50;
    //qDebug()<<sqrt(2*(165-75)*(165-75));

    /*
    p2.drawLine(width()/2+35,425,width()/2+35,430-((double)Temp/10.0)*7.44-63);*/
    qDebug()<<scaler<<"   ";
}
void Barometer :: on_Timer_timeout()
{

    update();
}

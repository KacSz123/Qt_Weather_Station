#include "mainqw.h"
#include <QDebug>
#include <QPainter>
MainQW::MainQW(QWidget *parent) : QWidget(parent)
{
    wTimer=new QTimer(this);
    wTimer->setObjectName("Timer");



    this->setStyleSheet("background-color: Blue");


    connect(wTimer,SIGNAL(timeout()), this, SLOT(on_Timer_timeout()));
}


void MainQW::paintEvent(QPaintEvent *)
{

    QPainter p2(this);
    double _Scale;



    _Scale=height()/static_cast<double>(tlo->height());
    p2.scale(_Scale, _Scale);
    p2.drawImage(0,0,*tlo);



    AnimateRain(&p2);
    AnimateSun(&p2);
}
void MainQW :: on_Timer_timeout()
{

    int ray_xs=380, ray_ys=130;
    drop_y+=5;
    drop_y2+=5;
    drop_y3+=5;
    if(drop_y>tlo->height())
        drop_y=0;

    if(drop_y2>tlo->height())
        drop_y2=0;

    if(drop_y3>tlo->height())
        drop_y3=0;

    ray_x-=1;
    ray_y+=1;

    iter++;
    if(iter>=20)
    {
        iter=0;
        ray_y=ray_ys;
        ray_x=ray_xs;
    }
    //qDebug()<<ray_y;
    update();
}



void MainQW :: setLightLvl(int l)
{
    if(l>=75)
    {
        Light_lvl=3;
    }
    else if(l<75 && l>=50)
    {
        Light_lvl=2;
    }
    else if(l<50 && l>=25)
    {
        Light_lvl=1;
    }
    else
    {
        Light_lvl=0;
    }
}
void MainQW :: setRainLvl(int R)
{
    if(R>=75)
    {
        Rain_lvl=3;
    }
    else if(R<75 && R>=50)
    {
        Rain_lvl=2;
    }
    else if(R<50 && R>=25)
    {
        Rain_lvl=1;
    }
    else
    {
        Rain_lvl=0;
    }
}

void MainQW :: AnimateSun(QPainter *paint)
{
    if(Light_lvl==3)
    {
        paint->drawImage(ray_x, ray_y, *ray);

        paint->translate(380, 50);
        paint->rotate(30);
        paint->drawImage(-iter, iter, *ray);


        paint->rotate(-30);
        paint->translate(40, -60);
        paint->rotate(60);
        paint->drawImage(-iter, iter, *ray);

        paint->rotate(-60);
        paint->translate(10, 190);
        paint->rotate(-30);
        paint->drawImage(-iter, iter, *ray);

        paint->rotate(30);
        paint->translate(50, 20);
        paint->rotate(-60);
        paint->drawImage(-iter, iter, *ray);

    }

    else if(Light_lvl==2)
    {
        paint->drawImage(ray_x, ray_y, *ray);

        paint->translate(380, 50);
        paint->rotate(30);
        paint->drawImage(-iter/2, iter/2, *ray);


        paint->rotate(-30);
        paint->translate(40, -60);
        paint->rotate(60);
        paint->drawImage(-iter/2, iter/2, *ray);

        paint->rotate(-60);
        paint->translate(10, 190);
        paint->rotate(-30);
        paint->drawImage(-iter/2, iter/2, *ray);

    }
    else if(Light_lvl==1)
    {
        paint->drawImage(ray_x+(iter/3), ray_y-(iter/3), *ray);

        paint->translate(380, 50);
        paint->rotate(30);
        paint->drawImage(-(iter/3), (iter/3), *ray);


        paint->rotate(-30);
        paint->translate(50, 130);
        paint->rotate(-30);
        paint->drawImage(-(iter/3), (iter/3), *ray);

    }
}
void MainQW :: AnimateRain(QPainter *paint)
{

    if(Rain_lvl==1)
    {
        paint->drawImage(drop_x, drop_y, *drop);
        paint->drawImage(drop_x+250, drop_y, *drop);
        paint->drawImage(drop_x-150, drop_y, *drop);

        paint->drawImage(drop_x, drop_y2, *drop);
        //paint->drawImage(drop_x+130, drop_y2, *drop);
       // paint->drawImage(drop_x-170, drop_y2, *drop);


        //  paint->drawImage(drop_x, drop_y3, drop);
        paint->drawImage(drop_x+180, drop_y3, *drop);
        paint->drawImage(drop_x-240, drop_y3,* drop);

        //p2.setBackground(Qt::blue);
       // qDebug()<<"test1  "<<Rain_lvl;
    }
    else if(Rain_lvl==2)
    {
        paint->drawImage(drop_x-50, drop_y, *drop);
        paint->drawImage(drop_x+60, drop_y, *drop);
        paint->drawImage(drop_x+250, drop_y, *drop);
        paint->drawImage(drop_x-280, drop_y, *drop);

        paint->drawImage(drop_x-20, drop_y2, *drop);
        paint->drawImage(drop_x+60, drop_y2, *drop);
        paint->drawImage(drop_x+160, drop_y2, *drop);
        paint->drawImage(drop_x-170, drop_y2, *drop);


        paint->drawImage(drop_x+100, drop_y3, *drop);
        paint->drawImage(drop_x+180, drop_y3, *drop);
        paint->drawImage(drop_x-240, drop_y3, *drop);
        paint->drawImage(drop_x-160, drop_y3, *drop);

        //p2.setBackground(Qt::blue);
       // qDebug()<<"test1  "<<Rain_lvl;
    }
    else if(Rain_lvl==3)
    {
        paint->drawImage(drop_x, drop_y, *drop);

        paint->drawImage(drop_x+120, drop_y, *drop);
        paint->drawImage(drop_x+220, drop_y, *drop);
        paint->drawImage(drop_x-120, drop_y, *drop);
        paint->drawImage(drop_x-220, drop_y, *drop);

        paint->drawImage(drop_x, drop_y2, *drop);
        paint->drawImage(drop_x+110, drop_y2, *drop);
        paint->drawImage(drop_x-110, drop_y2, *drop);
        paint->drawImage(drop_x+200, drop_y2, *drop);
        paint->drawImage(drop_x-280, drop_y2, *drop);

        paint->drawImage(drop_x-30, drop_y3, *drop);
        paint->drawImage(drop_x+60, drop_y3, *drop);
        paint->drawImage(drop_x-80, drop_y3, *drop);
        paint->drawImage(drop_x+250, drop_y3, *drop);
        paint->drawImage(drop_x-200, drop_y3, *drop);
    }

}

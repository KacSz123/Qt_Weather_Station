#include "diagrams.h"
#include "ui_diagrams.h"

#include <QWidget>
#include <QDebug>
#include <QDialog>
Diagrams::Diagrams(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Diagrams)
{

    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->setupUi(this);
    Time=0;
    //Wykres temperatury
    //tytul
    ui->TempPlot->plotLayout()->insertRow(0);
    ui->TempPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->TempPlot, tr("Temperature"), QFont("sans", 12, QFont::Bold)));
    ui->label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    ui->label_2->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    ui->label_3->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    ui->label_4->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    //dodanie grafu
    ui->TempPlot->addGraph();
    ui->TempPlot->graph(0)->setPen(QPen(QColor("blue")));
    ui->TempPlot->graph(0)->setName("Temp");
    ui->TempPlot->yAxis->setLabel("Temperature[C]");

    //y
    ui->TempPlot->yAxis->setRange(-10,40);

    //czas na osi X
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->TempPlot->xAxis->setTicker(timeTicker);
    ui->TempPlot->axisRect()->setupFullAxesBox();
    ui->TempPlot->xAxis->setLabel("Time [hh:mm:ss]");

    //wykres cisnienia
    ui->PressPlot->plotLayout()->insertRow(0);
    ui->PressPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->PressPlot, tr("Pressure"), QFont("sans", 12, QFont::Bold)));

    ui->PressPlot->addGraph();
    ui->PressPlot->graph(0)->setPen(QPen(QColor("red")));
    ui->PressPlot->graph(0)->setName("Pressure");
    ui->PressPlot->yAxis->setLabel("Pressure[hPa]");

    ui->PressPlot->yAxis->setRange(0,1200);

    ui->PressPlot->xAxis->setTicker(timeTicker);
    ui->PressPlot->axisRect()->setupFullAxesBox();
    ui->PressPlot->xAxis->setLabel("Time [hh:mm:ss]");


    //wykres deszczu
    ui->RainPlot->plotLayout()->insertRow(0);
    ui->RainPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->RainPlot, tr("Rain Intensity"), QFont("sans", 12, QFont::Bold)));

    ui->RainPlot->addGraph();
    ui->RainPlot->graph(0)->setPen(QPen(QColor("green")));
    ui->RainPlot->graph(0)->setName("Rain Intensity");
    ui->RainPlot->yAxis->setLabel("Rainfalls[%]");

    ui->RainPlot->yAxis->setRange(0,100);

    ui->RainPlot->xAxis->setTicker(timeTicker);
    ui->RainPlot->axisRect()->setupFullAxesBox();
    ui->RainPlot->xAxis->setLabel("Time [hh:mm:ss]");

    //wykres natezenia swiatla
    ui->LightPlot->plotLayout()->insertRow(0);
    ui->LightPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->LightPlot, tr("Light Intensity"), QFont("sans", 12, QFont::Bold)));

    ui->LightPlot->addGraph();
    ui->LightPlot->graph(0)->setPen(QPen(QColor("black")));
    ui->LightPlot->graph(0)->setName("Light Intensity");
    ui->LightPlot->yAxis->setLabel("Light Int.[%]");

    ui->LightPlot->yAxis->setRange(0,100);

    ui->LightPlot->xAxis->setTicker(timeTicker);
    ui->LightPlot->axisRect()->setupFullAxesBox();
    ui->LightPlot->xAxis->setLabel("Time [hh:mm:ss]");
}

Diagrams::~Diagrams()
{
    delete ui;
}

void Diagrams::getData(int Temp, int Press, int Rain, int Light)
{

    Time+=static_cast<double> (50.0/1000);
    ui->TempPlot->graph(0)->addData(Time, (double)(Temp/10.0));
    ui->TempPlot->xAxis->setRange(Time, 1000, Qt::AlignRight);
    ui->TempPlot->replot();
    ui->TempPlot->update();
    ui->label->setNum((double)(Temp/10.0));


    ui->PressPlot->graph(0)->addData(Time, Press);
    ui->PressPlot->xAxis->setRange(Time, 5000, Qt::AlignRight);
    ui->PressPlot->replot();
    ui->PressPlot->update();
    ui->label_2->setNum(Press);

    ui->RainPlot->graph(0)->addData(Time, (double)((1025-Rain)/1000.0)*100.0);
    ui->RainPlot->xAxis->setRange(Time, 100, Qt::AlignRight);
    ui->RainPlot->replot();
    ui->RainPlot->update();
    ui->label_3->setNum((double)((1025-Rain)/1000.0)*100.0);

    //Light=(double)((Light)/1000.0)*100.0;
    //qDebug()<<"light  "<<Light<<"\n";
    ui->LightPlot->graph(0)->addData(Time, (double)((Light)/1000.0)*100.0);
    ui->LightPlot->xAxis->setRange(Time, 100, Qt::AlignRight);
    ui->LightPlot->replot();
    ui->LightPlot->update();
    ui->label_4->setNum((double)((Light)/1000.0)*100.0);

}


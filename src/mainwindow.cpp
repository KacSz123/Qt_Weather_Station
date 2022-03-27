#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QSerialPortInfo>
#include <QDebug>
#include <QLabel>
#include <QDateTime>
#include <QTableWidget>
#include <QString>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QColor>
#include <QPen>
#include <math.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    nw=new Connect_window(this);
    Dg=new Diagrams;
    ui->mainFrame->setStyleSheet("background-color:rgb(201,249,250)");
    ui->DataFrame->setStyleSheet("font-weight: bold;background-color:rgb(245,245,245)");

    ///sekcja rysowania bitmap


    //wywolanie timera dla srodkowego okna

    ui->Label_pic_main->drawDrops();
    ui->Therm->startTimer();
    ui->Barom->startTimer();



    ///sekcja ustawien qlabel z wypisanymi danymi
    ui->LabelT->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    ui->LabelL->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    ui->LabelR->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    ui->LabelP->setAlignment(Qt::AlignCenter | Qt::AlignCenter);


    ///sekcja polaczen miedzy oknami

    //ustawienie polaczenia Connect_Window-->MainWindow
    QObject::connect(nw, SIGNAL(sendMsg(int, int, int, int)), this, SLOT(receiveMsg(int, int, int ,int )));
    //ustawienie polaczenia Connect_Window-->Diagrams
    QObject::connect(nw, SIGNAL(sendMsg(int, int, int, int)), Dg, SLOT(getData(int, int ,int, int)));




}

MainWindow::~MainWindow()
{

    delete ui;
    delete nw;
    delete Dg;

}




void MainWindow::receiveMsg(int Temp1, int Press1, int Rain1, int Light1)
{
    Temp=Temp1;
    Press=Press1;
    Rain=(double)((1025-Rain1)/1000.0)*100.0;
    Light=(double)((Light1)/1000.0)*100.0;

    ui->LabelT->setNum((double)(Temp1/10.0));
    ui->LabelP->setNum(Press1);
    ui->LabelR->setNum((double)((1025-Rain1)/1000.0)*100.0);
    ui->LabelL->setNum((double)((Light1)/1000.0)*100.0);
    ui->Therm->setTemp(Temp);
    ui->Barom->setPress(Press);
    ui->Label_pic_main->setRainLvl(Rain);
    ui->Label_pic_main->setLightLvl(Light);

}


void MainWindow :: receiveMsg(DataFrame *D)
{
    qDebug()<<"from mainwindow: ";
    D->display_DataFrame();
}


void MainWindow::on_actionPo_cz_triggered()
{
    nw->show();
}

void MainWindow::on_actionWykresy_triggered()
{
    Dg->show();
}

void MainWindow::on_actionWyjd_triggered()
{
    nw->close();
    Dg->close();
    this->close();

}


void MainWindow::closeEvent(QCloseEvent* e)  {


    QMessageBox::StandardButton resBtn = QMessageBox::question( this, ":(",
                                                                tr("Czy chcesz wyjść?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::No);
    if (resBtn != QMessageBox::Yes) {
        e->ignore();
    } else {
        nw->close();
        Dg->close();
        e->accept();
    }
}

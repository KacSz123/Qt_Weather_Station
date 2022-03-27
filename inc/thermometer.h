#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <QMainWindow>
#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QSpinBox>
#include <QPainter>
#include <QLabel>

class Thermometer : public QWidget
{
    Q_OBJECT
    QTimer *wTimer=nullptr;

    /*!
     * \brief tlo
     * Zmienna przechowująca obraz tła
     */
    QImage *tlo=new QImage(":/new/prefix1/img/Thermometer.png");
    int Temp=0;
    double scaler=0;
public:
    explicit Thermometer(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

    /*!
     * \brief startTimer
     * Funkcja rozpoczyna działanie licznika odpowiedzialnego
     * za animacje w widgecie
     */
    void startTimer(){wTimer->start(50);};

    void setTemp(const int &tmp){Temp=tmp;}
public slots:

    /*!
      * \brief on_Timer_timeout
      * Slot odbierający sygnał od timera i realizujący animację
      * słupka rtęci w termometrze.
      *
      */
    void on_Timer_timeout();

signals:
};

#endif // THERMOMETER_H

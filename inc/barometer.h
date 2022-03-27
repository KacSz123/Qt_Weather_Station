#ifndef BAROMETER_H
#define BAROMETER_H

#include <QMainWindow>
#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QSpinBox>
#include <QPainter>
#include <QLabel>
class Barometer : public QWidget
{
    Q_OBJECT
    QTimer *wTimer=nullptr;

    /*!
     * \brief tlo
     * Zmienna przechowująca obraz tła
     */
    QImage *tlo= new QImage(":/new/prefix1/img/bar2.png");
    int Press=0;
    double scaler=0;
public:
    explicit Barometer(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

    /*!
     * \brief startTimer
     * Funkcja rozpoczyna działanie licznika odpowiedzialnego
     * za animacje w widgecie
     */
    void startTimer(){wTimer->start(50);};

    void setPress(const int &tmp){Press=tmp;}
public slots:

    /*!
      * \brief on_Timer_timeout
      * .
      *
      */
    void on_Timer_timeout();

signals:

};

#endif // BAROMETER_H

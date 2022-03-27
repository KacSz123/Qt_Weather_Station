#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

/*!
 * \file
 * \brief Zawiera definicję Klasy DigitalClock
 *
 * Plik zawiera definicję klasy DigitalClock,
 *  która odpowiada za wyświetlania zegara z
 *  cyferblatem o rzeczywistym pomiarze czasu
 */

#include <QWidget>
#include<QTimer>
#include<QTime>
#include <QLCDNumber>
/*!
 * \brief The DigitalClock class
 * klasa odpowiedzialna za wyswietlanie zegara w mainWindow
 * korzysta z klas Qtimer, QTime i QLCDNumber
 */
class DigitalClock : public QLCDNumber
{
    Q_OBJECT
public:
    /*!
   * \brief Konstruktor bezparametryczny
   * Kontruktor bezparametryczny klasy DigitalClock
   * Tworzy nowy obiekt tej klasy
   * \param[in] Wskaźnik na Rodzica
   */

    DigitalClock(QWidget *parent = nullptr);

signals:

private slots:
    /*!
   * \brief Wyświetla wygenerowany zegar
   * slot odpowiadajacy za wyswietlenie wygenerowanego zegara cyfrowego
   *    Zgodnie z właściwościami ustanowionymi przez konstruktor
   *
   */
    void showTime();
};

#endif // DIGITALCLOCK_H

#ifndef DIAGRAMS_H
#define DIAGRAMS_H

/*!
 * \file
 * \brief Definicja klasy Diagram
 *
 * Plik zawiera definicję klasy Diagram,
 * jest to klasa pochodna do klasy QWidget
 *
 */
#include "qcustomplot.h"
#include <QWidget>


namespace Ui {

class Diagrams;
}

/*!
 * \brief The Diagrams class
 *  Definicja klasy Diagrams
 *  Modeluje pojęcie okna Diagrams
 * odpowiadajacej za  zdefiniowanie i obsługe okna z wykresami
 */
class Diagrams : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Diagrams
     * \param[in] parent wskaznik na rodzica
     * Konstruktor klasy Diagrams
     * Odpowiada za zdefiniowanie wygladu i parametrów okna diagrams
     * Zdefiniowane sa 4 wykresy w oknie zakladkowym
     */
    explicit Diagrams(QWidget *parent = nullptr);
    ~Diagrams();

private slots:
    /*!
 * \brief Odbiera sygnał od obiektu connect_Window
 * * Slot odpowiadajacy za odbieranie sygnalow od obiektu klasy Connect_Window
 * przyjmuje wartosci int i konwertuje je na odpowiednie wartosci(wartość temperatury),
 *  tak aby mozna bylo wyswietlic je na wykresie i realizuje rysowanie wykresów
 *
 * \param[in] Przeslana wartosc temperatury z portu w zakresie -100 do 400
 * \param[in] Przeslana wartosc cisnienia z portu,
 * przyjmuje wartości w zakresie od 0 do 1100 hPa
 * \param[in] Przeslana wartosc intensywnosci deszczu z portu,
 * wyrazona w '%' w zakresie od 0 do 100
 * \param[in] Przeslana wartosc nat. swiatla z portu, ,
 * wyrazona w '%' w zakresie od 0 do 100
 *
 *
 */
    void getData(int Temp, int Press, int Rain, int Light);



private:
    Ui::Diagrams *ui;

    /*!
     * \brief Time
     * zmienna odpwowiedzialna za czas
     */
    double Time;
};

#endif // DIAGRAMS_H

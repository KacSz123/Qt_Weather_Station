#ifndef DATAFRAME_H
#define DATAFRAME_H

/*!
  * \file
  * \brief Definicja klasy DataFrame
  *
  * Plik zawiera definicję klasy DataFrame,
  * ktora reprezentuje ramkę danych przesyłanych pomiedzy aplikacja
  * i Arduino.
  */
#include "CRC8.h"
#include <QDebug>
#define POLYNOMIAL_9 0x07
using namespace std;

/*!
 * \brief The DataFrame class
 *
 * Modeluje pojecie ramki danych
 *
 * Klasa zawiera 4 zmienne reprezentujace dane przesylane z urządzenia
 * Klasy, które pozwalają przetwarzac te dane i sprawdzic ich poprawność
 *
 */
class DataFrame
{
public:
    /*!
     * \brief LightIntensity
     * Zmienna przedstawiająca aktualnie odebraną wartość
     * Intensywności światła
     */
    int LightIntensity=0;
    /*!
     * \brief Pressure
     *
     * Zmienna przedstawiająca aktualnie odebraną wartość
     * ćiśnienia
     */
    int Pressure=0;
    /*!
     * \brief Rain
     *
     * Zmienna przedstawiająca aktualnie odebraną wartość
     * Intensywności opadów
     */
    int Rain=0;
    /*!
     * \brief Temp
     *
     * Zmienna przedstawiająca aktualnie odebraną wartość
     * temperatury
     */
    int Temp=0;
    //string pDataFrame;

    bool Read;

public:
    /*!
     * \brief Konstruktor bezparametryczny
     *
     * Inicjalizuje obiekt klasy DataFrame,
     * przypisuje wszystkim zmiennym wartosc 0
     */
    DataFrame();

    ~DataFrame();

    /*!
     * \brief Konstruktor parametryczny klasy Dataframe
     * Inicjalizuje obiekt klasy DataFrame na podstawie
     * przekazanej ramki danych. Parsuje otrzymaną ramkę danych, po czym sprawdza
     *  poprawność danych na podstawie CRC8 i przypisuje wartości do zmiennych
     * \param[in] Data przekazywana ramka danych, po parsowaniu i odczytaniu danych
     * przekazuje wartosci do zmiennych.
     */
    DataFrame(string Data);

    /*!
     * \brief Zwraca wartosc przekazanej temperatury
     * Zwraca aktualna wartość temperatury
     * \return Zwraca odczytana wartosc temperatury
     * odczytana z ramki danych są to dane nie przetworzone w zakresie od -100 do 400
     * Dane wymagają przetworzenia na zakres od -10 do 40
     */
    int returnTemp();

    /*!
     * \brief returnPres
     * Zwraca aktualna wartość Ciśnienia
     * \return Zwraca odczytaną wartość ciśnienia w zakresie od do 1100 hPa,
     * są to dane przetworzone gotowe do wizualizacji
     *
     */
    int returnPres();

    /*!
     * \brief Zwraca intensywnośc opadów deszczu
     * Zwraca aktualną wartość opadów
     * \return Zwraca wartość pomiaru w zakresie od 0 do 100 wyrażoną w procentach
     * Dane są gotowe do wizualizacji
     */
    int returnRain();

    /*!
     * \brief Zwraca intensywnośc światła
     * Zwraca aktualną intensywności światła
     * \return Zwraca wartość pomiaru w zakresie od 0 do 100 wyrażoną w procentach
     * Dane są gotowe do wizualizacji
     */
    int returnLight();

    /*!
      * \brief Parsuje ramkę danych
      * Parsuję ramkę danych i sprawdza ich poprawność, a następnie
      * przypisuje wartości do zmiennych
      * \param[in] Ramka danych z bitem początkowym i sumą kontrolną
      * Ramka powinna zawierać Bit początkowy A, 4, oraz sumę kontrolną
      */
    void ParseData(string Data);

    /*!
      * \brief Wyświetla zawartość obiektu klasy DataFrame
      *    wypisuje ramke danych uzywajac funkcji qDebug()
      */
    void display_DataFrame();


};


#endif// DATAFRAME_H


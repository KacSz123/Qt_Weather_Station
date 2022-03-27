#ifndef CONNECT_WINDOW_H
#define CONNECT_WINDOW_H

/*!
 * \file
 * \brief Definicja klasy Diagrams
 *
 * Plik zawiera definicję klasy Diagram,
 * ktora definiuje obiekt reprezentujący okno z wykresami
 */
#include <QDialog>
#include <QMainWindow>
#include <QSerialPort>
#include "dataframe.h"
#include "digitalclock.h"

//#include "mainwindow.h"

/*!
 *  \brief Klasa Connect_window
 *   Klasa i jej metody obslugujaca polaczenie z portem szeregowym
 *   Pozwala komunikować się z wybranym urządzeniem przez port szeregowy
 */
namespace Ui {
class Connect_window;
}

class Connect_window : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Connect_window
     *  Konstruktor bezparametryczny, tworzy nowe instancje klasy Connect_window
     * \param[in] wskaznik na rodzica
     *
     */
    explicit Connect_window(QWidget *parent = nullptr);

    /**
      * @brief ~Connect_window();
      * Dekontruktor klasy Connect_window
      */
    ~Connect_window();


signals:
    /*!
     * \brief Sygnał wysylający ramkę danych do innych obiektów
     * Sygnał wysyła dane otrzymane przez połączenie z Arduino poprzez port szeregowy
     * \param[in] Wskaźnik na obiekt klasy DataFrame
     * Sygnal wysylajacy obiekt klasy DataFrame
     */
    void sendMsg(DataFrame *D);

    /*!
     * \brief Wysyła wiadomości z konretnymi wartościami z ramki danych
     * Sygnał odpowiada za wysłanie informacji wyciagniętych z ramki danych
     * \param[in] Zmienna odpowiadajaca wartosci temperatury
     * \param[in] Zmienna odpowiadajaca wartosci cisnienia
     * \param[in] Zmienna odpowiadajaca wartosci sily deszczu
     * \param[in] Zmienna odpowiadajaca int. swiatla
     */
    void sendMsg(int Temp, int Press, int Rain, int Light);

public slots:
    /*!
     * \brief Slot emitujacy sygnal sendMsg(DataFrame)
     *
     */
    void sendData()
    {
        emit  sendMsg(DF);
    }

    /*!
     * \brief slot emitujacy sygnał
     * Wysyła sygnał z Danymi z sensorów
     * Wysyła sendMsg(int, int, int, int)
     *
     */
    void sendDataToPlot()
    {
        emit sendMsg(DF->returnTemp(),DF->returnPres(),DF->returnRain(), DF->returnLight());
    }

    /*!
    * \brief Wyszukuje urządzenia dostępne przez interfes UART
    * Wyszukuj podłączone przez interfejs szeregowy urządzenia do komputera
    */
    void on_pushButtonSearch_clicked();

    /*!
              * \brief Wysyła wiadomośc do widgetu z logami
              *Pokazuje w oknie ConnectWindow godzine ostatniego wydarzenia (zapisu)
              *Pozwala rowniez wyswietlac wiadomosci z portu szeregowego
              * \param[in] Obiekt typu string, który wyświetlany jest w oknie z logami
              *
              */
    void addToLogs(QString msg);

    /*!
     * \brief Slot odpowiadający za obsługę przycisku połącz
     * Po wciśnięciu nawiązuje połączenie z urządzeniem zewnętrznym przez UART,
     * jeżeli zostało ono wykryte
     */
    void on_pushButtonConnect_clicked();

    /*!
    * \brief Slot odpowiadający za obsługę przycisku rozłącz
    * Po wciśnięciu zrywa połączenie z urządzeniem zewnętrznym przez UART,
    * jeżeli zostało jeżeli to połączenie zostało nawiązane
    */
    void on_pushButtonDisc_clicked();

    /*!
    * \brief Odbiera string z portu szeregowego
    * Sprawdza czy jakieś dane zostały wysłane na port szeregowy
    * Następnie je odpiera i zapisuje w obiecie DataFrame
    */
    void readFromPort();


    /*!
     * \brief Wysyła wiadomości przez UART
     * Wysyła dane typu string przez port szeregowy
     * funkjca typu void
     * \param[in] Wiadomość wysyłana przez UART
     * Przesyła łańcuch znaków przez interfejs UART
     */
    void sendMessageToDevice(QString message);

public:

    Ui::Connect_window *ui;
    QSerialPort *device;
    DataFrame *DF;
};

#endif // CONNECT_WINDOW_H

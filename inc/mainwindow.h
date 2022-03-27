#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QSerialPort>
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include "diagrams.h"
#include "digitalclock.h"
#include "connect_window.h"
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/*!
 * \brief MainWindow::MainWindow
 * \param parent
 *Klasa reprezentujaca glowne okno
 */
class MainWindow :  public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
    /*!
     * \brief Temp
     * Przeslana wartosc temperatury z portu w zakresie -100 do 400
     * \brief Press
     * Przeslana wartosc cisnienia z portu,
     * przyjmuje wartości w zakresie od 0 do 1100 hPa
     * \brief Rain
     * Przeslana wartosc intensywnosci deszczu z portu,
     * wyrazona w '%' w zakresie od 0 do 100
     * \brief Light
     *  Przeslana wartosc nat. swiatla z portu, ,
     * wyrazona w '%' w zakresie od 0 do 100
     */
    double Temp=0, Press=0, Rain=0, Light=0;
    /*!
     * \brief pm
     * wskaźnik na obiekt Pixelmap
     */
    /*!
     * \brief pm_bar
     * wskaźnik na obiekt Pixelmap
     */
    QPixmap *pm, *pm_bar;
    /*!
     * \brief painter
     * wskaźnik na obiekt typu QPainter
     * \brief painter2
     * wskaźnik na obiekt typu QPainter
     */
    QPainter *painter, *painter2;
protected:
    void closeEvent(QCloseEvent* e) override;
private slots:
    /*!
     * \brief Odbiera wiadomosc od obiektu klasy Connect_window
     * Slot odpowiadający za odbieranie danych wysyłanych przez sygnał,
     * odbiera dane, przekazuje do odpowiednich zmiennch Klasy mainWindow, oraz
     * odpowiada za wyświetlanie ich wartosci w głownym oknie
     * \param[in] D - wskaznik na obiekt tupy DataFrame,
     * z którego odczytywane są wartości wykrozystywane do wizualizacji danych
     *
     */
    void receiveMsg(DataFrame *D);

    /*!
     * \brief Odbiera dane przesylane z portu szeregowego
     * \param[in] Wartosc przeslanych danych wartosci temperatury,
     *  przesylane sa dane nie przekonwertowane w zakresie od -100 do 400
     * \param[in] Wartosc przeslanych danych wartosci cisnienia,
     * przesylane dane są odpowiednio sformatowane w zakresie 0 - 1100
     * \param[in] Wartosc przeslanych danych mocy opadow,
     * przesylane dane są odpowiednio sformatowane w zakresie 0 - 100
     * \param[in] Wartosc przeslanych danych int. swiatla,
     * przesylane dane są odpowiednio sformatowane w zakresie 0 - 100
     */
    void receiveMsg(int Temp1, int Press1, int Rain1, int Light1);







    //virtual void paintEvent(QPaintEvent *event);

    void on_actionPo_cz_triggered();

    void on_actionWykresy_triggered();

    void on_actionWyjd_triggered();

private:

    Ui::MainWindow *ui;
    Connect_window *nw;
    Diagrams *Dg;
};
#endif // MAINWINDOW_H

#ifndef MAINQW_H
#define MAINQW_H

/*!
 * \file
 * \brief Definicja klasy MainQW
 *
 * Plik zawiera definicję klasy MainQW,
 * jest to klasa pochodna do klasy QWidget
 *
 */
#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QSpinBox>
#include <QPainter>
#include <QLabel>
/*!
 * \brief The MainQW class
 * Klas przedstawiająca główny widget wizualizacyjny
 * modeluje obiekt klasy MainQW
 */
class MainQW : public QWidget
{
    Q_OBJECT
    QTimer *wTimer=nullptr;

    /*!
     * \brief tlo
     * Zmienna przechowująca obraz tła
     */
    QImage *tlo=new QImage(":/new/prefix1/img/main.png");
    /*!
     * \brief drop
     * Zmienna przechowująca obraz kropli deszczu
     */
    QImage  *drop=new QImage(":/new/prefix1/img/drop.png");;
    /*!
     * \brief ray
     *
     * Zmienna przechowująca obraz promienia słońca
     */
    QImage *ray=new QImage(":/new/prefix1/img/ray.png");;


    /*!
     * \brief drop_y współrzędna y pierwszego rzędu  kropli
     * przyjmuje wartość od 0 do wysokości obrazu tła
     */
    int drop_y=50;
    /*!
     * \brief drop_y2 współrzędna y drugiego rzędu kropli
     * przyjmuje wartość od 0 do wysokości obrazu tła
     */
    int drop_y2=drop_y-150;

    /*!
     * \brief drop_y3 współrzędna y trzeciego rzędu kropli
     * przyjmuje wartość od 0 do wysokości obrazu tła
     */
    int drop_y3=drop_y2-150;

    /*!
     * \brief drop_x współrzędna x obrazka kropli
     * przyjmuje wartość od zera do szerokości obrazu tła
     */
    int drop_x=300;

    /*!
     * \brief ray_x współrzędna x obrazka promienia słońca
     * przyjmuje wartość od 0 do do szerokości obrazu tła
     */
    int ray_x=380;

    /*!
     * \brief ray_y współrzędna y obrazka promienia słońca
     * przyjmuje wartość od 0 do wysokości obrazu tła
     */
    int ray_y=130;

    /*!
     * \brief Light_lvl
     * Zmienna przedstawiajaca poziom wizualizacji światła.
     * Przyjmuje wartość od 0 do 3
     */
    int Light_lvl=0;

    /*!
     * \brief Rain_lvl
     * Zmienna przedstawiajaca poziom wizualizacji deszczu.
     * Przyjmuje wartość od 0 do 3
     */
    int Rain_lvl=0;

    /*!
     * \brief iter
     * iterator wykorzystywany przy animacji promieni słońca
     * przyjmuje wartość od 0 do 20
     */
    int iter=0;
public:
    /*!
      * \brief MainQW
      * \param[in] parent
      */
    MainQW(QWidget *parent = nullptr);

    /*!
      * \brief paintEvent
      * Fukncja odpowiadająca za wyrysowanie glownego widgetu
      * Funkjca ta odpowiada za wyświetlanie animacji głównej wizualizacji
      * intensywności opadów i promieni słońca
      * \param[in] event Wskaźnik na zdarzenie
      */
    void paintEvent(QPaintEvent *event);

    /*!
      * \brief drawDrops
      * Funkcja rozpoczyna działanie licznika odpowiedzialnego
      * za animacje w widgecie
      */
    void drawDrops(){wTimer->start(50);};



    /*!
      * \brief setLightLvl
      * Funkcja ustawia odpowiedni poziom intensywności słońca od 0 do 3
      * na podstawie tej wartości wyświetlana jest odpowiednia animacja, odpowiadające
      * przedziały to: 0-25, 25-50, 50-75, 75-100
      * \param[in] l
      * Przyjmuje wartość intensywności światła odebraną ze stacji pogodowej (0-100) wyrażoną w procentach
      */
    void setLightLvl(int l);
    /*!
      * \brief setRainLvl
      * Funkcja ustawia odpowiedni poziom intensywności deszczu od 0 do 3
      * na podstawie tej wartości wyświetlana jest odpowiednia animacja, odpowiadające
      * przedziały to: 0-25, 25-50, 50-75, 75-100
      * \param[in] R
      * Przyjmuje wartość intensywności opadów odebraną ze stacji pogodowej (0-100) wyrażoną w procentach
      */
    void setRainLvl(int R);
    /*!
      * \brief AnimateSun
      * Funkcja na podstawie aktualnej wartosci Light_lvl
      * wyświetla odpowiednią liczbę kropli deszczu
      * \param[in] paint
      * Wskaźnik na obiekt klasy QPainter
      */
    void AnimateSun(QPainter *paint);
    /*!
      * \brief AnimateRain
      * Funkcja na podstawie aktualnej wartosci Rain_lvl
      * wyświetla odpowiednią liczbę kropli deszczu i animację opadów
      * \param paint
      * Wskaźnik na obiekt klasy QPainter
      */
    void AnimateRain(QPainter *paint);
public slots:

    /*!
      * \brief on_Timer_timeout
      * Slot odbierający sygnał od timera i realizujący animację
      * kropli deszczu i promieni słońca, inkrementowane są odpowiednie współrzędne
      * dla których rysowane są obiekty QImage.
      *
      */
    void on_Timer_timeout();

signals:

};

#endif // MAINQW_H

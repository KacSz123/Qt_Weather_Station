#ifndef CRC8_H
#define CRC8_H
#include <iostream>
#include <cstring>
#include <string>
#include <cassert>
#include <iomanip>
#include <bitset>
//typedef unsigned char byte;
#define POLYNOMIAL_9 0x07
using namespace std;


/*!
 * \brief CRC8_SingleByte
 * \param Data2 - typ int
 * \return
 * oblicza dzielenie przez wielomian dla byte'u
 */
unsigned int CRC8_SingleByte( unsigned int Data2 );



/*!
 * \brief CRC8_DataArray
 * \param pDataFrame - wskaznik na ramke danych
 * \param Len - dlugosc ramki danych
 * \return
 * Oblicza crc8 dla podanej ramki danych
 */
unsigned char CRC8_DataArray( const unsigned char *pDataFrame, unsigned char Len );


inline
unsigned char CRC8_DataArray( const char *pDataFrame, unsigned char Len )
{
  return CRC8_DataArray(reinterpret_cast<const unsigned char*>(pDataFrame),Len);
}

/*!
 * \brief ParseDataFrame
 * \param pDataFrame - wskaznik na ciag znakow przekazanej ramki danych
 * \param Temp - referencja do zmiennej typu int gdzie zapisywane sa dane,
 * \param Press - referencja do zmiennej typu int gdzie zapisywane sa dane
 * \param Rain - referencja do zmiennej typu int gdzie zapisywane sa dane
 * \param Light - referencja do zmiennej typu int gdzie zapisywane sa dane
 * \return bool
 * Przetwarza podaną ramkę danych i wydobywa z niej przeslane dane i przypisuje je do referencji
 */
bool ParseDataFrame( const char *pDataFrame, int &Temp, int &Press, int &Rain , int &Light );

inline
bool ParseDataFrame( const std::string &rDataFrame, int &Temp, int &Press, int &Rain, int &Light )
{
  return ParseDataFrame(rDataFrame.c_str(),Temp,Press, Rain, Light);
}


/*!
 * \brief CreateDataFrame
 * \param Temp - przekazane wartosci danych
 * \param Press - przekazane wartosci danych
 * \param Rain - przekazane wartosci danych
 * \param Light - przekazane wartosci danych
 * \return string
 * Tworzy ramkę danych z podanych wartosci typu integer, dodajac na poczatek
 * bit startowy i konczac suma kontrolna crc8
 */
std::string CreateDataFrame( int Temp, int Press, int Rain, int Light );

#endif // CRC8_H

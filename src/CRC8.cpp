#include "CRC8.h"


unsigned int CRC8_SingleByte( unsigned int Data2 )
{
    unsigned int Poly = ( POLYNOMIAL_9 << 7 );
    for ( unsigned char Idx = 0; Idx < 8; ++Idx ) {
        if (( Data2 & 0x8000 ) != 0 ) Data2 ^= Poly;
        Data2 <<= 1;
    }
    return Data2;
}




unsigned char CRC8_DataArray( const unsigned char *pDataFrame, unsigned char Len )
{
    // cout << " Obliczanie dla ramki (" << static_cast<int>(Len) << "): " << pDataFrame << endl;
    unsigned int Data2 = pDataFrame[0] << 8;

    for ( unsigned int Idx = 1; Idx < Len; ++Idx ) {
        Data2 |= pDataFrame[Idx];
        Data2 = CRC8_SingleByte(Data2);
    }
    Data2 = CRC8_SingleByte( Data2 );
    return static_cast<unsigned char>(Data2 >>8);
}






bool ParseDataFrame( const char *pDataFrame, int &Temp, int &Press, int &Rain , int &Light )
{
    std::istringstream IStrm(pDataFrame);
    char  FHeader;
    unsigned int CRC8;

    IStrm >> FHeader >> Temp >> Press >>  Rain >> Light >> hex >> CRC8;
    if (IStrm.fail() || FHeader != 'A' ) return false;
    return static_cast<unsigned char>(CRC8) == CRC8_DataArray(pDataFrame,strlen(pDataFrame)-3);
}





std::string CreateDataFrame( int Temp, int Press, int Rain, int Light )
{
    std::ostringstream  OStrm;

    OStrm << "A " << Temp << " " << Press<< " " << Rain << " " << Light;
    unsigned char CRC8 = CRC8_DataArray(OStrm.str().c_str(),OStrm.str().length());
    OStrm << " " << hex << uppercase << setw(2) << static_cast<int>(CRC8);
    return OStrm.str();
}

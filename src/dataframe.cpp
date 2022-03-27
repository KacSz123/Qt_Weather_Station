#include "dataframe.h"

DataFrame :: DataFrame()
{
    Temp=0;
    Pressure=0;
    Rain=0;
    LightIntensity=0;
    Read=false;

};
DataFrame :: DataFrame(string Data)
{
    std::istringstream IStrm(Data);
    char a;
    IStrm>>a;
    if((a)=='A')
    IStrm>>Temp>>Pressure>>Rain>>LightIntensity;
}


int DataFrame :: returnTemp()
{
    return Temp;
}
int DataFrame :: returnPres()
{
    return Pressure;
}
int DataFrame ::  returnRain()
{
    return Rain;
}
int DataFrame :: returnLight()
{
    return LightIntensity;
}


void DataFrame ::  ParseData(string Data)
{
    Read=ParseDataFrame(Data,Temp,Pressure, Rain, LightIntensity);
  // qDebug() << Read;
}


void DataFrame :: display_DataFrame()
{
    qDebug()<<"A "<<Temp<<" "<<Pressure<<" "<<Rain<<" "<<LightIntensity;
}



DataFrame ::  ~DataFrame()
{

}



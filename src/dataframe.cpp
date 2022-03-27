#include "dataframe.h"

DataFrame :: DataFrame()
{
    Temp=0;
    Pressure=0;
    Rain=0;
    LightIntensity=0;

};
DataFrame :: DataFrame(string Data)
{

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
    ParseDataFrame(Data,Temp,Pressure, Rain, LightIntensity);
}


void DataFrame :: display_DataFrame()
{
    qDebug()<<"A "<<Temp<<" "<<Pressure<<" "<<Rain<<" "<<LightIntensity;
}



DataFrame ::  ~DataFrame()
{

}



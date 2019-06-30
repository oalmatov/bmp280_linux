/* bmp280runner.cpp
****************************************************************************************************************
****************************************************************************************************************
*/

#include "bmp280.h"

using namespace std;

int main()
{
    Bmp280      bmp280( "/dev/i2c-1" , 0x77 );

    bmp280.read();
    cout << "temperature in C: " << dec << bmp280.temperature() << endl;
    cout << "pressure: " << dec << bmp280.pressure() << " hPa" << endl;
}

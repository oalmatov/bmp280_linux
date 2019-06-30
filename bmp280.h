/* bmp280.h
****************************************************************************************************************
****************************************************************************************************************
    Copyright (C) 2019 Omar Almatov
     
    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General
    Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.
    
    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
    License for more details.
    
    You should have received a copy of the GNU General Public License along with this program. If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef BMP280_H_
#define BMP280_H_ 1

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

class Bmp280
{

public:
            
                            Bmp280( const char* busFile, uint8_t i2cAddress );

    void                    read();
    double                  temperature() const;
    double                  pressure() const;

protected:

    struct Raw_
    {
        uint16_t            t1;
        int16_t             t2;
        int16_t             t3;
        uint16_t            p1;
        int16_t             p2;
        int16_t             p3;
        int16_t             p4;          
        int16_t             p5;
        int16_t             p6;          
        int16_t             p7;
        int16_t             p8;
        int16_t             p9;
    };

    int                     fd_;
    Raw_                    raw_;
    unsigned                adcTemp_;
    unsigned                adcPres_;
};

#endif // BMP280_H_

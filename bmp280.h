// bmp280.h

#ifndef BMP280_H
#define BMP280_H 1

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

#endif // BMP280_H

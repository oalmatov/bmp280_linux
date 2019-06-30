#include "bmp280.h"

Bmp280::Bmp280( const char* busFile, uint8_t i2cAddress )
{
    fd_ = open( busFile, O_RDWR );
    
    ioctl( fd_, I2C_SLAVE, i2cAddress );
    usleep( 1000 );
}

void
Bmp280::read()
{
    i2c_smbus_read_i2c_block_data( fd_, 0x88, sizeof(raw_), reinterpret_cast<uint8_t*>(&raw_) );     
    i2c_smbus_write_byte_data( fd_, 0xF4, 0x27 );
    usleep( 1000 );
    i2c_smbus_write_byte_data( fd_, 0xF5, 0xA0 );
    usleep( 1000 );

    uint8_t     data[ 8 ];

    i2c_smbus_read_i2c_block_data( fd_, 0xF7, sizeof(data), data );
    adcPres_ = ((static_cast<unsigned>(data[0]) << 16) + (static_cast<unsigned>(data[1]) << 8) + (data[2] & 0xF0)) >> 4;
    adcTemp_ = ((static_cast<unsigned>(data[3]) << 16) + (static_cast<unsigned>(data[4]) << 8) + (data[5] & 0xF0)) >> 4;
}

double
Bmp280::temperature() const
{
    double      var1( (adcTemp_/16384.0L - raw_.t1/1024.0L) * raw_.t2 );
    double      var2( ((adcTemp_/131072.0L - raw_.t1/8192.0L) * (adcTemp_/131072.0L - raw_.t1/8192.0L)) * raw_.t3 );

    return (var1 + var2) / 5120.0L;
}

double
Bmp280::pressure() const
{
    double      var1( (adcTemp_/16384.0L - raw_.t1/1024.0L) * raw_.t2 );
    double      var2( ((adcTemp_/131072.0L - raw_.t1/8192.0L) * (adcTemp_/131072.0L - raw_.t1/8192.0L)) * raw_.t3 );

    var1 = ((var1 + var2) / 2.0L) - 64000.0L;
    var2 = var1 * var1 * raw_.p6 / 32768.0L;
    var2 = var2 + var1 * raw_.p5 * 2.0L;
    var2 = (var2 / 4.0L) + raw_.p4 * 65536.0L;
    var1 = (raw_.p3 * var1 * var1 / 524288.0L +  raw_.p2 * var1) / 524288.0L;
    var1 = (1.0L + var1 / 32768.0L) * raw_.p1;

    double      p( 1048576.0L - adcPres_ );

    p = (p - (var2 / 4096.0)) * 6250.0 / var1;
    var1 = raw_.p9 * p * p / 2147483648.0L;
    var2 = p * raw_.p8 / 32768.0L;

    return (p + (var1 + var2 + raw_.p7) / 16.0L) / 100.0L;
}

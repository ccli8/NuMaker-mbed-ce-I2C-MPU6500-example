#include "mbed.h"
#include "mpu6500.h"

I2C  mpu6500_i2c(PC_9, PA_15); // I2C0_SDA, I2C0_SCL

void MPU6500_WriteByte(uint8_t MPU6500_reg, uint8_t MPU6500_data)
{
    char data_out[2];
    data_out[0]=MPU6500_reg;
    data_out[1]=MPU6500_data;
    mpu6500_i2c.write(MPU6500_slave_addr, data_out, 2, 0);
}

uint8_t MPU6500_ReadByte(uint8_t MPU6500_reg)
{
    char data_out[1], data_in[1];
    data_out[0] = MPU6500_reg;
    mpu6500_i2c.write(MPU6500_slave_addr, data_out, 1, 1);
    mpu6500_i2c.read(MPU6500_slave_addr, data_in, 1, 0);
    return (data_in[0]);
}

void MPU6500::initialize()
{
    MPU6500_WriteByte(MPU6500_PWR_MGMT_1, 0x00);    // CLK_SEL=0: internal 8MHz, TEMP_DIS=0, SLEEP=0 
    MPU6500_WriteByte(MPU6500_SMPLRT_DIV, 0x07);  // Gyro output sample rate = Gyro Output Rate/(1+SMPLRT_DIV)
    MPU6500_WriteByte(MPU6500_CONFIG, 0x06);      // set TEMP_OUT_L, DLPF=2 (Fs=1KHz)
    MPU6500_WriteByte(MPU6500_GYRO_CONFIG, 0x18); // bit[4:3] 0=+-250d/s,1=+-500d/s,2=+-1000d/s,3=+-2000d/s
    MPU6500_WriteByte(MPU6500_ACCEL_CONFIG, 0x01);// bit[4:3] 0=+-2g,1=+-4g,2=+-8g,3=+-16g, ACC_HPF=On (5Hz)
}

int16_t MPU6500::getAccelXvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = MPU6500_ReadByte(MPU6500_ACCEL_XOUT_L); // read Accelerometer X_Low  value
    HiByte = MPU6500_ReadByte(MPU6500_ACCEL_XOUT_H); // read Accelerometer X_High value
    return((HiByte<<8) | LoByte);
}

int16_t MPU6500::getAccelYvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = MPU6500_ReadByte(MPU6500_ACCEL_YOUT_L); // read Accelerometer X_Low  value
    HiByte = MPU6500_ReadByte(MPU6500_ACCEL_YOUT_H); // read Accelerometer X_High value
    return ((HiByte<<8) | LoByte);
}

int16_t MPU6500::getAccelZvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = MPU6500_ReadByte(MPU6500_ACCEL_ZOUT_L); // read Accelerometer X_Low  value
    HiByte = MPU6500_ReadByte(MPU6500_ACCEL_ZOUT_H); // read Accelerometer X_High value
    return ((HiByte<<8) | LoByte);
}

int16_t MPU6500::getGyroXvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = MPU6500_ReadByte(MPU6500_GYRO_XOUT_L); // read Accelerometer X_Low  value
    HiByte = MPU6500_ReadByte(MPU6500_GYRO_XOUT_H); // read Accelerometer X_High value
    return ((HiByte<<8) | LoByte);
}

int16_t MPU6500::getGyroYvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = MPU6500_ReadByte(MPU6500_GYRO_YOUT_L); // read Accelerometer X_Low  value
    HiByte = MPU6500_ReadByte(MPU6500_GYRO_YOUT_H); // read Accelerometer X_High value
    return ((HiByte<<8) | LoByte);
}

int16_t MPU6500::getGyroZvalue()
{
    uint8_t LoByte, HiByte;
    LoByte = MPU6500_ReadByte(MPU6500_GYRO_ZOUT_L); // read Accelerometer X_Low  value
    HiByte = MPU6500_ReadByte(MPU6500_GYRO_ZOUT_H); // read Accelerometer X_High value
    return ((HiByte<<8) | LoByte);
}

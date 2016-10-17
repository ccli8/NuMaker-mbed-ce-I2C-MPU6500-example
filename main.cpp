// NuMaker-PFM-NUC472 : I2C0 reading IMU (3-axis accelerometer & 3-axis gyroscope)
#include "mbed.h"
#include "mpu6500.h"

I2C i2c0(PC_9, PA_15); // I2C0_SDA, I2C0_SCL

MPU6500 IMU; // IMU use on-board MPU6500

int main() {
    int16_t accX,  accY,  accZ;
    int16_t gyroX, gyroY, gyroZ;

    i2c0.frequency(400000);    
    IMU.initialize();
    
    while(true) {
       accX = IMU.getAccelXvalue();
       accY = IMU.getAccelYvalue();
       accZ = IMU.getAccelZvalue();
       gyroX= IMU.getGyroXvalue();
       gyroY= IMU.getGyroYvalue();
       gyroZ= IMU.getGyroZvalue();
       printf("Acc: %6d, %6d, %6d, ",   accX, accY, accZ);
       printf("Gyro:%6d, %6d, %6d\n\r", gyroX, gyroY, gyroZ);       
    }
}

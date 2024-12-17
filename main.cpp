#include "mbed.h"
#include "mpu6500.h"

/* Calculate tilt angle */
#define CALCULATE_TILT_ANGLE    1

#if CALCULATE_TILT_ANGLE
#include "math.h"
#define PI 3.14159265359
#endif

using namespace mbed_nuvoton;

#if TARGET_NUMAKER_PFM_NUC472
MPU6500 IMU(PC_9, PA_15, MPU6500_slave_addr, 400000);
#elif TARGET_NUMAKER_IOT_M467
MPU6500 IMU(PD_0, PD_1, MPU6500_slave_addr, 400000);
#else
MPU6500 IMU(I2C_SDA, I2C_SCL, MPU6500_slave_addr, 400000);
#endif

int main() {
    int16_t accX,  accY,  accZ;
    int16_t gyroX, gyroY, gyroZ;
#if CALCULATE_TILT_ANGLE
    float X2, Y2, Z2;
    float theta, psi, phi;
#endif

    IMU.initialize();

    while(true) {
        /* I2C reading IMU (3-axis accelerometer & 3-axis gyroscope) */
        accX = IMU.getAccelXvalue();
        accY = IMU.getAccelYvalue();
        accZ = IMU.getAccelZvalue();
        gyroX= IMU.getGyroXvalue();
        gyroY= IMU.getGyroYvalue();
        gyroZ= IMU.getGyroZvalue();
        printf("Acc: %6d, %6d, %6d, ",   accX, accY, accZ);
        printf("Gyro:%6d, %6d, %6d\n\r", gyroX, gyroY, gyroZ); 

#if CALCULATE_TILT_ANGLE
        /* degree = radians * 180 / PI */
       X2 = pow(accX,2.0);
       Y2 = pow(accY, 2.0);
       Z2 = pow(accZ,2.0);
       theta = atan(accX / sqrt(Y2 + Z2)) * 180 / PI;
       psi   = atan(accY / sqrt(Z2 + X2)) * 180 / PI;
       phi   = atan(sqrt(X2 + Y2) / accZ) * 180 / PI;
       printf("theta=%d, psi=%d, phi=%d\n\r", (int) theta, (int) psi, (int) phi);         
#endif

        ThisThread::sleep_for(1s);
    }
}

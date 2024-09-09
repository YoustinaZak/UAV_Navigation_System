# STM32 MPU6050 Sensor Project

This project demonstrates the integration of the STM32 microcontroller with the MPU6050 sensor. The MPU6050 sensor is used to read the accelerometer, gyroscope, and temperature data. This data is processed to calculate pitch, roll, and yaw angles. Additionally, the project employs **dependency injection** to allow flexible, portable, platform agnostic code.

## Components Used
- **STM32 Microcontroller**
  - Used to interface with the MPU6050 sensor, process data, and perform calculations for pitch, roll, and yaw.

- **MPU6050 Sensor**
  - A 6-axis sensor with a built-in accelerometer and gyroscope, capable of measuring linear acceleration, angular velocity, and temperature.

- **2x16 LCD Display**
  - A simple character-based display used to show pitch, roll, yaw, and temperature values in real-time.
    
## Features
- **Accelerometer**: Measures the linear acceleration in X, Y, and Z axes.
- **Gyroscope**: Measures the angular velocity (rotation) along the X, Y, and Z axes.
- **Temperature Sensor**: Reads the temperature from the MPU6050 sensor.
- **Pitch, Roll, and Yaw Calculation**: 
  - **Pitch**: Rotation about the X-axis.
  - **Roll**: Rotation about the Y-axis.
  - **Yaw**: Rotation about the Z-axis.
- **2x16 LCD Display**: Displays the pitch, roll, yaw, and temperature values.
- **Dependency Injection**: Used to decouple the sensor logic from the hardware-specific implementation, providing flexibility for different hardware configurations.

## How It Works
1. **MPU6050 Initialization**: 
   - The sensor is initialized over I2C (Inter-Integrated Circuit) protocol, configuring it to output data from the accelerometer, gyroscope, and temperature sensor.
  
2. **Hardware Abstraction and Dependency Injection**:
   - The project uses **dependency injection** for the hardware abstraction layer (HAL). This allows you to inject different hardware interfaces.
   - The hardware-specific implementations (e.g., I2C read/write functions) are abstracted in the **HW_Interface_MPU.c / HW_Interface_MPU.h**, which is injected into the MPU6050 sensor code at runtime.

3. **Data Acquisition**:
   - The STM32 microcontroller reads the raw data from the MPU6050 sensor for the accelerometer, gyroscope, and temperature.

4. **Data Processing**:
   - The accelerometer data is used to determine the inclination of the sensor (pitch and roll).
   - The gyroscope data provides angular velocity, which is used in the yaw calculation.

5. **Pitch, Roll, and Yaw Calculation**:
   - **Pitch**: Calculated from accelerometer data along the Y and Z axes.
   - **Roll**: Calculated from accelerometer data along the X and Z axes.
   - **Yaw**: Integrated from gyroscope data along the Z-axis.

6. **Temperature Measurement**:
   - The temperature sensor data is read and converted to Celsius from the raw output of the MPU6050.

## Prerequisites
- STM32 development environment (e.g., STM32CubeIDE )
- Basic understanding of C programming and embedded systems
- Familiarity with **Dependency Injection** and hardware abstraction techniques

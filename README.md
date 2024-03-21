# ArduinoBleFFT
Calculate the fft and normalized energy of IMU sensor outputs

This code is tested in Arduino Nano 33 BLE module with Microcontroller	nRF52840 where 32-bit ARM® Cortex®-M4 CPU running at 64 MHz.
IMU sensor used in this example is LSM9DS1 module on the Arduino Nano 33 BLE
We read the acceletometer outputs with 100Hz sampling frequency and window size of 100.
Note that, accelerometer output data rate is fixed at 104 Hz. (https://docs.arduino.cc/tutorials/nano-33-ble/imu-accelerometer/)
For DSP operations CMSIS DSP Software Library is used (https://www.keil.com/pack/doc/CMSIS/DSP/html/index.html)
Results are taken via serial port and read by Matlab script and plotted. 

If Test Option is given 1, then a sinosoidal signal from a LUT given to DSP operations to compare the results with other scripts from Python or Matlab. 

You can find serial port reader and plotter script in scripts folder. 
FFT and normalized energy calculation is under lib/MathUtilities
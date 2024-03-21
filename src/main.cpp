#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include "MathUtilities.hpp"

#define SAMPLE_RATE     100     // Sampling rate in Hz
#define ORIGINAL_SIZE   100     // Original size of the sample
#define PADDED_SIZE     128     // Size of the padded sample
#define TEST            1


int newTime;

float32_t mysineLUT[] = {
    0.0000, 0.3090, 0.5878, 0.8090, 0.9511, 1.0000, 0.9511, 0.8090, 0.5878, 0.3090, 0.0000, -0.3090,
    -0.5878, -0.8090, -0.9511, -1.0000, -0.9511, -0.8090, -0.5878, -0.3090, -0.0000, 0.3090, 0.5878, 0.8090,
    0.9511, 1.0000, 0.9511, 0.8090, 0.5878, 0.3090, 0.0000, -0.3090, -0.5878, -0.8090, -0.9511, -1.0000,
    -0.9511, -0.8090, -0.5878, -0.3090, -0.0000, 0.3090, 0.5878, 0.8090, 0.9511, 1.0000, 0.9511, 0.8090,
    0.5878, 0.3090, 0.0000, -0.3090, -0.5878, -0.8090, -0.9511, -1.0000, -0.9511, -0.8090, -0.5878, -0.3090,
    -0.0000, 0.3090, 0.5878, 0.8090, 0.9511, 1.0000, 0.9511, 0.8090, 0.5878, 0.3090, 0.0000, -0.3090,
    -0.5878, -0.8090, -0.9511, -1.0000, -0.9511, -0.8090, -0.5878, -0.3090, -0.0000, 0.3090, 0.5878, 0.8090,
    0.9511, 1.0000, 0.9511, 0.8090, 0.5878, 0.3090, -0.0000, -0.3090, -0.5878, -0.8090, -0.9511, -1.0000,
    -0.9511, -0.8090, -0.5878, -0.3090, -0.0000, 0.3090, 0.5878, 0.8090, 0.9511, 1.0000, 0.9511, 0.8090, 0.5878, 0.3090, -0.0000, -0.3090, -0.5878, -0.8090, -0.9511, -1.0000,
    -0.9511, -0.8090, -0.5878, -0.3090, -0.0000, 0.3090, 0.5878, 0.8090, 0.9511, 1.0000, 0.9511, 0.8090
};


void plotData(float32_t *data, int size);

void setup() {
    Serial.begin(9600);
  
   
    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }

    Serial.print("Accelerometer sample rate = ");
    Serial.print(IMU.accelerationSampleRate());
    Serial.println("Hz");
}

void loop() {
    newTime = micros();
    if (IMU.accelerationAvailable()) {
        float x, y, z;
        IMU.readAcceleration(x, y, z);

        // Compute FFT and calculate energy
        float32_t xData[ORIGINAL_SIZE]; // Original size of the sample
        for (int i = 0; i < ORIGINAL_SIZE; i++) {
            xData[i] = x; // Assuming x-axis for simplicity
            delay(1000 / SAMPLE_RATE); // Wait for next sample 100Hz -- normally 119hz is the samplingfreq of IMU
            IMU.readAcceleration(x, y, z); // Read next sample
        }

        // Zero-padding to increase the sample size from 100 to 128
        float32_t paddedData[PADDED_SIZE] = {0}; // Initialize with zeros
  
        Serial.println((double)55555);    // Send sync series for serial port reading, a random number

        if (TEST) {
            for (int i = 0; i < 128; i++) {
                paddedData[i] = mysineLUT[i];
            }
            plotData(paddedData, PADDED_SIZE);
        } else {
            for (int i = 0; i < ORIGINAL_SIZE; i++) {
                paddedData[i] = xData[i];
            }
            plotData(paddedData, ORIGINAL_SIZE);
        }

        float32_t fftOutput[PADDED_SIZE / 2]; // Output will be half the size due to symmetry
        float32_t energy = 0;
        mathCalc::calculateNormalizedShortTimeEnergy(paddedData, fftOutput, &energy);
  
        plotData(fftOutput, PADDED_SIZE / 2);
        Serial.println((double)energy, 5); // Separate plot for energy
    
        // Update LED brightness
        float elapsedTimePerSampleUs = (micros() - newTime);
        Serial.print("Time per sample (us): ");
        Serial.println(elapsedTimePerSampleUs);
    }
}

// Function to plot data
void plotData(float32_t *data, int size) {
    for (int i = 0; i < size; i++) {
        Serial.println(data[i]);
    }
}

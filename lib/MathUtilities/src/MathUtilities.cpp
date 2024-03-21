#include "MathUtilities.hpp"
#include <arm_math.h>
#include "arm_const_structs.h"

namespace mathCalc
{

// Function to compute FFT and calculate energy
float32_t calculateNormalizedShortTimeEnergy(float32_t *inputData, float32_t *fftOutput, float32_t *energy)
{
  float32_t rmsEnergy = 0;
  float32_t fftOutputComplex[PADDED_SIZE];
  arm_rfft_fast_instance_f32 fftInstance;
  arm_rfft_fast_init_f32(&fftInstance, PADDED_SIZE);
  
  // Take 128 points fft of the input signal  
  arm_rfft_fast_f32(&fftInstance, inputData, fftOutputComplex, 0);
  
  // Calculate magnitude of each FFT coefficient
  arm_cmplx_mag_f32(fftOutputComplex, fftOutput, PADDED_SIZE / 2);

  // Here we get sqrt of energy value  divided by (PADDED_SIZE)/2 already
  arm_rms_f32(fftOutput, PADDED_SIZE / 2, &rmsEnergy); 

  // Normalized energy calculation,  second division (PADDED_SIZE)
  //  We have sqrt of energy from rms operation, we need to take the square
  *energy = (rmsEnergy*rmsEnergy) /(PADDED_SIZE) ;
 
 
  
  
  return 0; 
}


}// namepsace mathCalc

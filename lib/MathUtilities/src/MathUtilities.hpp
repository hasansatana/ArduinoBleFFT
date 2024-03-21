#pragma once

#include <stdint.h>
#include <stdio.h>
#include "arm_const_structs.h"
#include <arm_math.h>

namespace mathCalc
{

constexpr uint32_t   ORIGINAL_SIZE = 100;  // Original size of the sample
constexpr uint32_t   PADDED_SIZE = 128; // Size of the padded sample
constexpr uint32_t   SAMPLE_RATE = 100; // Sampling rate in Hz

float32_t calculateNormalizedShortTimeEnergy(float32_t *inputData, float32_t *fftOutput, float32_t *energy);


} // namepsace mathCalc

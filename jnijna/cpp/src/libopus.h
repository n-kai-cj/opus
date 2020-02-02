#pragma once

#ifndef __LIBOPUS_H__
#define __LIBOPUS_H__

#ifdef _WIN32
#define LIBOPUS_API __declspec(dllexport)
#elif __linux__
#define LIBOPUS_API
#endif

#include <stdio.h>
#include <stdint.h>
#include "opus.h"

#define MAX_PACKET_SIZE 4000

#ifdef __cplusplus
extern "C"
{
#endif

    LIBOPUS_API uint64_t encoder_initialize(int sampleRateHz, int channel, int bitrate);
    LIBOPUS_API int encode(uint64_t enc, uint8_t *input, int inputOffset, int inputLength, uint8_t *output, int outputOffset, int outputLength);
    LIBOPUS_API void encoder_uninitialize(uint64_t enc);

    LIBOPUS_API uint64_t decoder_initialize(int sampleRateHz, int channel);
    LIBOPUS_API int decode(uint64_t dec, uint8_t *input, int inputOffset, int inputLength, uint8_t *output, int outputOffset, int outputLength);
    LIBOPUS_API void decoder_uninitialize(uint64_t dec);

#ifdef __cplusplus
}
#endif

#endif /* __LIBOPUS_H__ */

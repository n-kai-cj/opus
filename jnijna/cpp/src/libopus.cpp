
#include "libopus.h"


uint64_t encoder_initialize(int sampleRateHz, int channel, int bitrate)
{
    int error;
    OpusEncoder *enc = opus_encoder_create(sampleRateHz, channel, OPUS_APPLICATION_AUDIO, &error);
    if (OPUS_OK != error)
    {
        fprintf(stderr, "encoder initialize error %d\n", error);
        return error;
    }
    opus_encoder_ctl(enc, OPUS_SET_BITRATE(bitrate));
    opus_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
    opus_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_AUTO));
    opus_encoder_ctl(enc, OPUS_SET_APPLICATION(OPUS_APPLICATION_AUDIO));
    opus_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(0));

    return (uint64_t)(intptr_t)enc;
}

int encode(uint64_t enc, uint8_t *input, int inputOffset, int inputLength, uint8_t *output, int outputOffset, int outputLength)
{
    return opus_encode((OpusEncoder *)(intptr_t)enc,
                       (opus_int16 *)(input + inputOffset), inputLength,
                       (unsigned char *)(output + outputOffset), outputLength);
}

void encoder_uninitialize(uint64_t enc)
{
    opus_encoder_destroy((OpusEncoder *)(intptr_t)enc);
}

uint64_t decoder_initialize(int sampleRateHz, int channel)
{
    int error;
    OpusDecoder *dec = opus_decoder_create(sampleRateHz, channel, &error);
    if (OPUS_OK != error)
    {
        fprintf(stderr, "decoder initialize error %d\n", error);
        return error;
    }

    return (uint64_t)(intptr_t)dec;
}

int decode(uint64_t dec, uint8_t *input, int inputOffset, int inputLength, uint8_t *output, int outputOffset, int outputLength)
{
    return opus_decode((OpusDecoder *)(intptr_t)dec,
                       (unsigned char *)(input + inputOffset), inputLength,
                       (opus_int16 *)(output + outputOffset), outputLength, 0);
}

void decoder_uninitialize(uint64_t dec)
{
    opus_decoder_destroy((OpusDecoder *)(intptr_t)dec);
}



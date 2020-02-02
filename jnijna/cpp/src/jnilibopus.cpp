
#include "jnilibopus.h"

#ifdef __cplusplus
extern "C"
{
#endif

    std::vector<OpusEncoder *> encoder_list;
    std::vector<OpusDecoder *> decoder_list;
    std::mutex enc_mutex;
    std::mutex dec_mutex;

    JNIEXPORT jint JNICALL
    Java_com_test_JniOpus_encoder_1initialize(
        JNIEnv *env, jobject jobj,
        jint sampleRateHz, jint channel, jint bitrate)
    {
        enc_mutex.lock();

        int error;
        OpusEncoder *enc = opus_encoder_create(sampleRateHz, channel, OPUS_APPLICATION_AUDIO, &error);
        if (OPUS_OK != error)
        {
            fprintf(stderr, "encoder initialize error %d\n", error);
            enc_mutex.unlock();
            return error;
        }
        opus_encoder_ctl(enc, OPUS_SET_BITRATE(bitrate));
        opus_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
        opus_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_AUTO));
        opus_encoder_ctl(enc, OPUS_SET_APPLICATION(OPUS_APPLICATION_AUDIO));
        opus_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(0));
        encoder_list.push_back(enc);
        int ret = encoder_list.size() - 1;

        enc_mutex.unlock();

        return ret;
    }

    JNIEXPORT jint JNICALL
    Java_com_test_JniOpus_encode(
        JNIEnv *env, jobject jobj,
        jint enc, jbyteArray _input, jint inputOffset, jint inputLength,
        jbyteArray _output, jint outputOffset, jint outputLength)
    {
        if (enc >= encoder_list.size())
        {
            fprintf(stderr, "opus encode error. enc=%d, list.size=%d\n", enc, encoder_list.size());
            return -1;
        }

        enc_mutex.lock();

        jbyte *input = env->GetByteArrayElements(_input, NULL);
        jbyte *output = env->GetByteArrayElements(_output, NULL);
        OpusEncoder *encoder = encoder_list[enc];
        int ret = opus_encode(encoder,
                              (opus_int16 *)(input + inputOffset), inputLength,
                              (unsigned char *)(output + outputOffset), outputLength);
        env->ReleaseByteArrayElements(_input, input, 0);
        env->ReleaseByteArrayElements(_output, output, 0);

        enc_mutex.unlock();

        return ret;
    }

    JNIEXPORT void JNICALL
    Java_com_test_JniOpus_encoder_1uninitialize(
        JNIEnv *env, jobject jobj,
        jint enc)
    {
        if (enc >= encoder_list.size())
        {
            fprintf(stderr, "opus encoder uninitialize error. enc=%d, list.size=%d", enc, encoder_list.size());
            return;
        }

        enc_mutex.lock();

        OpusEncoder *encoder = encoder_list[enc];
        opus_encoder_destroy(encoder);

        enc_mutex.unlock();
    }

    JNIEXPORT jint JNICALL
    Java_com_test_JniOpus_decoder_1initialize(
        JNIEnv *env, jobject jobj,
        jint sampleRateHz, jint channel)
    {

        dec_mutex.lock();

        int error;
        OpusDecoder *dec = opus_decoder_create(sampleRateHz, channel, &error);
        if (OPUS_OK != error)
        {
            fprintf(stderr, "decoder initialize error %d\n", error);
            dec_mutex.unlock();
            return error;
        }
        decoder_list.push_back(dec);
        int ret = decoder_list.size() - 1;

        dec_mutex.unlock();

        return ret;
    }

    JNIEXPORT jint JNICALL
    Java_com_test_JniOpus_decode(
        JNIEnv *env, jobject jobj,
        jint dec, jbyteArray _input, jint inputOffset, jint inputLength,
        jbyteArray _output, jint outputOffset, jint outputLength)
    {
        if (dec >= decoder_list.max_size())
        {
            fprintf(stderr, "opus decode error. dec=%d, list.size=%d", dec, decoder_list.size());
            return -1;
        }

        dec_mutex.lock();

        jbyte *input = env->GetByteArrayElements(_input, NULL);
        jbyte *output = env->GetByteArrayElements(_output, NULL);
        OpusDecoder *decoder = decoder_list[dec];
        int ret = opus_decode(decoder,
                              (unsigned char *)(input + inputOffset), inputLength,
                              (opus_int16 *)(output + outputOffset), outputLength, 0);
        env->ReleaseByteArrayElements(_input, input, 0);
        env->ReleaseByteArrayElements(_output, output, 0);

        dec_mutex.unlock();

        return ret;
    }

    JNIEXPORT void JNICALL
    Java_com_test_JniOpus_decoder_1uninitialize(
        JNIEnv *env, jobject jobj,
        jint dec)
    {
        if (dec >= decoder_list.size())
        {
            fprintf(stderr, "opus decoder uninitialize error. dec=%d, list.size=%d", dec, decoder_list.size());
            return;
        }

        dec_mutex.lock();

        OpusDecoder *decoder = decoder_list[dec];
        opus_decoder_destroy(decoder);

        dec_mutex.unlock();
    }

#ifdef __cplusplus
}
#endif

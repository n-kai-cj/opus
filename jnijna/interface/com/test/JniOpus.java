package com.test;

public class JniOpus {

    public static final int[] OPUS_SUPPORTED_SAMPLE_RATES = {8000, 12000, 16000, 24000, 48000};
    public static final int[] OPUS_SUPPORTED_CHANNELS = {1, 2};
    public static final double[] OPUS_SUPPORTED_FRAME_SIZE_MS = {2.5, 5, 10, 20, 40, 60};
    public static final int MAX_PACKET_SIZE = 4000;

    public native int encoder_initialize(int sampleRateHz, int channel, int bitrate);
    public native int encode(int enc, byte[] input, int inputOffset, int inputLength, byte[] output, int outputOffset, int outputLength);
    public native void encoder_uninitialize(int enc);

    public native int decoder_initialize(int sampleRateHz, int channel);
    public native int decode(int dec, byte[] input, int inputOffset, int inputLength, byte[] output, int outputOffset, int outputLength);
    public native void decoder_uninitialize(int dec);

    public static byte getSampleRateIdx(int sampleRateHz) {
        for (int i = 0; i < OPUS_SUPPORTED_SAMPLE_RATES.length; i++) {
            if (sampleRateHz == OPUS_SUPPORTED_SAMPLE_RATES[i]) {
                return (byte) i;
            }
        }
        return -1;
    }

}



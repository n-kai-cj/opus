package com.test;

public interface LibOpusInterface extends com.sun.jna.Library {
    LibOpusInterface INSTANCE = com.sun.jna.Native.load("jnilibopus", LibOpusInterface.class);
    public static final int[] OPUS_SUPPORTED_SAMPLE_RATES = {8000, 12000, 16000, 24000, 48000};
    public static final int[] OPUS_SUPPORTED_CHANNELS = {1, 2};
    public static final double[] OPUS_SUPPORTED_FRAME_SIZE_MS = {2.5, 5, 10, 20, 40, 60};
    public static final int MAX_PACKET_SIZE = 4000;

    public int encoder_initialize(int sampleRateHz, int channel, int bitrate);
    public int encode(int enc, byte[] input, int inputOffset, int inputLength, byte[] output, int outputOffset, int outputLength);
    public void encoder_uninitialize(int enc);

    public int decoder_initialize(int sampleRateHz, int channel);
    public int decode(int dec, byte[] input, int inputOffset, int inputLength, byte[] output, int outputOffset, int outputLength);
    public void decoder_uninitialize(int dec);

}


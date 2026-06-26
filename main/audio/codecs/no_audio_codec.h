#pragma once
#include "audio_codec.h"
#include "driver/i2s_std.h"
#include "driver/i2s_pdm.h"
#include "driver/gpio.h"
#include <mutex>

class NoAudioCodec : public AudioCodec {
public:
    virtual ~NoAudioCodec();
    virtual int Write(const int16_t* data, int samples) override;
    virtual int Read(int16_t* dest, int samples) override;
    virtual void EnableInput(bool enable) override;
    virtual void EnableOutput(bool enable) override;

protected:
    bool duplex_ = false;
    int input_sample_rate_ = 16000;
    int output_sample_rate_ = 24000;
    i2s_chan_handle_t tx_handle_ = nullptr;
    i2s_chan_handle_t rx_handle_ = nullptr;
    std::mutex data_if_mutex_;
};

class NoAudioCodecDuplex : public NoAudioCodec {
public:
    NoAudioCodecDuplex(int input_sample_rate, int output_sample_rate, gpio_num_t bclk, gpio_num_t ws, gpio_num_t dout, gpio_num_t din);
};

class NoAudioCodecSimplex : public NoAudioCodec {
public:
    NoAudioCodecSimplex(int input_sample_rate, int output_sample_rate, gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din);
    NoAudioCodecSimplex(int input_sample_rate, int output_sample_rate, gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, i2s_std_slot_mask_t spk_slot_mask, gpio_num_t mic_sck, gpio_num_t mic_ws, gpio_num_t mic_din, i2s_std_slot_mask_t mic_slot_mask);
};

class NoAudioCodecSimplexPdm : public NoAudioCodec {
public:
    NoAudioCodecSimplexPdm(int input_sample_rate, int output_sample_rate, gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, gpio_num_t mic_sck, gpio_num_t mic_din);
    NoAudioCodecSimplexPdm(int input_sample_rate, int output_sample_rate, gpio_num_t spk_bclk, gpio_num_t spk_ws, gpio_num_t spk_dout, i2s_std_slot_mask_t spk_slot_mask, gpio_num_t mic_sck, gpio_num_t mic_din);
    int Read(int16_t* dest, int samples) override;
};

#include "AudioKitHAL.h"

#define WAV_SAMPLES 43245
#define WAV_4SAMPLES WAV_SAMPLES*4

AudioKit kit;
uint8_t buffer[WAV_4SAMPLES];

void setup() {
  LOGLEVEL_AUDIOKIT = AudioKitInfo; 
  Serial.begin(115200);
  // open in write mode

  auto cfg = kit.defaultConfig(AudioOutput);
  cfg.sample_rate = AUDIO_HAL_16K_SAMPLES;
  cfg.dac_output = AUDIO_HAL_DAC_OUTPUT_LINE2; // Левый?
  cfg.codec_mode =AUDIO_HAL_CODEC_MODE_DECODE;
  cfg.bits_per_sample = AUDIO_HAL_BIT_LENGTH_16BITS;

  // Serial.print("SampleRate:"); Serial.println(cfg.sampleRate());
  // Serial.print("dac_output:"); Serial.println(cfg.dac_output);
  // Serial.print("buffer size:"); Serial.println(cfg.buffer_size);
  // Serial.print("i2sconf bits per sample:"); Serial.println(cfg.i2sConfig().bits_per_sample);
  ///Serial.print("i2sconf bits per chan:"); Serial.println(cfg.i2sConfig().bits_per_chan);

  kit.begin(cfg);


}

void loop() {
  size_t l = read_to_i2s(buffer,WAV_4SAMPLES);
  kit.write(buffer,l);
  delay(5000);
}



size_t read_to_i2s(uint8_t *buffer, size_t bytes){
            size_t result = 0;
            int16_t *ptr = (int16_t*)buffer;
            for (int j=0;j<bytes/4;j++){
                int16_t sample = signal_samples[j];
                *ptr++ = sample;
                *ptr++ = sample;
                result+=4;
            }
            return result;
}


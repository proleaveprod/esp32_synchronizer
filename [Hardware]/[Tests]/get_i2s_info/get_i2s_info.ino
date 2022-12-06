/**
 * @file headphone.ino
 * @author Phil Schatzmann
 * @brief Headphone Detection Demo
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

 #define AUDIOKIT_BOARD 7
#include "AudioKitHAL.h"
#include "SineWaveGenerator.h"
#define AUDIOKIT_DEFAULT_I2S_FMT        AUDIO_HAL_I2S_LEFT

AudioKit kit;
SineWaveGenerator wave;
const int BUFFER_SIZE = 1024;
uint8_t buffer[BUFFER_SIZE];

void setup() {
  LOGLEVEL_AUDIOKIT = AudioKitInfo; 
  Serial.begin(115200);

  //Serial.println(KIT_LOG);
  

  
  // open in write mode
  auto cfg = kit.defaultConfig(AudioOutput);
  cfg.fmt = AUDIO_HAL_I2S_LEFT;
  kit.begin(cfg);
  Serial.print(kit.pinHeadphoneDetect());
  // 1000 hz
  wave.setFrequency(500);
  wave.setSampleRate(cfg.sampleRate());

  Serial.print("SampleRate:"); Serial.println(cfg.sampleRate());
  Serial.print("dac_output:"); Serial.println(cfg.dac_output);
  Serial.print("buffer size:"); Serial.println(cfg.buffer_size);
  Serial.print("i2sconf bits per sample:"); Serial.println(cfg.i2sConfig().bits_per_sample);
  Serial.print("audio format: ");Serial.println(cfg.fmt);

  Serial.println("______PINS_______");
  i2s_pin_config_t pines;
  pines = cfg.i2sPins();
  
  Serial.print("bck_io_num: ");Serial.println(pines.bck_io_num);
  Serial.print("ws_io_num: ");Serial.println(pines.ws_io_num);
  Serial.print("data_out_num: ");Serial.println(pines.data_out_num);
  Serial.print("data_in_num: ");Serial.println(pines.data_in_num);



}

void loop() {
  size_t l = wave.read(buffer, BUFFER_SIZE);
  kit.write(buffer, l);
}
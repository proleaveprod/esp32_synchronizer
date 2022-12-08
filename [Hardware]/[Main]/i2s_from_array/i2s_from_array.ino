/**
 * @file streams-generator_fromarray-audiokit.ino
 * @brief Tesing GeneratorFromArray with output on audiokit
 * @author Phil Schatzmann
 * @copyright GPLv3
 */
 
#include "AudioTools.h"
#include "AudioLibs/AudioKit.h"
#include "signal10ms_18k.h"

uint16_t sample_rate=48000;
uint8_t channels = 2;                                      // The stream will have 2 channels 

GeneratorFromArray<int16_t> signal(wav_array,0,false);
GeneratedSoundStream<int16_t> sound(signal);             // Stream generated 
AudioKitStream out; 

StreamCopy copier(out, sound);                             // copies sound into i2s

// Arduino Setup
void setup(void) {  
  // Open Serial 
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  // start I2S
  Serial.println("starting I2S...");
  auto config = out.defaultConfig(TX_MODE);
  config.sample_rate = sample_rate; 
  config.channels = channels;
  config.bits_per_sample = 16;
  out.begin(config);

  // Setup sine wave
  auto cfg = signal.defaultConfig();
  cfg.channels = channels;
  cfg.sample_rate = sample_rate;
  sineWave.begin(cfg);
  Serial.println("started...");
}

// Arduino loop - copy sound to out 
void loop() {
  copier.copy();
}
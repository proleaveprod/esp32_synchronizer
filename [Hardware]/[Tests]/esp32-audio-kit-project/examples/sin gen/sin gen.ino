/**
 * @file headphone.ino
 * @author Phil Schatzmann
 * @brief Headphone Detection Demo
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "AudioKitHAL.h"
#include "SineWaveGenerator.h"


AudioKit kit;
SineWaveGenerator wave;
const int BUFFER_SIZE = 1024;
uint8_t buffer[BUFFER_SIZE];

void setup() {
  LOGLEVEL_AUDIOKIT = AudioKitInfo; 
  Serial.begin(115200);
  // open in write mode
  auto cfg = kit.defaultConfig(AudioOutput);
  kit.begin(cfg);

  // 1000 hz
  wave.setFrequency(250);
  wave.setSampleRate(cfg.sampleRate());

}

uint16_t last_time=0;
uint16_t freq=500;
void loop() {
  size_t l = wave.read(buffer, BUFFER_SIZE);
  kit.write(buffer, l);

  if(millis()-last_time > 1000){
    wave.setFrequency(freq);
    freq+=250;
    if(freq==3000)freq=500;
    last_time = millis();
  }

}
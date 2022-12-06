#include "AudioKitHAL.h"
#include "SineWaveGenerator.h"
//#include "hl2_8k_int16.h"

#define SAMPLES WAV_SAMPLES
#define CBUFF   256*4
uint8_t buff[CBUFF];
uint8_t zerobuff[CBUFF]={0};

int smp_cnt=0;


AudioKit kit;
SineWaveGenerator wave;

void setup() {
  LOGLEVEL_AUDIOKIT = AudioKitDebug; 
  Serial.begin(115200);




  // open in write mode
  auto cfg = kit.defaultConfig(AudioOutput);
  cfg.sample_rate = AUDIO_HAL_08K_SAMPLES;
  kit.begin(cfg);


  wave.setFrequency(1000);
  wave.setSampleRate(cfg.sampleRate());
  
  // 1000 hz

}

size_t l=0;

long t1,t2;
esp_err_t err_state;
void loop() {
  err_state = es8388_set_voice_mute(0);
  delay(100);
  //t1 = millis();
  Serial.println("a");
  wave.m_time = 0;
  for(int i=0;i<10;i++){
  l = wave.read(buff,CBUFF);
  kit.write(buff, l);
  }
  err_state = es8388_set_voice_mute(1);
  Serial.print("s:");Serial.println(err_state);

  //t2=millis();
  //Serial.print("m1:");Serial.println(t2-t1);
  //for(int i=0;i<10;i++)kit.write(zerobuff,l);
  //t1=millis();
  //Serial.print("m2:");Serial.println(t1-t2);


  delay(1000);
}

uint32_t reading(uint8_t *buffer,int len){
            size_t result = 0;
            int16_t *ptr = (int16_t*)(buffer);

            for (int j=0;j<len;j++){
                int16_t sample = signal_samples[j+smp_cnt];
                *ptr++ = sample;
                *ptr++ = sample;
                result+=4;
            }

            smp_cnt+=len;
            if(smp_cnt>=SAMPLES)smp_cnt=0;

            return result;
}




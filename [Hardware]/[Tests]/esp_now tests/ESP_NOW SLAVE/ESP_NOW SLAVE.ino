/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>

#define PIN_TEST  21

#define WIFI_RATE WIFI_PHY_RATE_48M

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  char recData;
  memcpy(&recData, incomingData, sizeof(recData));


  if(recData=='@'){
    
      digitalWrite(PIN_TEST,1);
      long time_d = micros();
      while(micros()-time_d<3000);
      digitalWrite(PIN_TEST,0);


  }
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(PIN_TEST,OUTPUT);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_err_t status = esp_wifi_config_espnow_rate(WIFI_IF_STA,WIFI_RATE);
  Serial.println(status);
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

}
 
void loop() {

}
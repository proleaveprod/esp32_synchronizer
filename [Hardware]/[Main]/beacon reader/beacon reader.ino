#include <WiFi.h>
#define PIN_TEST  21
#define WIFI_RATE WIFI_PHY_RATE_48M




 
void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  esp_wifi_init();

}
 
void loop() {
  delay(1000);  // Нужно, чтобы не ебашило таймер.
}


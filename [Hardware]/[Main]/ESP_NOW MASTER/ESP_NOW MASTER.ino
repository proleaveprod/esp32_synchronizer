#include <esp_now.h>
#include <WiFi.h>


#define PIN_TEST  21
#define PIN_TEST2  22

#define WIFI_RATE WIFI_PHY_RATE_48M

uint8_t master1Addr[] = {0xC4,0xDE,0xE2,0x1C,0x40,0xCC};
//uint8_t slave2Addr[] =  {0xFF,0xFF,0xFF,0xFF,0xFF,0xF1};

uint8_t slave2Addr[] = {0xC4,0xDE,0xE2,0x1C,0x47,0x44};
uint8_t slave3Addr[] = {0xC4,0xDE,0xE2,0x20,0x07,0xC4};
uint8_t slave4Addr[] = {0xC4,0xDE,0xE2,0x1C,0x44,0x14};
uint8_t dataToSend = '@';

long time1;
#define TIME1 10000

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    digitalWrite(PIN_TEST,1);
    long time_d = micros();
    while(micros()-time_d<3000);
    digitalWrite(PIN_TEST,0);
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  
  
  pinMode(PIN_TEST,OUTPUT);
  pinMode(PIN_TEST2,OUTPUT);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }


  esp_err_t status = esp_wifi_config_espnow_rate(WIFI_IF_STA,WIFI_RATE);
  Serial.println(status);

  
  esp_now_register_send_cb(OnDataSent);

  peerInfo.channel = 0;  
  peerInfo.encrypt = false; 

  memcpy(peerInfo.peer_addr, slave2Addr, 6);       
  if (esp_now_add_peer(&peerInfo) != ESP_OK)Serial.println("Failed to add peer with SLAVE2");

  // memcpy(peerInfo.peer_addr, slave3Addr, 6);       
  // if (esp_now_add_peer(&peerInfo) != ESP_OK)Serial.println("Failed to add peer with SLAVE3");

  // memcpy(peerInfo.peer_addr, slave4Addr, 6);       
  // if (esp_now_add_peer(&peerInfo) != ESP_OK)Serial.println("Failed to add peer with SLAVE4");


}
 
void loop() {
  uint32_t check_counter=0;

  if(micros()-time1 > 100000){ // Раз в 100мс делать:

  digitalWrite(PIN_TEST2,1);
  long time_d = micros();  // Пускаем импульс

  esp_err_t result = esp_now_send(slave2Addr, &dataToSend, sizeof(dataToSend)); // Отправляем байт
  
  while(micros()-time_d<3000)check_counter++; //  Ждем момента, когда импульс будет по времени 3мс. 
  digitalWrite(PIN_TEST2,0);
  Serial.print("check_counter = ");Serial.println(check_counter); // Выводим инфу сколько раз цикл прогнал себя до того, как прошло 3мс
                                                                  // Если будет 0, значит функция esp_now_send зависла на время более 3мс


  time1 = micros();
  }

  // esp_err_t result = esp_now_send(slave2Addr, &dataToSend, sizeof(dataToSend));
  // if (result == ESP_OK) {
  //   //Serial.println("Sent with success");
  // }
  // else {
  //   Serial.println("Error sending the data");
  // }
  // delay(100);
}



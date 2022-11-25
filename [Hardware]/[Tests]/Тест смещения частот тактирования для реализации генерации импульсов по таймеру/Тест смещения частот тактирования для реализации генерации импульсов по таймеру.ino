#include <esp_now.h>
#include <WiFi.h>

#define PIN_TEST  21
#define WIFI_RATE WIFI_PHY_RATE_48M
uint8_t master1Addr[] = {0xC4,0xDE,0xE2,0x1C,0x40,0xCC};
uint8_t broadcastAddr[] =  {0xFF,0xFF,0xFF,0xFF,0xFF,0xF1};
esp_now_peer_info_t peerInfo;
//ADDR S2 S3 S3: {0xC4,0xDE,0xE2,0x1C,0x47,0x44};{0xC4,0xDE,0xE2,0x20,0x07,0xC4};{0xC4,0xDE,0xE2,0x1C,0x44,0x14};

uint8_t dataToSend = '@';

uint32_t time1;
#define TIME1 10000

uint32_t t1_sync=0;
uint32_t t4_resp=0;

hw_timer_t *My_timer = NULL;

uint8_t pin_state=0;


 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  pinMode(PIN_TEST,OUTPUT);





  timer_init();
  Serial.println("Delay 5sec.");
  delay(5000);

  // wifi_init();
  

  // Serial.println("Delay 5sec.");
  // delay(5000);
  // master_sync();

}
 
void loop() {
  delay(1000);  // Нужно, чтобы не ебашило таймер.
}


void IRAM_ATTR onTimer(){       //   ОБРАБОТЧИК ТАЙМЕРА 

  pin_state = !pin_state;

  digitalWrite(PIN_TEST, pin_state);   // Блинкуем пин
}

void timer_init(){
  Serial.println("- TIMER init -");
  My_timer = timerBegin(3, 8, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 100, true);          //Раз в миллисек
  timerAlarmEnable(My_timer);

}

void master_sync(){
  Serial.println("Master Sync start");
  esp_now_unregister_recv_cb(); // Отключаем callback-функцию передачи
  esp_now_register_recv_cb(OnMasterRecvPTP);
  
  t1_sync = micros(); // Засекаем время
  uint8_t dataToSend[5] = {'$',0,0,0,0};       
  memcpy(&dataToSend[1], &t1_sync, 4);  // Копируем в dataToSend 4 байта с t1

  esp_now_send(broadcastAddr, dataToSend, 5); // Отправляем 5 байт Sync-пакета 
}

void OnMasterRecvPTP(const uint8_t * mac, const uint8_t *incomingData, int len){
  uint8_t recData=0;
  memcpy(&recData, incomingData, 1);

  if(recData=='@'){     // Если это Request
    t4_resp = micros();
    uint8_t dataToSend[5] = {'#',0,0,0,0};
    
    memcpy(&dataToSend[1], &t4_resp, 4);  // Копируем в dataToSend 4 байта с t1
    esp_now_send(broadcastAddr, dataToSend, 5); // Отправляем 5 байт Resp-пакета
    Serial.println("master sent Response");
  }


}

/*void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    digitalWrite(PIN_TEST,1);
    long time_d = micros();
    while(micros()-time_d<3000);
    digitalWrite(PIN_TEST,0);
}
*/

void wifi_init(){
  Serial.println("- ESP-NOW init -");
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_wifi_config_espnow_rate(WIFI_IF_STA,WIFI_RATE);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false; 
  memcpy(peerInfo.peer_addr, broadcastAddr, 6);       
  if (esp_now_add_peer(&peerInfo) != ESP_OK)Serial.println("Failed to add peer with BROADCAST");
  
}
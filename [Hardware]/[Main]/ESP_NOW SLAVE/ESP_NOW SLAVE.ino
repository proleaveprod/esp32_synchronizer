#include <esp_now.h>
#include <WiFi.h>

#define PIN_TEST  21
#define WIFI_RATE WIFI_PHY_RATE_48M
uint8_t master1Addr[] = {0xC4,0xDE,0xE2,0x1C,0x40,0xCC};
esp_now_peer_info_t peerInfo;

uint32_t t1_sync,t2_getSync,t3_req,t4_resp;
long deltaSync=0;
uint8_t deltaSync_counter=0;

hw_timer_t *My_timer = NULL;
uint8_t pin_state=0;
uint8_t tim_flag=0;

// callback function that will be executed when data is received


TaskHandle_t Task1;




 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(PIN_TEST,OUTPUT);
  
  // xTaskCreatePinnedToCore(
  // Task1code, /* Функция, содержащая код задачи */
  // "Task1", /* Название задачи */
  // 10000, /* Размер стека в словах */
  // NULL, /* Параметр создаваемой задачи */
  // 3, /* Приоритет задачи */
  // &Task1, /* Идентификатор задачи */
  // 0); /* Ядро, на котором будет выполняться задача */
  
  
  //timer_init();
  // Serial.println("Delay 1sec.");
  // delay(10000);
  slave_wifi_init();  

  esp_now_register_recv_cb(OnSlaveRecv1byte);

  //slave_sync();

  // esp_now_register_recv_cb(OnDataRecv);

}
 
void loop() {
  delay(1000);  // Нужно, чтобы не ебашило таймер.
}




void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core");
  Serial.println(xPortGetCoreID());
           //  "Задача Task1 выполняется на ядре "
  

  for(;;){
    digitalWrite(PIN_TEST, HIGH);
    delay(1000);
    digitalWrite(PIN_TEST, LOW);
    delay(1000);
  } 
}












uint32_t t1=0;
uint32_t t2=0;
void OnSlaveRecv1byte(const uint8_t * mac, const uint8_t *incomingData, int len){
  uint8_t recData=0;
  memcpy(&recData, incomingData, 1);  // Принимаем 5 байт с таймингом
  t1 = micros();

  //Serial.println(xPortGetCoreID());
  Serial.println(t1-t2);

  t2 = micros();

  // digitalWrite(PIN_TEST,1);
  //     long time_d = micros();
  //     while(micros()-time_d<3000);
  //     digitalWrite(PIN_TEST,0);
}
// void IRAM_ATTR onTimer(){

//   pin_state = !pin_state;

//   digitalWrite(PIN_TEST, pin_state);   // Блинкуем пин
// }

// void timer_init(){
//   Serial.println("- TIMER init -");
//   My_timer = timerBegin(3, 8, true);
//   timerAttachInterrupt(My_timer, &onTimer, true);
//   timerAlarmWrite(My_timer, 100, true);          //Раз в миллисек
//   timerAlarmEnable(My_timer);

// }

void slave_sync(){
  Serial.println("Slave sync start");
  esp_now_unregister_recv_cb(); // Отключаем callback-функцию приема
  esp_now_register_recv_cb(OnSlaveRecvPTP);
  t1_sync=0;
  t2_getSync=0;
  t3_req=0;
  t4_resp=0;
  deltaSync_counter=0;
}

void OnSlaveRecvPTP(const uint8_t * mac, const uint8_t *incomingData, int len){
  uint8_t recData[5];

  memcpy(&recData, incomingData, 5);  // Принимаем 5 байт с таймингом

  if(recData[0] == '$'){              // Для Sync+t1

    
    memcpy(&t1_sync, &recData[1], 4);                   // Получаем t1
    t2_getSync = micros();                              // Получаем t2

    uint8_t req_symbol = '@';
    esp_now_send(master1Addr, &req_symbol, 1);  // Отправляем Request 

    t3_req = micros();                                  // Получаем t3

  }else if (recData[0] == '#'){       // Для Resp+t4
    memcpy(&t4_resp, &recData[1], 4);                   // Получаем t4

    deltaSync = getDeltaSync(t1_sync,t2_getSync,t3_req,t4_resp);  // ПОЛУЧАЕМ СМЕЩЕНИЕ
    deltaSync_counter++;
    Serial.print(deltaSync_counter);Serial.print(". ");

     Serial.print("deltaSync = ");
    Serial.println(deltaSync%100000);
    Serial.print("time for sync = ");Serial.println(t4_resp-t1_sync);
    // Serial.print("    t1=");Serial.println(t1_sync);
    // Serial.print("    t4=");Serial.println(t4_resp);
    // Serial.print("    t2=");Serial.println(t2_getSync);
    // Serial.print("    t3=");Serial.println(t3_req);
  }

}

uint32_t getDeltaSync(uint32_t t1,uint32_t t2, uint32_t t3, uint32_t t4){
    uint32_t dT = 0;
    dT = t2 - t1; // Вычисляем смещение
    dT -= t4;
    dT += t3;
    dT /=2;
    return dT;
}

void slave_wifi_init(){
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);


  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //esp_wifi_config_espnow_rate(WIFI_IF_STA,WIFI_RATE);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false; 
  memcpy(peerInfo.peer_addr, master1Addr, 6); 
  if (esp_now_add_peer(&peerInfo) != ESP_OK)Serial.println("Failed to add peer with MASTER");



}
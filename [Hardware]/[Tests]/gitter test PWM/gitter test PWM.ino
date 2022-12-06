const int testPin = 21;

// задаём свойства ШИМ-сигнала
const int freq = 50000;
const int testChannel = 1;
const int resolution = 10;

//LEDC_APB_CLK_SEL = 1;
void setup(){
  ledcSetup(testChannel, freq, resolution); // частота 50к; максимальная скважность 1024 единиц (при разрешении 10 бит)
  
  // привязываем канал к портам светодиодов
  ledcAttachPin(testPin, testChannel);


  ledcWrite(testChannel, 512);  // Запускаем подачу ШИМ-сигнала. частота 50к и скважность 512 (50%). То есть это генерация импульсов 10мкс.

}
 
void loop(){
  
}
#define PIN_MASTER  12
#define PIN_SLAVE   14

uint32_t time_slave,time_master;
int64_t dt;
uint32_t counter=0;
void setup() {

  Serial.begin(115200);
  pinMode(PIN_MASTER,INPUT);
  pinMode(PIN_SLAVE,INPUT);

}

void loop() {

  while(!digitalRead(PIN_SLAVE)); //Ждем импульса slave
  time_slave = micros();
  while(!digitalRead(PIN_MASTER)); // Ждем импульса master
  time_master = micros();

  while(digitalRead(PIN_SLAVE)); // Ждем окончания импульса slave
  while(digitalRead(PIN_MASTER)); // Ждем окончания импульса master

  dt = time_master - time_slave;

  //if(dt>100)dt = 3000-dt;   
  if(dt<300)Serial.print(dt);Serial.print("\n");   //  Если меньше 1000! 
              //Программа не предусматривает ошибки(когда имульс слейв позже мастера) или когда очень сильная задержка есть
  counter++;


  if(counter==1000){while(1);}
}

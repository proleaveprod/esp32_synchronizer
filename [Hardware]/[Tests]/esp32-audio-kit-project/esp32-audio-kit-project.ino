#define LED_1   22
#define LED_2   19

#define KEY_1   36
#define KEY_2   13
#define KEY_3   19
#define KEY_4   23
#define KEY_5   18
#define KEY_6   5

void setup() {
  
  Serial.begin(115200);
  gpio_init();
  led_test();
  Serial.println("\n\n_____________\nESP32 STARTED");
  



}

void loop() {

}


void gpio_init(){
  pinMode(LED_1,OUTPUT);
  pinMode(LED_2,OUTPUT);
}

void led_test(){
  digitalWrite(LED_2,1);
  for(int i=0;i<10;i++){
    digitalWrite(LED_1,0);
    delay(20);
    digitalWrite(LED_1,1);
    delay(20);
  }

  for(int i=0;i<10;i++){
    digitalWrite(LED_2,0);
    delay(20);
    digitalWrite(LED_2,1);
    delay(20);
  }
}

void key_test(){

  Serial.print("KEYS:   ");Serial.print(digitalRead(KEY_1));
  Serial.print("   ");Serial.print(digitalRead(KEY_2));
  Serial.print("   ");Serial.print(digitalRead(KEY_3));
  Serial.print("   ");Serial.print(digitalRead(KEY_4));
  Serial.print("   ");Serial.print(digitalRead(KEY_5));
  Serial.print("   ");Serial.println(digitalRead(KEY_6));


}
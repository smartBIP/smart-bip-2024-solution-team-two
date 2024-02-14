// display
#include <TM1637Display.h>
#define CLK 3
#define DIO 4
TM1637Display display = TM1637Display(CLK, DIO);

//temp
#define TEMP_SENSOR_PIN 5
int tempVal;

// temp + humidity
#define DHT11_PIN 5
#include <dht.h>
dht DHT;

// led lamp
#define LED_LAMP 6

// sabotage sensor
#define SAB_SENSOR 8

// ir count sensor for entrance sensor
#define ENTRANCE_COUNT 2

// sound 7
#define BUZZ 7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //display
  display.clear();
  display.setBrightness(7);

  // buzzer
  pinMode(BUZZ, OUTPUT); // Set buzzer - pin 9 as an output
}

void loop() {
  // put your main code here, to run repeatedly:

  // TEMP sensor

  // tempVal = analogRead(TEMP_SENSOR_PIN);  
  // float mv = (tempVal * 5.0 / 1023.0) * 100;
  // float cel = mv/10;
  // Serial.print("TEMPRATURE = ");
  // Serial.print(cel);
  // Serial.print("*C");
  // Serial.println();

  //temp and humidity
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  // delay(1000);
  
  //buzz if the remperature is over 25
  // if(cel > 25){
  //   Serial.println("OVER");
  //   tone(BUZZ, 1000); // Send 1KHz sound signal...
  //   delay(1000);        // ...for 1 sec
  //   noTone(BUZZ);     // Stop sound...
  //   delay(1000);        // ...for 1sec
  // }
   if(DHT.temperature > 30){
    Serial.println("OVER");
    tone(BUZZ, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(BUZZ);     // Stop sound...
    delay(1000);        // ...for 1sec
  }
  delay(1000);

  // Count sensor for entering

  // DISPLAY sensor
  display.showNumberDec(DHT.temperature);



}

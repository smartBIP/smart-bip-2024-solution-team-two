// display
#include <TM1637Display.h>
#define CLK 3
#define DIO 4
TM1637Display display = TM1637Display(CLK, DIO);

//temp
// #include <OneWire.h>
// #include <DallasTemperature.h>
#define TEMP_SENSOR_PIN 5
int tempVal;
// sabotage sensor 8
// led lamp is 6
// ir sensor 2

// sound 7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //display
  display.clear();
  display.setBrightness(7);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Count sensor for entering

  // TEMP sensor

  tempVal = analogRead(TEMP_SENSOR_PIN);  
  // float mv = ( tempVal /1024.0)*5000;
  float mv = (tempVal * 5.0 / 1023.0) * 100;
  float cel = mv/10;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();

  delay(1000);

    // DISPLAY sensor
      display.showNumberDec(cel);


}

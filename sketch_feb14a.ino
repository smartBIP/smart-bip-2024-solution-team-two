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
int digital;

// exit counter
#define EXIT_SENSOR 9

// enter counter 
#define ENTRANCE_COUNT 2
int amount_of_people = 0;

// sound 7
#define BUZZ 7

//button
#define BUTTON 10
int buttonState = 0;
int pressCount = 0;

// LED
#define LED 6
int ledState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(SAB_SENSOR, INPUT);
  Serial.begin(9600);

  //display
  display.clear();
  display.setBrightness(7);

  // buzzer
  pinMode(BUZZ, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(BUTTON, INPUT); // Set button as an input
  pinMode(LED, OUTPUT);  // initialize the LED pin as an output:
}

void showTempHum(){
//temp and humidity
  int chk = DHT.read11(DHT11_PIN);
  // Serial.print("Temperature = ");
  // Serial.println(DHT.temperature);
  // Serial.print("Humidity = ");
  // Serial.println(DHT.humidity);
}

void enterCounter(){
  amount_of_people += digitalRead(ENTRANCE_COUNT);
  display.showNumberDec(amount_of_people);
}

void exitCounter(){
  amount_of_people -= digitalRead(EXIT_SENSOR);
  if(amount_of_people < 0){
    amount_of_people = 0;
  }
  display.showNumberDec(amount_of_people);
}
void buzzIfTempHum(){
  // buzz if the temperature is over 30
  // when hum and temp are too high buzz as well but make the functionality
   if(DHT.temperature > 30){
    Serial.println("OVER");
    tone(BUZZ, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(BUZZ);     // Stop sound...
    delay(1000);        // ...for 1sec
  }
}

void sabotage(){
  //sabotage
  digital = digitalRead(SAB_SENSOR);
  // Serial.print("digital=");
  // Serial.print(digital); 
  if(digital == HIGH) {
    //comment the lines below if you don t want it to buzz
    // tone(BUZZ, 1000); // Send 1KHz sound signal...
    // delay(1000);        // ...for 1 sec
    // noTone(BUZZ);     // Stop sound...
    // delay(1000); 
  };
}

void buttonFunct(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON);
  Serial.println(buttonState);
  // check if the pushbutton is pressed. If it is, the buttonState is LOW:
  // if (buttonState == LOW) {
  //   Serial.println("button pressed");
  //   // turn LED on:
  //   if(ledState = 0){
  //     Serial.println("ledState is 0");
  //     // ledState = 1;
  //     digitalWrite(LED, HIGH);
  //   }else{
  //     Serial.println("ledstate is 1");
  //     // ledState = 0;
  //     digitalWrite(LED, LOW);
  //   }
  // } 
  if(buttonState == LOW){
    if(pressCount % 2 == 1){
      digitalWrite(LED, HIGH);
    }else{
      digitalWrite(LED, LOW);
    }
    pressCount += 1;
  }
}
void loop() {
  // put your main code here, to run repeatedly:

  enterCounter();
  exitCounter();
  showTempHum();
  buzzIfTempHum();
  sabotage();
  buttonFunct();
  // Count sensor for entering
  // DISPLAY sensor
 // display.showNumberDec(DHT.temperature);
  delay(300);
}
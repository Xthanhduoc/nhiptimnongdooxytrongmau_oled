#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
PulseOximeter pox;
unsigned long timeS=millis();
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>
Adafruit_SSD1306 display(128, 32, &Wire, -1);
#include <Ticker.h>
Ticker timer;

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  display.setFont(&FreeSerif9pt7b);
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);        
  display.setCursor(20,10);             
  display.println("Welcome to");
  display.setCursor(0,30);             
  display.println("DTM E-SMART");            
  display.display();
  delay(2000); 
  if (!pox.begin()) {
      Serial.println("FAILED");
      for(;;);
  } else {
      Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
  timer.attach_ms(100, update);
}

void loop() {
  if(millis()-timeS>1000){
    Serial.print("Heart rate:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("%");

    display.clearDisplay(); 
    display.setCursor(0,12);  
    display.print("HeartR:");
    display.print(pox.getHeartRate(),0); 
    display.println(" bpm");
    display.setCursor(0,29);
    display.print("SpO2  : ");
    display.print(pox.getSpO2());
    display.println(" %");
    display.display();

    timeS=millis();
  }
}
void update(){
  pox.update();
}
void onBeatDetected()
{
    Serial.println("Beat!");
}
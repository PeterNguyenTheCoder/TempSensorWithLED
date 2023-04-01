#include "DHT.h"
#include "SimpleDHT.h"
#include <Adafruit_Sensor.h> // necessary for all adafruit sensors

#define DHTPIN 4 
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Define pins
#define BLUE 3
#define GREEN 5
#define RED 6
#define delayTime 20 // fading time between colours

int redValue = 255; // analog integer from 0 to 255
int greenValue = 0; // analog integer from 0 to 255
int blueValue = 0; // analog integer from 0 to 255

// Read temperature as Celsius
float t = dht.readTemperature(); // had to adjust to get values in Celsius as there was an issue with my sensor
float t1 = t - 260.0;

void setup() {
  Serial.begin(750);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  analogWrite(RED, LOW);
  analogWrite(GREEN, LOW);
  analogWrite(BLUE, LOW);
  dht.begin();
}

void loop() {

  tempSensor();
  if (t1 >= 20) {
    redValue = 255;    
  }
  if (t1 < 20 && t1 >= 15) {
    redValue = 200;
    blueValue = 50;
  }
  if (t1 < 15 && t1 >= 10) {
    redValue = 150;
    blueValue = 100;
  }
  if (t1 < 10 && t1 >= 5) {
    redValue = 100;
    blueValue = 150;
  }
  if (t1 < 5 && t1 >= 0) {
    redValue = 50;
    blueValue = 200;
  }
  if (t1 < 0) {
    redValue = 0;
    blueValue = 255;
  }
  //led();
  delay(1);
}

void led() {
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);
  // redValue -= delayTime;
  // blueValue += delayTime;  
}

void tempSensor() {
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t3 = dht.readTemperature(); // had to adjust to get values in Celsius as there was an issue with my sensor
  float t4 = t3 - 260.0;

  // if (isnan(h) || isnan(t4)) { // isnan() means is not a number || means or (if one or both are true, if statement is triggered)
  //   Serial.println(F("Failed to read from DHT sensor!"));
  //   return;
  // }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(t4);
  Serial.println("°C ");
  delay(1);
}

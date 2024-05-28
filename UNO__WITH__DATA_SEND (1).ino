#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <SPI.h>
#include "DHT.h"
#include "Wire.h" 
#define DHT_A_TYPE DHT11
#define DHTP A0 
DHT dht(DHTP, DHT_A_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial espSerial(2,3); //tx,rx

const int MPU_ADDR = 0x68; 
const int trigPin = 11; 
const int echoPin = 10; 
long duration; 
int distance; 

#define GLED 12
#define RLED 13

String cdata;

void setup()
{
  Serial.begin(115200);
  dht.begin();
  espSerial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); 
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true);
  pinMode(DHTP, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.print("ANTI-PLUNDERING");
  lcd.setCursor(0, 1);
  lcd.print("BIET COLLEGE DVG");
  delay(4000);
  lcd.clear();
}

void loop()
{
  //--------TEMP---------------//
  int h = dht.readHumidity();
  int t = dht.readTemperature();
//  Serial.print("HUM: ");
//  Serial.println(h);
//  Serial.print("TEMP: ");
//  Serial.println(t);

    
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.setCursor(2, 0);
  lcd.print(t);

  lcd.setCursor(5, 0);
  lcd.print("H:");
  lcd.setCursor(7, 0);
  lcd.print(h);

//--------MPU---------------//
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7*2, true); 

  int accelerometer_x = Wire.read()<<8 | Wire.read(); 
  int accelerometer_y = Wire.read()<<8 | Wire.read(); 
  int accelerometer_z = Wire.read()<<8 | Wire.read(); 

//  Serial.print("aX = "); Serial.print(accelerometer_x);
//  Serial.print(" | aY = "); Serial.print(accelerometer_y);
//  Serial.print(" | aZ = "); Serial.print(accelerometer_z);
//  Serial.println();



  lcd.setCursor(0, 1);
  lcd.print("ST:");
  

  if(accelerometer_x>4000)
    {
      lcd.setCursor(3, 1);
      lcd.print("Tree..Cutting");
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      delay(5000);
    }
  else if(accelerometer_x<-4000)
   {
      lcd.setCursor(3, 1);
      lcd.print("Tree..Cutting");
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      delay(5000);
    }
   else if(accelerometer_y>4000)
   {
      lcd.setCursor(3, 1);
      lcd.print("Tree..Cutting");
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      delay(5000);
    }
   else if(accelerometer_y<-4000)
   {
      lcd.setCursor(3, 1);
      lcd.print("Tree..Cutting");
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      delay(5000);
    }
   else if(accelerometer_z<13000)
   {
      lcd.setCursor(3, 1);
      lcd.print("Tree..Cutting");
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      delay(5000);
    }
   else if(accelerometer_z<13000)
   {
      lcd.setCursor(3, 1);
      lcd.print("Tree..Cutting");
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      delay(5000);
    }
   else
   {
    lcd.setCursor(3, 1);
    lcd.print("Tree..Safe....");
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    }
   
//--------ULTRASONIC---------------//

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
   
//  Serial.print("distance:");
//  Serial.println(distance);

  lcd.setCursor(10, 0);
  lcd.print("AT:");

  
 if(distance > 10)
    {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
      lcd.setCursor(13, 0);
      lcd.print("OPN");
      delay(5000);
    }
 else
 {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    lcd.setCursor(13, 0);
    lcd.print("CLS");
  
  }
  
 if(t > 38)
     {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    }
 else
 {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
  }



if(espSerial.available())
   {
      Serial.print("NT=");
      Serial.print(t);
      Serial.println();
       
       Serial.print("NH=");
       Serial.println(h);
       Serial.println();

       Serial.print("NAX=");
       Serial.println(accelerometer_x);
       Serial.println();

       Serial.print("NAY=");
       Serial.println(accelerometer_y);
       Serial.println();

       Serial.print("NAZ=");
       Serial.println(accelerometer_z);
       Serial.println();

       Serial.print("NDIS=");
       Serial.println(distance);
       Serial.println();

       
       cdata = cdata + t+","+h+","+accelerometer_x+","+accelerometer_y+","+accelerometer_z+","+distance;
       Serial.println(cdata); 
       espSerial.println(cdata);
       delay(1000); // 100 milli seconds
       cdata = ""; 
  }
   
}


   

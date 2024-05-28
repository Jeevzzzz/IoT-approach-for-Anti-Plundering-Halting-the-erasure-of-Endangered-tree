#define BLYNK_TEMPLATE_ID "TMPLoZiLx5Lf"
#define BLYNK_DEVICE_NAME "ANTIPROACHING TREE"
#define BLYNK_AUTH_TOKEN "TKbZ6fPx-ZGcnP0Us0rCJxMIHswk66o2"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

 
char auth[] = "TKbZ6fPx-ZGcnP0Us0rCJxMIHswk66o2";
char ssid[] = "PROJECT";
char pass[] = "DEMO2024";

 
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors
 
int t,h,accelerometer_x,accelerometer_y,accelerometer_z,distance;

 
BlynkTimer timer;
void setup()
{
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  //timer.setInterval(1000L, sensorvalue);
}
 
void loop()
{
   if (Serial.available()) 
   {
  Blynk.run();
   }
   
  if (Serial.available()) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
    if( rdata == '\n')
    {
   String l = getValue(myString, ',', 0);
   String m = getValue(myString, ',', 1);
   String n = getValue(myString, ',', 2); 
   String o = getValue(myString, ',', 3); 
   String p = getValue(myString, ',', 4);
   String q = getValue(myString, ',', 5);  

 

t= l.toInt();
h= m.toInt();
accelerometer_x= n.toInt();
accelerometer_y= o.toInt();
accelerometer_z= p.toInt();
distance= q.toInt();




myString = "";
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

Blynk.virtualWrite(V0, t );
Blynk.virtualWrite(V4, h);


//---------BLYNK STRING----------//
if(t>38)
{
  Blynk.virtualWrite(V3, "ALERT FIRE DETECTED..."); 
  }
else
{
  Blynk.virtualWrite(V3, "NO FIRE DETECTED"); 
  }

if(distance>10)
{
  Blynk.virtualWrite(V1, "ALERT THEFT DETECTED"); 
  delay(5000);
  }
else
{
  Blynk.virtualWrite(V1, "NO THEFT DETECTED"); 
  
  }
if(accelerometer_x>4000)
    {
      Blynk.virtualWrite(V2, "ALERT TREE IS CUTTING"); 
      delay(5000);
    }
else
{
  Blynk.virtualWrite(V2, "TREE IS SAFE"); 
  }
    
if(accelerometer_x<-4000)
   {
      Blynk.virtualWrite(V2, "ALERT TREE IS CUTTING"); 
      delay(5000);
    }
else
{
  Blynk.virtualWrite(V2, "TREE IS SAFE"); 
  }

  
    
if(accelerometer_y>4000)
   {
      Blynk.virtualWrite(V2, "ALERT TREE IS CUTTING"); 
      delay(5000);
    }
else
{
  Blynk.virtualWrite(V2, "TREE IS SAFE"); 
  }

if(accelerometer_y<-4000)
   {
      Blynk.virtualWrite(V2, "ALERT TREE IS CUTTING"); 
      delay(5000);
    }
else
{
  Blynk.virtualWrite(V2, "TREE IS SAFE"); 
  }


if(accelerometer_z<13000)
   {
      Blynk.virtualWrite(V2, "ALERT TREE IS CUTTING");
      delay(5000); 
    }
else
{
  Blynk.virtualWrite(V2, "TREE IS SAFE"); 
  }

if(accelerometer_z<13000)
   {
      Blynk.virtualWrite(V2, "ALERT TREE IS CUTTING"); 
      delay(5000);
    }
else
{
  Blynk.virtualWrite(V2, "TREE IS SAFE"); 
  }
    





//---------EVENT LOG----------//



if(t>38)
{
  Blynk.logEvent("fire","Fire Detected");
  }

if(distance>10)
{
  Blynk.logEvent("open","Theft Detected");
  }
  
  }
}
 
}
 

 
 
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

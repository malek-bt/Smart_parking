//#include <LiquidCrystal.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial espSerial(2,3);


#define t1 13
#define t11 10
#define t2 9
#define t22 8
#define t3 7
#define t33 6
#define t4 5
#define t44 4

int distanceThreshold = 100;


void setup() {
  
  
  Serial.begin (9600);
  espSerial.begin(9600);
}

long readDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}


void loop()
{
  float d1 = 0.01723 * readDistance(t1, t11);
  float d2 = 0.01723 * readDistance(t2, t22);
  float d3 = 0.01723 * readDistance(t3, t33);
  float d4 = 0.01723 * readDistance(t4, t44);

  StaticJsonDocument<200> doc;
  if(d1>10){
  doc["cap1"] = false;
  }
  else{ 
  doc["cap1"] = true;
  }
  if(d2>10){
  doc["cap2"] = false;
  }
  else{ 
  doc["cap2"] = true;
  }
  if(d3>10){
  doc["cap3"] = false;
  }
  else{ 
  doc["cap3"] = true;
  }
  if(d4>10){
  doc["cap4"] = false;
  }
  else{ 
  doc["cap4"] = true;
  }
  
  
  
  
  //serializeJson(doc, Serial);
  Serial.println();
  serializeJsonPretty(doc, espSerial);
  //String str="hello";
  //espSerial.println(str);

  
if (d1>10 & d2>10 & d3>10 & d4>10){
  //lcd.setCursor(0,0);
  Serial.println("4 Slots Free");
  //lcd.setCursor(0,1);
  Serial.println("Slot 1 2 3 4 Free");
  delay(500);
  }
else if((d1>10 & d2>10 & d3>10)|(d2>10 & d3>10 & d4>10)|(d3>10 & d4>10& d1>10)|(d4>10 & d1>10 & d2>10))
  {
  //lcd.setCursor(0,0);
  Serial.println("3 Slots Free");
  //lcd.setCursor(0,1);

    if(d1>10 & d2>10 & d3>10)
    Serial.println("Slot 1 2 & 3 Free");
    else if(d1>10 & d3>10 & d4>10)
    Serial.println("Slot 1 3 & 4 Free");
    //else
    else if(d1>10 & d2>10 & d4>10)
    Serial.println("Slot 1 2 & 4 Free");
     else
    Serial.println("Slot 2 3 & 4 Free");
  delay(500);
  }
  else if((d1>10 & d2>10)|(d2>10 & d3>10 )|(d3>10 & d4>10) | (d4>10 & d1>10)|(d1>10&d3>10)|(d2>10&d4>10))
  {
  //lcd.setCursor(0,0);
  Serial.println("2 lots Free");
  //lcd.setCursor(0,1);
    if(d1>10 & d2>10)
    Serial.println("Slot 1 & 2 Free");
    else if(d2>10 & d3>10)
    Serial.println("Slot 2 & 3 Free");
    else if (d3>10 & d4>10)
        Serial.println("Slot 3 & 4 Free");
    else if(d4>10 & d1>10)
    Serial.println("Slot 1 and 4 ae Free");
      else if(d1>10 & d3>10)
        Serial.println("slot 1 and  3  Free");
      else if(d2>10 & d4>10)
        Serial.println("slot 2 and  4 Free");
      
    
  delay(500);
  }
  else if(d1<10 & d2<10 & d3<10 & d4<10)
  {
  //lcd.setCursor(0,0);
  Serial.println("No Slot Free");
  //lcd.setCursor(0,1);
  Serial.println("Parking Full");
  delay(500);
  }

else if((d1<10 & d2<10 & d3<10)|(d2<10 & d3<10 & d4<10)|(d3<10 & d4<10 & d1<10)|(d4<10 & d1<10 &d2<10))
  {
  //lcd.setCursor(0,0);
  Serial.println("1 Slot Free");
  //lcd.setCursor(0,1);
    if(d1>100)
      Serial.println("Slot 1 is Free");
  else if (d2>100)
       Serial.println("Slot 2 is Free");
    else if (d3>100)
       Serial.println("Slot 3 is Free");
    else
       Serial.println("Slot 4 is Free");
  delay(500);
   }
  

  delay(100);
}

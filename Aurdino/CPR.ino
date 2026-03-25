#include <LiquidCrystal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define heart 13                             
const int rs = 13, en = 12, d4 =14 , d5 = 27, d6 = 26, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int data=36;//heartbeat sensor


int buzzer=19;

unsigned long temp=0;

byte customChar1[8] = {0b00000,0b00000,0b00011,0b00111,0b01111,0b01111,0b01111,0b01111};
byte customChar2[8] = {0b00000,0b11000,0b11100,0b11110,0b11111,0b11111,0b11111,0b11111};
byte customChar3[8] = {0b00000,0b00011,0b00111,0b01111,0b11111,0b11111,0b11111,0b11111};
byte customChar4[8] = {0b00000,0b10000,0b11000,0b11100,0b11110,0b11110,0b11110,0b11110};
byte customChar5[8] = {0b00111,0b00011,0b00001,0b00000,0b00000,0b00000,0b00000,0b00000};
byte customChar6[8] = {0b11111,0b11111,0b11111,0b11111,0b01111,0b00111,0b00011,0b00001};
byte customChar7[8] = {0b11111,0b11111,0b11111,0b11111,0b11110,0b11100,0b11000,0b10000};
byte customChar8[8] = {0b11100,0b11000,0b10000,0b00000,0b00000,0b00000,0b00000,0b00000};

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 18 

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float temperature;

#include <Wire.h>

#include <Adafruit_Sensor.h> 

#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

void Connect_wifi();
float BPM, SpO2;
int count=0;

char mystr[20];

PulseOximeter pox;
uint32_t tsLastReport = 0;
int A=0;
char ch;
int X_val,Y_val;

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>


const char* ssid = "Praveen";
const char* password = "123456789";

// Initialize Telegram BOT
#define BOTtoken "8441427560:AAG4zcUNS8g8_npp0-r1hpdgrR4B-ch7_98"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "5513403184"
//X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

//
//char Start_buff[70]; 
//int i,z;             
//char ch;
//int str_len;
//char textmessage[20];



void Init_spo2();
void HEART_BEAT_MONITOR();

int LO_1=2;
int LO_2=4;

int ECG_val;
const int ECG=34;

int SW=5;
int relay=23;

void Init_spo2()
{
   Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");

    pox.setOnBeatDetectedCallback(onBeatDetected);
  }

  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);



}

void onBeatDetected()
{
  Serial.println("Beat Detected!");
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(data,INPUT);
  pinMode(SW,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
  pinMode(LO_1, INPUT); // Setup for leads off detection LO +
  pinMode(LO_2, INPUT); // Setup for leads off detection LO -
  pinMode(relay,OUTPUT);
  Serial.begin(9600);  //Initialize serial
   lcd.begin(16, 2); 
  lcd.clear();
  lcd.print("CHEST");
  lcd.setCursor(0, 1);
  lcd.print("COMPRESSION");
  delay(1000);
   
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.createChar(5, customChar5);
  lcd.createChar(6, customChar6);
  lcd.createChar(7, customChar7);
  lcd.createChar(8, customChar8);

     Serial.println("Starting TelegramBot...");

    Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

   Serial.print("Initializing pulse oximeter..");

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");

    pox.setOnBeatDetectedCallback(onBeatDetected);
  }
   if(!accel.begin())
   {

      Serial.println("No valid sensor found");

      while(1);

   }


  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
//   attachInterrupt(digitalPinToInterrupt(SW), Emergency, FALLING); 
digitalWrite(buzzer,LOW);
   digitalWrite(relay,LOW);
 bot.sendMessage(CHAT_ID, "Chest Compressor Interactive CPR..");
  delay(2000); 
   

}



void loop() 
{
   Emergency();
  // put your main code here, to run repeatedly:
  int i=0;
 Init_spo2();
    while(i<10000)
    {
        pox.update();
        BPM = pox.getHeartRate();
        SpO2 = pox.getSpO2();
      
        if (millis() - tsLastReport > REPORTING_PERIOD_MS)
        {
      
          Serial.print("Glucose: ");
          Serial.print(BPM);
          Serial.println("");
      
          Serial.print("SpO2: ");
          Serial.print(SpO2);
          Serial.println("%");
          lcd.clear();
          lcd.print("Glucose: ");
          lcd.print(BPM);
          lcd.setCursor(12,0);
          lcd.print("mmol/L");
          lcd.setCursor(0, 1);
          lcd.print("SpO2: ");
          lcd.print(SpO2);
          lcd.print("%");
      
          Serial.println("*****");
          Serial.println();
       //   delay(1000);
      
          tsLastReport = millis();
        }
//        delay(500);
        i++;
    }

    if((pox.getSpO2()<90)&&(A==1))
        {
          A=0;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("SPO2 IS LESS");
          lcd.setCursor(0,1);
          lcd.print("ATTEND PATIENT");
          Serial.println("$SPO2 IS LESS ATTEND PATIENT#");
          
          digitalWrite(buzzer,HIGH);
          delay(1000);
          digitalWrite(buzzer,LOW);
          bot.sendMessage(CHAT_ID, "SPO2 &ECG IS LESS ATTEND PATIENT");
  delay(2000); 
//         MOTORCHECK();
       
       for(int z=0;z<5;z++)
       {
        digitalWrite(relay,HIGH);
        
        delay(3000);
        digitalWrite(relay,LOW);
        
        delay(500);
       } 
  delay(500); 

       
        
        }
        
        if(pox.getSpO2()>91)
        {
        
         digitalWrite(relay,LOW);
         delay(1000);
        }
    HEART_BEAT_MONITOR();
    TEMP_MONITOR();
     Fall_check();
    ECGCheck();
    Emergency();
    delay(500);
    
}
void Fall_check() 
{
  sensors_event_t event; 

   accel.getEvent(&event);

  X_val=event.acceleration.x;

  Y_val=event.acceleration.y;

  int Z_val=event.acceleration.z;
   

   Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");

   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");

   //Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");

   Serial.println("m/s^2 ");

   lcd.clear();
   lcd.print("X:");
   lcd.print(X_val);
   lcd.setCursor(0,1);
   lcd.print("Y:");
   lcd.print(Y_val);

   if((X_val<-5.5)||(X_val>5.5))
   {
   // Fall=1;
    lcd.clear();
    lcd.print("Fall Detected");
      //  Serial.println(Fall);
    Serial.println("$FALL DETECTED#");
      String one ="Fall Detected Location AT:";
       
           String two ="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
      
          String message= one + two +"12.9759,77.4832";
           // Convert String to char array
           int str_len = message.length() + 1;
           char textmessage[str_len];
           message.toCharArray(textmessage,str_len);
          Serial.println('$'+String(textmessage)+'#');
           bot.sendMessage(CHAT_ID, textmessage);
              digitalWrite(buzzer,HIGH);
             
              delay(1000);
               digitalWrite(buzzer,LOW);
               
   }
   if((Y_val<-5.5)||(Y_val>5.5))
   {
//      Fall=1;
    lcd.clear();
    lcd.print("Fall Detected");
//    Serial.println(Fall);
   
    Serial.println("$FALL DETECTED#");
    String one ="Fall Detected Location AT:";
       
           String two ="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
      
          String message= one + two +"12.9759,77.4832";
           // Convert String to char array
           int str_len = message.length() + 1;
           char textmessage[str_len];
           message.toCharArray(textmessage,str_len);
          Serial.println('$'+String(textmessage)+'#');
           bot.sendMessage(CHAT_ID, textmessage);
            digitalWrite(buzzer,HIGH);
              delay(1000);
               digitalWrite(buzzer,LOW);
              
   }
 Emergency();

   
}
void Emergency()
{
  if(digitalRead(SW)==LOW)
    {
     Serial.println("Emergency...");
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
   

      for(int z=0;z<5;z++)
       {
         digitalWrite(relay,HIGH);
      
        delay(3000);
        digitalWrite(relay,LOW);
        
        delay(500);
       } 
  delay(500);
       String one ="Fall Detected Location AT:";
       
           String two ="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
      
          String message= one + two +"12.9759,77.4832";
           // Convert String to char array
           int str_len = message.length() + 1;
           char textmessage[str_len];
           message.toCharArray(textmessage,str_len);
          Serial.println('$'+String(textmessage)+'#');
           bot.sendMessage(CHAT_ID, textmessage);
            digitalWrite(buzzer,HIGH);
              delay(1000);
               digitalWrite(buzzer,LOW);
 
    }
}
void TEMP_MONITOR()
{

  sensors.requestTemperatures(); 
  temperature = sensors.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  delay(1000);
  lcd.clear();
  lcd.print("Temp:");
  lcd.print(temperature);  
  lcd.print("C");
  delay(2000);
  Emergency();
//  Init_spo2();

}
  

void HEART_BEAT_MONITOR()
{
   count=0;
   lcd.setCursor(0, 0);
   lcd.print("Place The Finger");
   lcd.setCursor(0, 1);
   lcd.print("to check HB");
   Serial.println("Place The Finger to check HB");
   delay(1000);
 // while(digitalRead(start)>0);
  
//   lcd.clear();
   temp=millis();
   
   while(millis()<(temp+5000))
   {
   
      if(analogRead(data)<100)
        {
         count=count+1;
         
         lcd.setCursor(6, 0);
         lcd.write(byte(1));
         lcd.setCursor(7, 0);
         lcd.write(byte(2));
         lcd.setCursor(8, 0);
         lcd.write(byte(3));
         lcd.setCursor(9, 0);
         lcd.write(byte(4));

         lcd.setCursor(6, 1);
         lcd.write(byte(5));
         lcd.setCursor(7, 1);
         lcd.write(byte(6));
         lcd.setCursor(8, 1);
         lcd.write(byte(7));
         lcd.setCursor(9, 1);
         lcd.write(byte(8));
         
         while(analogRead(data)<100);

         lcd.clear();
        }
   }
   
         lcd.clear();
         lcd.setCursor(0, 0);
           count=count*5;
         lcd.setCursor(2, 0);
         lcd.write(byte(1));
         lcd.setCursor(3, 0);
         lcd.write(byte(2));
         lcd.setCursor(4, 0);
         lcd.write(byte(3));
         lcd.setCursor(5, 0);
         lcd.write(byte(4));

         lcd.setCursor(2, 1);
         lcd.write(byte(5));
         lcd.setCursor(3, 1);
         lcd.write(byte(6));
         lcd.setCursor(4, 1);
         lcd.write(byte(7));
         lcd.setCursor(5, 1);
         lcd.write(byte(8));
         lcd.setCursor(7, 1);
         lcd.print(count);
         lcd.print(" BPM");
         temp=0;
//delay(1000);
       sprintf(mystr, "HB:%d", count);
       Serial.print("");
      Serial.print(mystr);
      Serial.println("");
      delay(1000);
Emergency();
}

void ECGCheck()
{
 if((digitalRead(2) == 1) || (digitalRead(4) == 1))
  { //check if leads are removed
      lcd.clear();
      lcd.print("Please Wear the");
      lcd.setCursor(0,1);
      lcd.print("ECG Electrodes");
      Serial.println("$Please Wear the ECG Electrodes#");    
      delay(1000);
     
  }
  else
  {
    ECG_val=analogRead(34);
    ECG_val = map(ECG_val, 0, 4095, 0, 1023);
    ECG_val=1023-ECG_val;
    Serial.print("ECG:");
     Serial.print(ECG_val);
     Serial.println("");
       lcd.clear();
      lcd.print("ECG:");
      lcd.print(ECG_val); 
      delay(1000);

      if((ECG_val>10)&&(ECG_val<500))
      {
        A=1;
      }
  }
  delay(1);
  Emergency();
 Init_spo2();

}
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define LED_RED 14
#define LED_GREEN 12
#define LED_BLUE 13

//Blynk variable inputs - start
int LED_PROFILE,LED_MODE,BLYNK_RED,BLYNK_GREEN,BLYNK_BLUE;
int animdelay = 1;
//Blynk variable inputs - end


//Auth Blynk - start
char auth[] = "auth";

char ssid[] = "ssid";
char pass[] = "pass";
//Auth Blynk - end


void setup()
{
  // Debug console & Leds mode inputs - start
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  // Debug console & Leds mode inputs - end
}

//Sync Blynk Signals - start

BLYNK_WRITE(V10) 
{
  BLYNK_RED = param.asInt();
  Serial.println(BLYNK_RED);
  
}

BLYNK_WRITE(V7) 
{
  animdelay = param.asInt();
  Serial.println(animdelay);
  
}

BLYNK_WRITE(V11) 
{
  BLYNK_GREEN = param.asInt();
  Serial.println(BLYNK_GREEN);
  
}

BLYNK_WRITE(V12) 
{
  BLYNK_BLUE = param.asInt();
  Serial.println(BLYNK_BLUE);
  
}

BLYNK_WRITE(V5) 
{
  LED_MODE = param.asInt();
  Serial.println(LED_MODE);
  
}

BLYNK_WRITE(V4)
{
  LED_PROFILE = param.asInt();
  Serial.println(LED_PROFILE);
  
}






//Sync Blynk Signals - end



void ledkapat(){ 
        analogWrite(LED_RED, 0);
        analogWrite(LED_GREEN, 0);
        analogWrite(LED_BLUE, 0);
  }


//Rgbwave effect - start

void rgbwave(){
   for(int i=0; i<255; i++){
        analogWrite(LED_RED, 255);
        analogWrite(LED_GREEN, 0);
        analogWrite(LED_BLUE, i);
        delay(animdelay);
        }
        
        Blynk.syncVirtual(V10,V11,V12,V5,V4);
        
       for(int i=255; i>0; i--){
        analogWrite(LED_RED, i);
        delay(animdelay);
        }
        Blynk.syncVirtual(V10,V11,V12,V5,V4);
        
       for(int i=0; i<255; i++){
        analogWrite(LED_RED, 0);
        analogWrite(LED_GREEN, i);
        analogWrite(LED_BLUE, 255);
        delay(animdelay);
        }
        Blynk.syncVirtual(V10,V11,V12,V5,V4);
       for(int i=255; i>0; i--){
        analogWrite(LED_BLUE, i);
        delay(animdelay);
        }
         Blynk.syncVirtual(V10,V11,V12,V5,V4);
       for(int i=0; i<255; i++){
        analogWrite(LED_RED, i);
        analogWrite(LED_GREEN, 255);
        analogWrite(LED_BLUE, 0);
        delay(animdelay);
       
        }
         Blynk.syncVirtual(V10,V11,V12,V5,V4);
       for(int i=255; i>0; i--){
        analogWrite(LED_GREEN, i);
        delay(animdelay);
        
        }
       Blynk.syncVirtual(V10,V11,V12,V5,V4);
  }

//Rgbwave effect - end


void hearteffect1(){
for(int i=25; i<255; i++){
        analogWrite(LED_RED, i);
        delay(2);
        }
  Blynk.syncVirtual(V10,V11,V12,V5,V4);
}

void hearteffect2(){
for(int i=255; i>25; i--){
        analogWrite(LED_RED, i);
        delay(2);
        }
      Blynk.syncVirtual(V10,V11,V12,V5,V4);
}


//heart effect - start
void hearteffect(){
      Blynk.syncVirtual(V10,V11,V12,V5,V4);
      analogWrite(LED_GREEN, 0);
      analogWrite(LED_BLUE, 0);
        
      hearteffect1();
      hearteffect2();
        
      
      hearteffect1();
      hearteffect2();
  
        delay(500);
  
      hearteffect1();
      hearteffect2();
        
      
      hearteffect1();
      hearteffect2();
        delay(500);
}

//heart effect - end



//randomlights - start
void randomlights(){
    int profil3delay;
        if(animdelay<4){profil3delay =4*10;}else {profil3delay = animdelay*10;}
       
        Blynk.syncVirtual(V10,V11,V12,V5,V4);
        analogWrite(LED_GREEN, 0);
        analogWrite(LED_BLUE, 0);
        analogWrite(LED_RED, 255);
        delay(profil3delay);
        analogWrite(LED_GREEN, 0);
        analogWrite(LED_BLUE, 0);
        analogWrite(LED_RED, 0);
        delay(profil3delay);
        Blynk.syncVirtual(V10,V11,V12,V5,V4);
        analogWrite(LED_RED, 0);
        analogWrite(LED_BLUE, 0);
        analogWrite(LED_GREEN, 255);
        delay(profil3delay);
        analogWrite(LED_GREEN, 0);
        analogWrite(LED_BLUE, 0);
        analogWrite(LED_RED, 0);
        delay(profil3delay);
        Blynk.syncVirtual(V10,V11,V12,V5,V4);
        analogWrite(LED_RED, 0);
        analogWrite(LED_GREEN, 0);
        analogWrite(LED_BLUE, 255);
        delay(profil3delay);
        ledkapat();
        delay(profil3delay);
  }
//randomlights - end



void loop(){
  Blynk.syncVirtual(V10,V11,V12,V5,V4);
  if(LED_MODE == 1){





    if(LED_PROFILE == 1){
      
      ledkapat();
      rgbwave();
      
      }else if(LED_PROFILE == 2){
       
      hearteffect();
        
      }else if(LED_PROFILE == 3){

      randomlights();
        
      }
    

    }else{
    analogWrite(LED_RED, BLYNK_RED);
    analogWrite(LED_GREEN, BLYNK_GREEN);
    analogWrite(LED_BLUE, BLYNK_BLUE);
      }
    
  Blynk.run();
}

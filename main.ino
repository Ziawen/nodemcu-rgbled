#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define LED_RED 14
#define LED_GREEN 12
#define LED_BLUE 13

//Blynk variable inputs
int POWER,BRIGHTNESS=1,LED_PROFILE, LED_MODE, BLYNK_RED, BLYNK_GREEN, BLYNK_BLUE;
int animdelay = 1;



//Auth Blynk
char auth[] = "";
char ssid[] = "";
char pass[] = "";



BlynkTimer timer;
void setup()
{
  // Debug console & Leds mode inputs & DataSync - start
  // Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);
  timer.setInterval(1000L, sensorDataSend); //timer will run every sec
}

//Sync Data
void sensorDataSend()
{
  Blynk.syncVirtual(V10, V11, V12, V3, V7, V6, V5, V4);
}




////////////////Sync Blynk Signals
BLYNK_WRITE(V10)
{
  BLYNK_RED = param.asInt();
  Serial.print("Red = ");
  Serial.print(BLYNK_RED);

}
BLYNK_WRITE(V11)
{
  BLYNK_GREEN = param.asInt();
  Serial.print(" Green = ");
  Serial.print(BLYNK_GREEN);

}
BLYNK_WRITE(V12)
{
  BLYNK_BLUE = param.asInt();
  Serial.print(" Blue = ");
  Serial.println(BLYNK_BLUE);

}
BLYNK_WRITE(V3)
{
  POWER = param.asInt();
  Serial.print("Power = ");
  Serial.println(POWER);
}
BLYNK_WRITE(V6)
{
  BRIGHTNESS = param.asInt();
  Serial.print("Brightness = ");
  Serial.println(BRIGHTNESS);
}
BLYNK_WRITE(V7)
{
  animdelay = param.asInt();
  Serial.print("Delay = ");
  Serial.println(animdelay);

}
BLYNK_WRITE(V5)
{
  LED_MODE = param.asInt();
  Serial.print("Mode = ");
  Serial.println(LED_MODE);

}
BLYNK_WRITE(V4)
{
  LED_PROFILE = param.asInt();
  Serial.print("Profile = ");
  Serial.println(LED_PROFILE);
  Serial.println(" ");
  Serial.println(" ");

}


////////////////Sync Blynk Signals - End



////////////////Effect Voids


void RGB(int R, int G, int B){
  int Rr = R/BRIGHTNESS;
  int Gr = G/BRIGHTNESS;
  int Br = B/BRIGHTNESS;
  analogWrite(LED_RED, Rr);
  analogWrite(LED_GREEN, Gr);
  analogWrite(LED_BLUE, Br);
  }
  



//Rgbwave effect - start
void rgbwave() {
  for (int i = 0; i < 255; i++) {
    RGB(255,0,i);
    delay(animdelay);
  }
  for (int i = 255; i > 0; i--) {
    RGB(i,0,255);
    delay(animdelay);
  }
  for (int i = 0; i < 255; i++) {
    RGB(0,i,255);
    delay(animdelay);
  }
  for (int i = 255; i > 0; i--) {
    RGB(0,255,i);
    delay(animdelay);
  }
  for (int i = 0; i < 255; i++) {
    RGB(i,255,0);
    delay(animdelay);
  }
  for (int i = 255; i > 0; i--) {
    RGB(255,i,0);
    delay(animdelay);
  }
}





//heart effect - start
void hearteffect1() {
  for (int i = 25; i < 255; i++) {
    RGB(i,0,0);
    delay(2);
  }


  for (int i = 255; i > 25; i--) {
    RGB(i,0,0);
    delay(2);
  }

}

void hearteffect() {
  RGB(0,0,0);
  hearteffect1();
  hearteffect1();
  delay(500);
  hearteffect1();
  hearteffect1();
  delay(500);
}





//randomlights - start
void randomlights() {
  int profil3delay;
  if (animdelay < 4) {
    profil3delay = 4 * 10;
  } else {
    profil3delay = animdelay * 10;
  }


  RGB(255,0,0);
  delay(profil3delay);
  RGB(0,0,0); // Turn Off Led
  delay(profil3delay);
  RGB(0,255,0);
  delay(profil3delay);
  RGB(0,0,0); // Turn Off Led
  delay(profil3delay);
  RGB(0,0,255);
  delay(profil3delay);
  RGB(0,0,0); // Turn Off Led
  delay(profil3delay);
}

//randomlightsv2 - start
void randomlightsv2() {
  int profil4delay;
  if (animdelay < 4) {
    profil4delay = 4 * 10;
  } else {
    profil4delay = animdelay * 10;
  }



  RGB(255,0,0);
  delay(profil4delay);
  RGB(0,0,0); // Turn Off Led
  delay(profil4delay);
  RGB(127,255,0);
  delay(profil4delay);
  RGB(0,0,0); // Turn Off Led
  delay(profil4delay);
  RGB(0,255,0);
  delay(profil4delay);
  RGB(0,0,0); // Turn Off Led
  delay(profil4delay);
  RGB(0,127,255);
  delay(profil4delay);
  RGB(0,0,0); // Turn Off Led
  delay(profil4delay);
  RGB(0,0,255);
  delay(profil4delay);
  RGB(0,0,0); // Turn Off Led
  delay(profil4delay);
  RGB(255,0,127);
  delay(profil4delay);
  RGB(0,0,0); // Turn Off Led
  delay(profil4delay);

}


//blink color effect - start
void blinkcolor() {

  int profile5delay;
  profile5delay = animdelay * 50;
  RGB(BLYNK_RED,BLYNK_GREEN,BLYNK_BLUE);
  delay(profile5delay);
  RGB(0,0,0); // Turn Off Led
  delay(profile5delay);
}


////////////////Effect Voids - End

void loop() {
  Blynk.run();
  timer.run();
  if (POWER == 0) {
    RGB(0,0,0); // Turn Off Led
  } else {

    if (LED_MODE == 1) {

      if (LED_PROFILE == 1) {

        RGB(0,0,0); // Turn Off Led
        rgbwave();

      } else if (LED_PROFILE == 2) {

        hearteffect();

      } else if (LED_PROFILE == 3) {

        randomlights();

      } else if (LED_PROFILE == 4) {

        randomlightsv2();
        
      } else if (LED_PROFILE == 5) {
        
        blinkcolor();
        
      }


    } else {
      RGB(BLYNK_RED,BLYNK_GREEN,BLYNK_BLUE);
    }

  }


}

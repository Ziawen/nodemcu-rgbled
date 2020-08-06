#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define LED_RED 14
#define LED_GREEN 12
#define LED_BLUE 13

//Blynk variable inputs
int POWER, LED_PROFILE, LED_MODE, BLYNK_RED, BLYNK_GREEN, BLYNK_BLUE;
int animdelay = 1;



//Auth Blynk
char auth[] = "bxY96_vZYUoiW5kUyehyV8Ou8XOk5VOx";
char ssid[] = "SEBILCI";
char pass[] = "a8fe7bc4";


BlynkTimer timer;
void setup()
{
  // Debug console & Leds mode inputs & DataSync - start
  Serial.begin(9600);
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
  Blynk.syncVirtual(V10, V11, V12, V3, V7, V5, V4);
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


void ledkapat() {
  analogWrite(LED_RED, 0);
  analogWrite(LED_GREEN, 0);
  analogWrite(LED_BLUE, 0);
}


//Rgbwave effect - start

void rgbwave() {
  for (int i = 0; i < 255; i++) {
    analogWrite(LED_RED, 255);
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_BLUE, i);
    delay(animdelay);
  }



  for (int i = 255; i > 0; i--) {
    analogWrite(LED_RED, i);
    delay(animdelay);
  }


  for (int i = 0; i < 255; i++) {
    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, i);
    analogWrite(LED_BLUE, 255);
    delay(animdelay);
  }

  for (int i = 255; i > 0; i--) {
    analogWrite(LED_BLUE, i);
    delay(animdelay);
  }

  for (int i = 0; i < 255; i++) {
    analogWrite(LED_RED, i);
    analogWrite(LED_GREEN, 255);
    analogWrite(LED_BLUE, 0);
    delay(animdelay);

  }

  for (int i = 255; i > 0; i--) {
    analogWrite(LED_GREEN, i);
    delay(animdelay);

  }

}

//Rgbwave effect - end


void hearteffect1() {
  for (int i = 25; i < 255; i++) {
    analogWrite(LED_RED, i);
    delay(2);
  }


  for (int i = 255; i > 25; i--) {
    analogWrite(LED_RED, i);
    delay(2);
  }

}




//heart effect - start
void hearteffect() {
  analogWrite(LED_GREEN, 0);
  analogWrite(LED_BLUE, 0);
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


  analogWrite(LED_GREEN, 0);
  analogWrite(LED_BLUE, 0);
  analogWrite(LED_RED, 255);

  delay(profil3delay);
  ledkapat();
  delay(profil3delay);

  analogWrite(LED_RED, 0);
  analogWrite(LED_BLUE, 0);
  analogWrite(LED_GREEN, 255);

  delay(profil3delay);
  ledkapat();
  delay(profil3delay);

  analogWrite(LED_RED, 0);
  analogWrite(LED_GREEN, 0);
  analogWrite(LED_BLUE, 255);

  delay(profil3delay);
  ledkapat();
  delay(profil3delay);
}


//blink color effect - start
void blinkcolor() {

  int profile4delay;
  profile4delay = animdelay * 50;
  analogWrite(LED_RED, BLYNK_RED);
  analogWrite(LED_GREEN, BLYNK_GREEN);
  analogWrite(LED_BLUE, BLYNK_BLUE);
  delay(profile4delay);
  ledkapat();
  delay(profile4delay);
}


////////////////Effect Voids - End

void loop() {
  Blynk.run();
  timer.run();
  if (POWER == 0) {
    ledkapat();
  } else {

    if (LED_MODE == 1) {

      if (LED_PROFILE == 1) {

        ledkapat();
        rgbwave();

      } else if (LED_PROFILE == 2) {

        hearteffect();

      } else if (LED_PROFILE == 3) {

        randomlights();

      } else if (LED_PROFILE == 4) {

        blinkcolor();

      }


    } else {
      analogWrite(LED_RED, BLYNK_RED);
      analogWrite(LED_GREEN, BLYNK_GREEN);
      analogWrite(LED_BLUE, BLYNK_BLUE);
    }

  }


}

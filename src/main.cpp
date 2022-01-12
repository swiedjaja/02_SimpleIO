// ESP32Cam: SDA = 21; SCL = 22;
// Program function: press Switch to reset the counter, led flash will blink 2 times
// problem: switch not always respons, how to overcome this problem?
#include <Arduino.h>
#if defined(ESP8266)
  #define LED_RED    D8
  #define LED_YELLOW D7
  #define LED_GREEN  D6
  #define PIN_SW     D5
#elif defined(ESP32)
  #if !defined(LED_BUILTIN) // ESP32Cam
    #define LED_BUILTIN 33
  #endif
  #define LED_FLASH 4
  #define LED_RED    15
  #define LED_YELLOW 14
  #define LED_GREEN   2
  #define PIN_SW      0
#endif

#define LED_BUILTIN_ON  0
#define LED_BUILTIN_OFF 1

#define LED_ON  1
#define LED_OFF 0

const uint8_t arLed[3] = {LED_RED, LED_YELLOW, LED_GREEN};
int nCount = 0;
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  #if defined(LED_FLASH)    
    pinMode(LED_FLASH, OUTPUT);
  #endif    
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(PIN_SW, INPUT);

  Serial.println("System ready...");
}

void loop() {
  if (digitalRead(PIN_SW)==0)
  {
  #if defined(LED_FLASH)    
    for (uint8_t i=0; i<2; i++)
    {
      digitalWrite(LED_FLASH, LED_ON);
      delay(3);
      digitalWrite(LED_FLASH, LED_OFF);
      delay(200);
    }
  #endif
    nCount=0;
  }
  Serial.printf("Hello World %d\n", nCount);
  digitalWrite(arLed[nCount%3], LED_ON);
  digitalWrite(LED_BUILTIN, LED_BUILTIN_ON);
  delay(100);
  digitalWrite(arLed[nCount%3], LED_OFF);
  digitalWrite(LED_BUILTIN, LED_BUILTIN_OFF);
  delay(900);
  nCount++;
}
#include <Keyboard.h>
#define LED_PIN 2
#define KEY_PIN 9
#define DEBOUNCE_TIME 5
#define KEY_LOCKOUT 500
void setup(){
  pinMode(LED_PIN, OUTPUT);
  pinMode(KEY_PIN, INPUT_PULLUP);
  while ( digitalRead(KEY_PIN) != LOW ){}
  Keyboard.begin();
}

void loop(){
  if (readForKey()){
    int timeStarted = millis();
    int character = 65;
    while ( timeElapsed(timeStarted) < KEY_LOCKOUT ){
      if (character > 127){
        character = 0;
      }
      if (readForKey()){
        timeStarted = millis();
        character ++;
      }
    }
    Keyboard.write(character);
  }
}
bool readForKey(){
  if (digitalRead(KEY_PIN) == LOW){
    delay(DEBOUNCE_TIME);
    while(digitalRead(KEY_PIN) == LOW){
      digitalWrite(LED_PIN, HIGH);
    }
    delay(DEBOUNCE_TIME);
    digitalWrite(LED_PIN, LOW);
    return true;
  }else{
    return false;
  }
  
}
int timeElapsed(int timestarted){
  return millis() - timestarted;
}

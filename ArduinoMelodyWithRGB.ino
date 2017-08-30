#include "pitches.h"

#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10
#define REDPin 6
#define GREENPin 3
#define BLUEPin 5

// transcript by Changcheng Fu
// "Summer"
int melody[] = {
 NOTE_B2, NOTE_FS3, NOTE_B3, NOTE_FS3, NOTE_G2, NOTE_D3, NOTE_G3,NOTE_D3,NOTE_A2,NOTE_E3,NOTE_A3,NOTE_E3,NOTE_D3,NOTE_A3,NOTE_D4,NOTE_A3,NOTE_B2, NOTE_FS3, NOTE_B3, NOTE_FS3, NOTE_G2, NOTE_D3, NOTE_G3,NOTE_D3,NOTE_A2,NOTE_E3,NOTE_A3,NOTE_E3,NOTE_D3,NOTE_A3,NOTE_A4,NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_D5,NOTE_D5,NOTE_A4,NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_FS5,NOTE_A4,NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_D5,NOTE_D5,NOTE_A4,NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_D5,NOTE_E5,NOTE_A5,NOTE_FS5,NOTE_FS5,NOTE_G5,NOTE_A5,NOTE_A5,NOTE_A5,NOTE_A5,NOTE_A5,NOTE_FS5,NOTE_D5,NOTE_FS5,NOTE_G5,NOTE_A5,NOTE_A5,NOTE_A5,NOTE_A5,NOTE_A5,NOTE_FS5,NOTE_D5,
NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_FS5,NOTE_FS5,NOTE_FS5,NOTE_FS5,NOTE_B5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_D5,NOTE_E5
};
int noteDurations[] = {
8,8,8,8,8,8,
8,8,8,8,8,8,
8,8,8,8,8,8,
8,8,8,8,8,8,
8,8,8,8,8,8,16,16,16,16,8,16,2,16,16,16,16,8,16,6,8
,4,16,16,16,16,8,16,2,16,16,16,16,8,16,6,8,4,8,8,8,16,6,8,8,16,6,16,16,8,16,6,8,8,16,6,16,16,8,16,6,8,8,8,32,32,32,32,4
};

void playSong(){
  int brightness = 255;
int increment = 5; 
  for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(int); thisNote++) {
  

  if (brightness <= 0 || brightness > 255)    // reverse the direction of the fading
  {
    increment = -increment;
  }
 brightness = brightness + increment;  // increment brightness for next loop iteration
  analogWrite(REDPin, brightness);
  analogWrite(GREENPin, brightness);
  analogWrite(BLUEPin, brightness);
  Serial.println(brightness);
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 3000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
  delay(1000);
}

//void RGB() {
//  
//  brightness = brightness + increment;  // increment brightness for next loop iteration
//
//  if (brightness <= 0 || brightness >= 255)    // reverse the direction of the fading
//  {
//    increment = -increment;
//  }
//  brightness = constrain(brightness, 0, 255);
//  analogWrite(REDPin, brightness);
//  analogWrite(GREENPin, brightness);
//  analogWrite(BLUEPin, brightness);
//
//  delay(20);  // wait for 20 milliseconds to see the dimming effect
//}

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(REDPin, OUTPUT);
  pinMode(GREENPin, OUTPUT);
  pinMode(BLUEPin, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 75) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite(led2,LOW);
    playSong();
  analogWrite(REDPin, 0);
  analogWrite(GREENPin, 0);
  analogWrite(BLUEPin, 0);

  }
  else {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}

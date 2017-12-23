#include <Adafruit_Circuit_Playground.h>
#include "pitches.h"

/*
 * Ethan Schwartz; ethanms@ethanms.com; Dec/23/2017
 * 
 * This is largely based on "The Sound of Music" example code from Adafruit 
 * ...which was located here:
 * https://learn.adafruit.com/circuit-playground-music/the-sound-of-music
 * 
 * Jingle Bell melody is from public domain
 * 
 */

// lower is slower, higher is faster... 2 is about right
const int speed = 2;

// brightness of the Neopixels... for my eyes brighter red looks more even with green
const int green = 75;
const int red   = 125;

const int numNotes = 26;

// Jingle Bells!
int melody[] = {                          
  NOTE_B4, NOTE_B4, NOTE_B4, 
  NOTE_B4, NOTE_B4, NOTE_B4,
  NOTE_B4, NOTE_D5, NOTE_G4, NOTE_A4,
  NOTE_B4, 0,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, 
  NOTE_C5, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, 
  NOTE_D5, NOTE_D5, NOTE_C5, NOTE_A4, 
  NOTE_G4};

// Durations... 8 = 1/8, 4 = 1/4, 3 = ~3/8, 2 = 1/2, 1 = Full
int noteDurations[] = {    
  4, 4, 2, 
  4, 4, 2, 
  4, 4, 3, 8,
  1, 4,
  4, 4, 3, 8, 
  4, 4, 4, 8, 8,
  4, 4, 4, 4, 
  1
  };

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(100);
}

void loop() {
  for (int p = 0; p < 10; p++){
    CircuitPlayground.setPixelColor(p, 0, 0, 0);
  }
  
  if(CircuitPlayground.rightButton()) {   // play when we press the right button
    for (int thisNote = 0; thisNote < numNotes; thisNote++) { // play notes of the melody
      if (melody[thisNote] != 0){
        if (thisNote % 2){
          for (int p = 0; p <= 8; p=p+2){
            CircuitPlayground.setPixelColor(p, red, 0, 0);
            CircuitPlayground.setPixelColor(p+1, 0, green, 0);
          }
        }
        else{
          for (int p = 0; p <= 8; p=p+2){
            CircuitPlayground.setPixelColor(p, 0, green, 0);
            CircuitPlayground.setPixelColor(p+1, red, 0, 0);
          }
        }
      }
      
      int noteDuration = (1000 / speed) / noteDurations[thisNote];
      CircuitPlayground.playTone(melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    }
  }
}

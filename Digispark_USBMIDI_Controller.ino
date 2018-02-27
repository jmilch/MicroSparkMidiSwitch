#include <DigiMIDI.h>

DigiMIDIDevice midi;

int const numDigPinsCC = 4; // number of digital pins to send CC
int currentDigcc[numDigPinsCC]; //+1 for double switch
int digitalpincc[] = {
   0,1,2,5 // which digital pins to use for sending CC
};
int digInputcc[numDigPinsCC];




// the MIDI channel number to send messages
const int channel = 1;



void setup() {
    for (int i = 0; i < numDigPinsCC; i++) {
    pinMode(digitalpincc[i], INPUT);
}
 

  Serial.begin(38400);

}

void loop() {
  // put your main code here, to run repeatedly:
// digital pins sending CC

  for (int i = 0; i < numDigPinsCC; i++) {
    if (digitalRead(digitalpincc[i]) == 1 && currentDigcc[i] == 0) {
      midi.sendControlChange(i+50, 127, channel); 
      currentDigcc[i] = 1;
    }  
    if (digitalRead(digitalpincc[i]) == 0  && currentDigcc[i] == 1) {
      midi.sendControlChange(i+50, 0, channel);
      currentDigcc[i] = 0;
    }  
  }
 
}

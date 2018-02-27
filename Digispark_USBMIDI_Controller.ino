#include <DigiMIDI.h>
#include <Bounce2.h>

DigiMIDIDevice midi;
#define BUTTON_PIN_0 0
#define BUTTON_PIN_1 1
#define BUTTON_PIN_2 2
#define BUTTON_PIN_5 5

Bounce debouncer0 = Bounce(); 
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer5 = Bounce(); 

int const numDigPinsCC = 4; // number of digital pins to send CC
int currentDigcc[numDigPinsCC]; //+1 for double switch
int digitalpincc[] = {
   0,1,2,5 // which digital pins to use for sending CC
};
int digInputcc[numDigPinsCC];
int value[] = {0, 0, 0, 0};




// the MIDI channel number to send messages
const int channel = 1;



void setup() {
    for (int i = 0; i < numDigPinsCC; i++) {
    pinMode(digitalpincc[i], INPUT);
    digitalWrite(digitalpincc[i],HIGH);
}
  debouncer0.attach(BUTTON_PIN_0);
  debouncer0.interval(5); // interval in ms
  debouncer1.attach(BUTTON_PIN_1);
  debouncer1.interval(5); // interval in ms
  debouncer2.attach(BUTTON_PIN_2);
  debouncer2.interval(5); // interval in ms
  debouncer5.attach(BUTTON_PIN_5);
  debouncer5.interval(5); // interval in ms

  Serial.begin(38400);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Update the Bounce instances :
  debouncer0.update();
  debouncer1.update();
  debouncer2.update();
  debouncer5.update();

  // Get the updated value :
  value[0] = debouncer0.read();
  value[1] = debouncer1.read();
  value[2] = debouncer2.read();
  value[3] = debouncer5.read();
   
   
   // digital pins sending CC

  for (int i = 0; i < numDigPinsCC; i++) {
    if (value[i] == 1 && currentDigcc[i] == 0) {
      midi.sendControlChange(i+50, 127, channel); 
      currentDigcc[i] = 1;
    }  
    if (value[i] == 0  && currentDigcc[i] == 1) {
      midi.sendControlChange(i+50, 0, channel);
      currentDigcc[i] = 0;
    }  
  }
 
}

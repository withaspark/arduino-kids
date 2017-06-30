#include "pitches.h"

// PITCH SHORTCUTS
#define P1 NOTE_C4
#define P2 NOTE_D4
#define P3 NOTE_E4
#define P4 NOTE_F4
#define P5 NOTE_G4
#define P6 NOTE_A5
#define P7 NOTE_B5
#define P8 NOTE_C5
#define P9 NOTE_D5
#define P10 NOTE_E5
#define P11 NOTE_F5
#define P12 NOTE_G5
#define P13 NOTE_A6

//
// I/O
//

// DIs
const int PIN_BUTTON_BUZZER = 2;
const int PIN_BUTTON_BLUE = 3;
const int PIN_BUTTON_GREEN = 4;

// DOs
const int PIN_BUZZER = 8;
const int PIN_LIGHT_BLUE = 10;
const int PIN_LIGHT_GREEN = 11;
const int PIN_LIGHT_ONBD = 13;

//
// Songs
//

// Charge!
const int note_melody[] = { P1, P3, P5, P8, 0, P5, P8, 0 };
const int note_durations[] = { 8, 8, 8, 8, 16, 8, 2, 2 };

// Ring
const int ring_melody[] = {
  NOTE_E7, NOTE_C7, NOTE_E7, NOTE_C7, NOTE_E7, NOTE_C7, 0,
  NOTE_E7, NOTE_C7, NOTE_E7, NOTE_C7, NOTE_E7, NOTE_C7, 0,
  NOTE_E7, NOTE_C7, NOTE_E7, NOTE_C7, NOTE_E7, NOTE_C7, 0,
//  NOTE_D8, NOTE_D8, NOTE_D8
};
const int ring_durations[] = {
  12, 12, 12, 12, 12, 12, 1,
  12, 12, 12, 12, 12, 12, 1,
  12, 12, 12, 12, 12, 12, 1,
//  1, 1, 1
};

// Mary Had a Little Lamb
const int mary_had_a_little_lamb_melody[] = {
  //                                 |                                   |                                   |
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4,       0, NOTE_D4, NOTE_D4, NOTE_D4,       0, NOTE_E4, NOTE_G4, NOTE_G4,      0,
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4,       0,       0,      0
};
const int mary_had_a_little_lamb_durations[] = {
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
};

// Amazing Grace
const int amazing_grace_melody[] = {
   0, P1, P4, P6, P4,
  P6, P5, P4, P2,
  P1, P1, P4, P6, P4,
  P6, P5, P8,
//   0, P6, P8, P6,
//  P4, P1, P2, P4, P4, P2,
//  P1, P1, P4, P6, P4,
//  P6, P5, P4, 0
};
const int amazing_grace_durations[] = {
  12, 6, 3, 12, 12,
  3, 6, 3, 6,
  3, 6, 3, 12, 12,
  3, 6, 2,
//  3, 6, 3, 6,
//  3, 6, 4, 12, 12, 12,
//  3, 6, 3, 12, 12,
//  3, 6, 3, 6
};

void setup() {
  Serial.begin(9600);

  pinMode(PIN_BUTTON_BUZZER, INPUT_PULLUP);
  pinMode(PIN_BUTTON_BLUE, INPUT_PULLUP);
  pinMode(PIN_BUTTON_GREEN, INPUT_PULLUP);
  pinMode(PIN_LIGHT_BLUE, OUTPUT);
  pinMode(PIN_LIGHT_GREEN, OUTPUT);
  pinMode(PIN_LIGHT_ONBD, OUTPUT);
  digitalWrite(PIN_LIGHT_ONBD, LOW);

  int numNotes = sizeof(note_melody) / sizeof(int);
  playSong(numNotes, note_melody, note_durations, 1000, 300);
}

void loop() {
  if (digitalRead(PIN_BUTTON_BLUE) == LOW && digitalRead(PIN_BUTTON_GREEN) == LOW) {
    Serial.println("BUTTON_BLUE AND BUTTON_GREEN PRESSED");
    digitalWrite(PIN_LIGHT_BLUE, HIGH);
    digitalWrite(PIN_LIGHT_GREEN, HIGH);
    
    int numNotes = sizeof(ring_melody) / sizeof(int);
    playSong(numNotes, ring_melody, ring_durations, 1000, 10);
    return;
  }
  
  if (digitalRead(PIN_BUTTON_BLUE) == HIGH) {
    digitalWrite(PIN_LIGHT_BLUE, LOW);
  } else {
    Serial.println("BUTTON_BLUE PRESSED");
    for (int i = 0; i < 5; i++) {
      digitalWrite(PIN_LIGHT_BLUE, HIGH);
      delay(200);
      digitalWrite(PIN_LIGHT_BLUE, LOW);
      delay(100);
    }
  }
  
  if (digitalRead(PIN_BUTTON_GREEN) == HIGH) {
    digitalWrite(PIN_LIGHT_GREEN, LOW);
  } else {
    Serial.println("BUTTON_GREEN PRESSED");
    digitalWrite(PIN_LIGHT_GREEN, HIGH);
    
    int numNotes = sizeof(amazing_grace_melody) / sizeof(int);
    playSong(numNotes, amazing_grace_melody, amazing_grace_durations, 5000, 300);
  }
  
  if (digitalRead(PIN_BUTTON_BUZZER) == LOW) {
    Serial.println("BUTTON_BUZZER PRESSED");

    int numNotes = sizeof(mary_had_a_little_lamb_melody) / sizeof(int);
    playSong(numNotes, mary_had_a_little_lamb_melody, mary_had_a_little_lamb_durations, 1000, 300);
  }
}

void playSong(int numNotes, const int* notes, const int* durations, int tempo, float spacing) {
  char message[50];
  
  sprintf(message, "Playing song with %d notes\n", numNotes);
  Serial.println(message);
  
  for (int i = 0; i < numNotes; i++) {
    int duration = tempo / durations[i];
    int pause = duration * (1.0 + (spacing / 1000.0));
    
    tone(PIN_BUZZER, notes[i], duration);
    delay(pause);
    noTone(PIN_BUZZER);

    if (digitalRead(PIN_BUTTON_BLUE) == LOW && digitalRead(PIN_BUTTON_GREEN) == LOW) {
      break;
    }
  }
}


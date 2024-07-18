/******************************************************************/
/*RGB 5-tone Keyboard Project
For use in Intermediate Arduino Workshop
By Stephen R Grenesko*/
/******************************************************************/

//VARIABLE AND DATA DECLARATIONS
const int blue = 12, yellow = 9, green = 10, red = 11, pink = 8,rLED = 6, gLED = 4, bLED = 3 ,buzz = 2;// Assigning Arduino pins for hardware control
int notes[] = {262, 294, 330, 349, 392};// An array of values, each value corresponds to a note
int RGB[][3] = {{0, 0, 255},   // Red (inverted)
                {0, 255, 0},   // Green
                {255, 0, 0},   // Blue (inverted)
                {255, 255, 0}, // Yellow
                {255, 0, 255}}; // Pink
int currentNote = -1;
const int debounceDelay = 80; // debounce delay in milliseconds

//MAIN SETUP FUNCTION FOR PIN SETTING AND FUN STARTUP SEQUENCE
void setup() {
  Serial.begin(9600);//This is for serial porting, kinda complicated not important

  pinMode(buzz, OUTPUT);//Output pin for buzzer
  pinMode(rLED, OUTPUT);//Output pins for LED
  pinMode(gLED, OUTPUT);
  pinMode(bLED, OUTPUT);

  pinMode(blue, INPUT_PULLUP);//Sets these pins to an input, does other stuff but that is also kind of complicated so don't worry
  pinMode(green, INPUT_PULLUP);
  pinMode(red, INPUT_PULLUP);
  pinMode(yellow, INPUT_PULLUP);
  pinMode(pink, INPUT_PULLUP);
  

  // Play initial sequence startup, basically a rising note scale
  for (int i = 0; i < 5; i++)//For loop control flow! {
    tone(buzz, notes[i]);//Plays the tone at location i in the array of notes
    delay(500);// delays by 500ms
    noToneAndResetColor(); // Reset color after each note
    delay(50);
  }
}

//MAIN LOOPING FUNCTION FOR DETECTING BUTTON PUSHES AND OUTPUTS NOTE AND LIGHT
void loop() {

  //Control flow logic for detecting button presses, if a button is pressed, play a note, make the LED a color!
  if (digitalRead(blue) == LOW) {
    playNoteWithColor(0);
  } else if (digitalRead(yellow) == LOW) {
    playNoteWithColor(1);
  } else if (digitalRead(green) == LOW) {
    playNoteWithColor(2);
  } else if (digitalRead(red) == LOW) {
    playNoteWithColor(3);
  } else if (digitalRead(pink)== LOW){
    playNoteWithColor(4);
  }else {
    noToneAndResetColor(); // Stop the tone and reset color if no button is pressed
  }
}

//CUSTOM FUNCTION FOR CREATING THE COLORS
void playNoteWithColor(int noteIndex) {
  if (currentNote != noteIndex) {
    currentNote = noteIndex;
    analogWrite(rLED, 255 - RGB[noteIndex][0]); // Invert value for common cathode
    analogWrite(gLED, 255 - RGB[noteIndex][1]); // Green remains same
    analogWrite(bLED, 255 - RGB[noteIndex][2]); // Invert value for common cathode
    tone(buzz, notes[noteIndex]);
    delay(debounceDelay); // delay for debouncing
  }
}

//CUSTOM FUNCTION 
void noToneAndResetColor() {
  noTone(buzz); // Stop the tone
  analogWrite(rLED, 255); // Turn off all RGB LEDs (255 means off for common cathode)
  analogWrite(gLED, 255);
  analogWrite(bLED, 255);
  currentNote = -1;
}

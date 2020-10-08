const int buttonPin = 2; //pin that we're assigning to the button, doesn't ever change
int curlight = 9;
int direction = -1;
bool winable = false;
float speed = 100; //the time that the system takes between changing lights
unsigned long lastTime = millis(); //starts the time from which we will determine lighting timing
//float and unsigned long are both variables to hold numbers. In general you should use floats
 
void setup() { //Things that we only need to do once at the beginning
  for (int i = 7; i <= 13; i++) {//Constructs an iterator from 7 to 13
      pinMode(i, OUTPUT); //sets each pin to output mode
    }
  randomSeed(analogRead(0)); //sets up the random number generator. A seed is the root from which numbers are generated
  speed *= random(1, 4); //the time that the system takes between changing lights
  pinMode(buttonPin, INPUT_PULLUP); //tells the computer that pin 2 is being used as an input
  Serial.begin(9600); //not necessary, inits serial communication with the computer
  Serial.println(speed); //tells the computer what the selected speed is
}

void loop() { //repeats forever
  if (digitalRead(buttonPin) == LOW) { //checks if the button is pressed
    end(); //tells the computer to jump to void end() at the bottom (executing all the code therein)
  }
  if (millis() - lastTime >= speed) { //checks if it's time to update lights
    if (updateLights() == 11) { //calls update lights function and compares the return value
      winable = true;
    }
    else {
      winable = false;
    }
    lastTime = millis(); //resets timer
  }
}

int updateLights() { //this is a function that returns an integer as compared to void which returns nothing
  if (curlight == 9 || curlight == 13) { //makes the lights 'bounce' rather than iterating up forever
    direction = direction * -1;
  }
  curlight = curlight + direction; //applies the direction to the currently selected light
  for (int i = 9; i <= 13; i++) { //turns all lights off
    digitalWrite(i, LOW);
  }
  digitalWrite(curlight, HIGH); //turns on the light selected at the top of the function
  return curlight; //tells the main loop the current light that is lit
}

void end() {
  if (winable){
    Serial.println("Win!");
    digitalWrite(8, HIGH); //turn on green light
    digitalWrite(7, LOW);} //make sure red light is off
  else{
    Serial.println("Loss!");
    digitalWrite(8, LOW);   //turn on red light
    digitalWrite(7, HIGH);} //make sure green light is off
    while (true){} //do nothing forever (requires a board reset to play again)
}

const int buttonPin = 2; //pin that we're assigning to the button, doesn't ever change
int curlight = 9;
int direction = -1;
bool winable = false;
float speed = 100; //the time that the system takes between changing lights
unsigned long lastTime = millis(); //starts the time from which we will determine lighting timing

void setup() { //Things that we only need to do once at the beginning
  for (int i = 7; i <= 13; i++) {//tells the computer that pin 11 is being used and that it is an output
      pinMode(i, OUTPUT);
    }
  randomSeed(analogRead(0)); //sets up the random number generator. A seed is the root from which numbers are generated
  speed *= random(1, 4); //the time that the system takes between changing lights
  pinMode(buttonPin, INPUT_PULLUP); //tells the computer that pin 2 is being used as an input
  Serial.begin(9600);
  Serial.println(speed);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { //checks if the button is pressed when a win is possible
    end(); //tells the computer to jump to void win() at the bottom
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

int updateLights() {
  if (curlight == 9 || curlight == 13) { //makes the lights 'bounce' rather than going on forever
    direction = direction * -1;
  }
  curlight = curlight + direction;
  for (int i = 9; i <= 13; i++) { //turns all lights off
    digitalWrite(i, LOW);
  }
  digitalWrite(curlight, HIGH); //turns on the light selected at the top of the function
  return curlight; //tells the main loop the current light that is lit
}

void end() {
  if (winable){
    Serial.println("Win!");
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);}
  else{
    Serial.println("Loss!");
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);}
    while (true){}
}

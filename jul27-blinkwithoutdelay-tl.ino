// INPUT BUTTONS

int redBtn = 2;
int blinkBtn = 4;

int whiteBtn = 5;
int whiteBlinkBtn = 7;


// VARS FOR CONSTANT MODE

int reading;   
int previous = LOW; 
int state = LOW;

int whiteReading;   
int whitePrevious = LOW; 
int whiteState = LOW;

// VARS FOR BLINKING MODE

unsigned long mainTimer = 0; 
unsigned long ledTimer = 0;
boolean setMode = false;  

unsigned long mainWhiteTimer = 0; 
unsigned long ledWhiteTimer = 0;
boolean setWhiteMode = false;  

// RED LEDS

const int redPin1 = 10;       
const int redPin2 = 11; 

// WHITE LEDS

const int whitePin1 = 9; 

long time = 0; 
long debounce = 200; 

void setup() {
  pinMode(redBtn, INPUT); 
  pinMode(blinkBtn, INPUT); 
  pinMode(redPin1, OUTPUT);
  pinMode(redPin2, OUTPUT);

  pinMode(whiteBtn, INPUT); 
  pinMode(whitePin1, OUTPUT);
  
}

void loop() {

// red pin blink  
  if ((millis() - mainTimer) >= 200UL) {
    if ((digitalRead(blinkBtn) == HIGH)) {
      if (setMode == false) {
        setMode = true;
        ledTimer = millis();
      }
      else if (setMode == true) {
        setMode = false;
      }
      mainTimer = millis();
    }
  }

  if (setMode == true) {
    if ((millis() - ledTimer) <= (1024UL - analogRead(A0))) {
      digitalWrite(redPin1, HIGH); 
      digitalWrite(redPin2, HIGH); 
    }
    else if ((millis() - ledTimer) <= 2*(1024UL - analogRead(A0))) {
      digitalWrite(redPin1, LOW);
      digitalWrite(redPin2, LOW); 
    }
    else {
      ledTimer = millis();
    }
  }
  else {
    digitalWrite(redPin1, LOW);
    digitalWrite(redPin2, LOW); 
  }


// white pin blink  
  if ((millis() - mainTimer) >= 200UL) {
    if ((digitalRead(whiteBlinkBtn) == HIGH)) {
      if (setWhiteMode == false) {
        setWhiteMode = true;
        ledWhiteTimer = millis();
      }
      else if (setWhiteMode == true) {
        setWhiteMode = false;
      }
      mainWhiteTimer = millis();
    }
  }

  if (setWhiteMode == true) {
    if ((millis() - ledWhiteTimer) <= (1024UL - analogRead(A0))) {
      digitalWrite(whitePin1, HIGH); 
    }
    else if ((millis() - ledWhiteTimer) <= 2*(1024UL - analogRead(A0))) {
      digitalWrite(whitePin1, LOW);
    }
    else {
      ledWhiteTimer = millis();
    }
  }
  else {
    digitalWrite(whitePin1, LOW);
  }

// red pin

  reading = digitalRead(redBtn);
  
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();    
  }

  digitalWrite(redPin1, state);
  digitalWrite(redPin2, state);

  previous = reading;


// white pin

whiteReading = digitalRead(whiteBtn);
  
  if (whiteReading == HIGH && whitePrevious == LOW && millis() - time > debounce) {
    if (whiteState == HIGH)
      whiteState = LOW;
    else
      whiteState = HIGH;

    time = millis();    
  }

  digitalWrite(whitePin1, whiteState);

  whitePrevious = whiteReading;

}

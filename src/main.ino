unsigned long currentTime;
unsigned long targetTime;
unsigned long startTime;
unsigned long readInterval;
unsigned long readTime;
String inputString = "";
boolean stringComplete = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  inputString.reserve(400);
  
  readInterval = 1000;
  readTime = 0;
}

void loop() {
  currentTime = millis();
  
  if(currentTime-readTime >= readInterval){
    //readADC
    long randNumber = random(0, 1023);
    Serial.print("^A");
    Serial.println(randNumber);
    readTime = currentTime;
  }
  
  if (stringComplete) {
    if(currentTime-startTime >= targetTime){
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("^D");
      inputString = "";
      stringComplete = false;
    }
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      digitalWrite(LED_BUILTIN, HIGH);
      targetTime = inputString.toInt();
      startTime = millis();
      stringComplete = true;
    }
  }
}

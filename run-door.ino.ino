#define pc 0 // the cell and 10k pull-down resistor are connected to analog 0
#define enA 1
#define in1 0
#define in2 1

int photocellReading;
int lightThreshold = 1000;
int rotationDirection = 1;
int totalLength = 100;
int currentPosition = 0;
int maxPwmOutput = 255; //50% rotation speed

void setup() {
  Serial.begin(9600); //Enable debug output in console
  pinMode(LED_BUILTIN, OUTPUT); //Get ready to use the built-in led to indicate light/dark status
  pinMode(enA, OUTPUT);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  //Set motor's initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void loop() {
  photocellReading = analogRead(pc);
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);
  
  //Set rotation direction based on light level and set LED status as a helper
  if(photocellReading > lightThreshold) {
    Serial.println("lighting up led");
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    rotationDirection = 1;
  }else{
    Serial.println("shutting off led");
    digitalWrite(LED_BUILTIN, LOW);    
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    rotationDirection = -1;
  }
  Serial.print("Current position = ");
  Serial.println(currentPosition);
  Serial.print("Total length = ");
  Serial.println(totalLength);
  Serial.print("Rotation direction = ");
  Serial.println(rotationDirection);
  int pwmOutput = 0;
  if((currentPosition < totalLength && rotationDirection == 1) || (currentPosition > 0 && rotationDirection == -1)) {
    currentPosition += rotationDirection;
    pwmOutput = maxPwmOutput;
  }
    Serial.print("Sending output voltage to enA of ");
    Serial.println(pwmOutput);
  analogWrite(enA, pwmOutput);    
  delay(100);
}

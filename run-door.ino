// the photocell and 10k pull-down resistor that make up the light sensor
#define pc 0
// optional - If you connect enA or enB on the motor controller,
//            you can use maxPwmOutput to control the speed of the motor
#define enB 4
// in1/in2 or in3/in4 on the motor controller.  These control the direction
// of the motor's spin
#define in3 13
#define in4 14
int photocellReading;
int lightThreshold = 1000;
int rotationDirection = 1;
int totalLength = 100;
int currentPosition = 0;
int maxPwmOutput = 255; //50% rotation speed
void setup() {
  Serial.begin(9600); //Enable debug output in console
  pinMode(LED_BUILTIN, OUTPUT); //Get ready to use the built-in led to indicate light/dark status
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //Set motor's initial rotation direction
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void loop() {
  photocellReading = analogRead(pc);
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);
  //Set rotation direction based on light level and set LED status as a helper
  if(photocellReading > lightThreshold) {
    Serial.println("lighting up led");
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    rotationDirection = 1;
  }else{
    Serial.println("shutting off led");
    digitalWrite(LED_BUILTIN, LOW);    
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
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
  Serial.print("Sending output voltage to enB of ");
  Serial.println(pwmOutput);
  analogWrite(enB, pwmOutput);
  delay(100);
}

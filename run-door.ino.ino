#define enA 9
#define in1 6
#define in2 7
#define button 4

int photocellPin = 0; // the cell and 10k pull-down resistor are connected to analog 0
int photocellReading;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  photocellReading = analogRead(photocellPin);
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);
  if(photocellReading > 200) {
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, LOW);    
  }
}

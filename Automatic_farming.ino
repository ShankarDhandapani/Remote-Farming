int relay = 8;
int LDR = A1;
int Light_Sensitivity = 500;
int LEDLamp = 13;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  char Statement[42] = "";
  int SensorValue = analogRead(A0);
  int LDRValue = analogRead(LDR);
  //Serial.println(LDRValue);
  Serial.print(SensorValue);
  Serial.print(" - ");

  if(LDRValue < 50)
  {
    digitalWrite(13, LOW);
  }
  if(LDRValue > 500)
  {
    digitalWrite(13, HIGH);
  }
  
  if(SensorValue >= 340) {
    Statement[42] = "Sensor is not in the Soil or DISCONNECTED";
    Serial.print("Sensor is not in the Soil or DISCONNECTED.MOTOR is OFF");
    digitalWrite(relay, HIGH);
  }
  if(SensorValue >= 281 && SensorValue < 340) {
    Statement[42] = "Soil is DRY";
    Serial.print("Soil is Humid. MOTOR is ON");
    digitalWrite(relay, LOW);
  }
  if(SensorValue < 165) {
    Statement[42] = "Soil is HUMID";
    Serial.print("Soil is Dry.MOTOR is ON");
    digitalWrite(relay, LOW);
  }
  if(SensorValue >= 165 && SensorValue < 280) { 
    Statement[42] = "Sensor in WATER";
    Serial.print("Sensor in WATER.MOTOR is OFF");
    digitalWrite(relay, HIGH);
  }
  Serial.print('\n');
  delay(1000);
}


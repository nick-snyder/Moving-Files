// H-Bridge (Right) is on pin 6
int RPWM = 3;

// H-Bridge (Left) is on pin 7
int LPWM = 2;

// Right Enable is always high
int R_EN = 42;

// Left Enable is always high
int L_EN = 40;

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(42, OUTPUT);

  
}

void loop()
{
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);
  
  // Write motor 100% duty (full CW)
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 255);
  delay(2000);

  // Write motor 50% duty (full CCW)
  analogWrite(RPWM, 255);
  analogWrite(LPWM, 0);
  delay(2000);
}

void setup() {
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
}

int dot = 60;
int dash = 180;
int gap = 60;

void loop() {
  if (digitalRead(12) > (0.5))
  {
    // you
    // y
    digitalWrite(13, LOW);
    delay(dash);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dot);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dash);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dash);
    digitalWrite(13, HIGH);
    delay(gap);

    // o
    digitalWrite(13, LOW);
    delay(dash);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dash);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dash);
    digitalWrite(13, HIGH);
    delay(gap);

    // u
    digitalWrite(13, LOW);
    delay(dot);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dot);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dash);
    digitalWrite(13, HIGH);
    delay(gap);

    // lose
    // l
    digitalWrite(13, LOW);
    delay(dot);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dash);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dot);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dot);
    digitalWrite(13, HIGH);
    delay(gap);

    // o
    digitalWrite(13, LOW);
    delay(dash);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dash);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dash);
    digitalWrite(13, HIGH);
    delay(gap);

    // s
    digitalWrite(13, LOW);
    delay(dot);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dot);
    digitalWrite(13, HIGH);
    delay(gap);
    digitalWrite(13, LOW);
    delay(dot);
    digitalWrite(13, HIGH);
    delay(gap);

    // e
    digitalWrite(13, LOW);
    delay(dot);
    digitalWrite(13, HIGH);
    delay(gap);
  }
}

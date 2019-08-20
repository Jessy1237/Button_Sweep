#include <Servo.h>
#define BUTTON_LEFT 2
#define SERVO 9
#define BUTTON_RIGHT 4
#define DELAY_MS 1000
#define MAX_VALUE 90


Servo myservo;

const int resting = 45;
const int pressedL = 0;
const int pressedR = 90;
int value = resting;
int prevValue = 0;

bool leftHeld = false;
bool rightHeld = false;

void moveServo(int value, int prevValue);

void setup() {
  myservo.attach(SERVO);  // attaches the servo on pin 3 to the servo object
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  //Serial.begin(9600);
  moveServo(value, prevValue);
}

void loop() {
  //if (Serial.available() > 0)
  //{
    //value = Serial.parseInt();
    //Serial.print(value);
    //Serial.print("\n");

    //moveServo(value, prevValue);

    //prevValue = value;
  //}

  if (digitalRead(BUTTON_LEFT) == LOW && !leftHeld)
  {
    moveServo(pressedL, resting);
    delay(DELAY_MS);
    moveServo(resting, pressedL);
    leftHeld = true;
  }

  if (digitalRead(BUTTON_RIGHT) == LOW && !rightHeld)
  {
    moveServo(pressedR, resting);
    delay(DELAY_MS);
    moveServo(resting, pressedR);
    rightHeld = true;
  }

  //Reset the held bools so that we know if the button can be pressed again
  if (digitalRead(BUTTON_LEFT) == HIGH)
  {
    leftHeld = false;
  }

  if (digitalRead(BUTTON_RIGHT) == HIGH)
  {
    rightHeld = false;
  }
}

void moveServo(int value, int prevValue)
{

  if (value > MAX_VALUE)
    value = MAX_VALUE;

  if (value < 0)
    value = 0;

  if (value < prevValue)
  {
    for (int i = prevValue; i > value; i--)
    {
      myservo.write(i);
      delay(5);
    }
  }
  else if (value > prevValue)
  {
    for (int i = prevValue; i < value; i++)
    {
      myservo.write(i);
      delay(5);
    }
  }
}

/*
    PIN DEFINITIONS FOR
    ULTRASONIC SENSOR AND
    L298N MOTOR DRIVER
*/

#define left_trig_pin 9
#define left_echo_pin 10
#define front_trig_pin 6
#define front_echo_pin 7
#define right_trig_pin 3
#define right_echo_pin 4
#define enA 22
#define enB 24

/*
  VARIABLE DECLARATIONS
*/

int LS, FS, RS;
int LW, RW;
int inp1 = 26;
int inp2 = 28;
int inp3 = 30;
int inp4 = 32;

// =============================================================
// setup() function
void setup()
{
  Serial.begin(9600);
  pinMode(left_trig_pin, OUTPUT);
  pinMode(front_trig_pin, OUTPUT);
  pinMode(right_trig_pin, OUTPUT);
  pinMode(left_echo_pin, INPUT);
  pinMode(front_echo_pin, INPUT);
  pinMode(right_echo_pin, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(inp1, OUTPUT);
  pinMode(inp2, OUTPUT);
  pinMode(inp3, OUTPUT);
  pinMode(inp4, OUTPUT);
}

// =============================================================
// loop() function
void loop()
{
  // check sensor values

  LS = read_sensor_left(left_trig_pin, left_echo_pin);
  FS = read_sensor_front(front_trig_pin, front_echo_pin);
  RS = read_sensor_right(right_trig_pin, right_echo_pin);

  if (RS > LS && LS < 30)
    LW = 1;
  else if (RS <= LS && RS < 30)
    RW = 1;

  if (RW == 1)
  {
    while (FS > 20)
    {
      // move forward UGV
      ugv_forward();
      // check FS and RS
      FS = read_sensor_front(front_trig_pin, front_echo_pin);
      RS = read_sensor_right(right_trig_pin, right_echo_pin);
      if (FS <= 20 || RS > 30)
      {
        // stop UGV
        ugv_stop();
        RW = 0;
        break;
      }
    }
  }
  else if (LW == 1)
  {
    while (FS > 20)
    {
      // move forward UGV
      ugv_forward();
      // check FS and LS
      LS = read_sensor_left(left_trig_pin, left_echo_pin);
      FS = read_sensor_front(front_trig_pin, front_echo_pin);
      if (FS <= 20 || LS > 30)
      {
        // stop UGV
        ugv_stop();
        LS = 0;
        break;
      }
    }
  }

  if (LW == 0 && RW == 0)
  {
    while (FS > 20)
    {
      // move forward UGV
      ugv_forward();
      // check FS
      FS = read_sensor_front(front_trig_pin, front_echo_pin);
      if (FS <= 20)
      {
        // stop UGV
        ugv_stop();
        break;
      }
    }
  }

  // check LS and RS
  LS = read_sensor_left(left_trig_pin, left_echo_pin);
  RS = read_sensor_right(right_trig_pin, right_echo_pin);

  if (RS > LS && LS < 30)
  {
    LW = 1;
    // turn right UGV
    ugv_right();
    // stop UGV
    ugv_stop();
  }
  else if (RS <= LS && RS < 30)
  {
    RW = 1;
    // turn left UGV
    ugv_left();
    // stop UGV
    ugv_stop();
  }
  else
  {
    // turn left UGV
    ugv_left();
    // stop UGV
    ugv_stop();
    RW = 1;
  }
}

/* ======================================================================== */
/* ======================================================================== */
/*                        HELPER   FUNCTIONS
/* ======================================================================== */
/* ======================================================================== */

/*
   Function - getDistance()
   returns the value of the three sensors after measuring the distance
*/
int getDistance(int trigPin, int echoPin)
{
  int duration;
  int distance;

  // send sonic waves at delay of 10 ms
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);

  // receive sonic waves
  duration = pulseIn(echoPin, HIGH);
  distance = 0.034 * duration;

  return distance;
}

/*
  read the left sensor value
*/
int read_sensor_left(int trigPin, int echoPin)
{
  int sensorValue = getDistance(trigPin, echoPin);

  // print the values
  Serial.println("LS = " + String(sensorValue));
  delay(100);

  return sensorValue;
}

/*
  read the front sensor value
*/
int read_sensor_front(int trigPin, int echoPin)
{
  int sensorValue = getDistance(trigPin, echoPin);

  // print the values
  Serial.println("FS = " + String(sensorValue));
  delay(100);

  return sensorValue;
}

/*
  read the right sensor value
*/
int read_sensor_right(int trigPin, int echoPin)
{
  int sensorValue = getDistance(trigPin, echoPin);

  // print the values
  Serial.println("RS = " + String(sensorValue));
  delay(100);

  return sensorValue;
}

/*
   Function - ugv_forward()
   moves the UGV in forward direction
*/
void ugv_forward()
{
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
  digitalWrite(inp3, HIGH);
  digitalWrite(inp4, LOW);
}

/*
   Function - ugv_left()
   turns the UGV in left direction
*/
void ugv_left()
{
  analogWrite(enA, 182);
  analogWrite(enB, 182);

  digitalWrite(inp1, LOW);
  digitalWrite(inp2, HIGH);
  digitalWrite(inp3, HIGH);
  digitalWrite(inp4, LOW);
}

/*
   Function - ugv_right()
   turns the UGV in right direction
*/
void ugv_right()
{
  analogWrite(enA, 182);
  analogWrite(enB, 182);

  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
  digitalWrite(inp3, LOW);
  digitalWrite(inp4, HIGH);
}

/*
   Function - ugv_stop()
   stops the UGV from moving
*/
void ugv_stop()
{
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

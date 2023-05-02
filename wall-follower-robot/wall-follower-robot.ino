//Algorithm
/*
   Start
   Read LS, RS, FS
   if (LS = d) LSP = 1
   else if (RS = d) RSP = 1
   else {
    LS > RS ? RSP = 1 : LSP = 1
   }

   if (RSP = 1) {
    while (RS = d)
      read LS, RS, FS
      if (FS > ɑ )
        move_forward()
      else
        stop()
        check LS, RS, FS
        turn 9º anticlock (turn_left())
        check LS, RS, FS

       while (RS != d)
        turn 90º clockwise [ turn_right() ]
        move_forward()
   }
*/

#define left_trig_pin 9
#define left_echo_pin 10
#define front_trig_pin 6
#define front_echo_pin 7
#define right_trig_pin 3
#define right_echo_pin 4
#define enA 22
#define enB 24

#define min_wall_dist 30
#define min_obj_dist 300
#define turn_dist 500


int left_distance, front_distance, right_distance;
int left_priority, right_priority;
int inp1 = 26;
int inp2 = 28;
int inp3 = 30;
int inp4 = 32;

void setup() {
  // put your setup code here, to run once:
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

  left_distance = getDistance(left_trig_pin, left_echo_pin);
  front_distance = getDistance(front_trig_pin, front_echo_pin);
  right_distance = getDistance(right_trig_pin, right_echo_pin);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("\n");
  Serial.print("Sensor 1 = "); Serial.print(left_distance); Serial.println(" cm");
  //	Serial.print("\n");
  Serial.print("Sensor 2 = "); Serial.print(front_distance); Serial.println(" cm");
  //  Serial.print("\n");
  Serial.print("Sensor 3 = "); Serial.print(left_distance); Serial.println(" cm");
  delay(2000);

  if (left_distance == min_wall_dist)
    left_priority = 1;
  else if (right_distance == min_wall_dist)
    right_priority = 1;
  else
    left_distance > right_distance ? right_priority = 1 : left_priority = 1;

  if (right_priority) {
    while (right_distance == min_wall_dist) {
      left_distance = getDistance(left_trig_pin, left_echo_pin);
      front_distance = getDistance(front_trig_pin, front_echo_pin);
      right_distance = getDistance(right_trig_pin, right_echo_pin);
      if (front_distance > min_obj_dist)
        // move forward
        move_forward();
      else {
        // stop
        stop_robot();
        // check sensors
        left_distance = getDistance(left_trig_pin, left_echo_pin);
        front_distance = getDistance(front_trig_pin, front_echo_pin);
        right_distance = getDistance(right_trig_pin, right_echo_pin);
        if (left_distance >= turn_dist)
          // turn 90 deg anticlock
          turn_left();
        else {
          // stuck from all sides
          reverse();
        }
        left_distance = getDistance(left_trig_pin, left_echo_pin);
        front_distance = getDistance(front_trig_pin, front_echo_pin);
        right_distance = getDistance(right_trig_pin, right_echo_pin);
      }
    }
    while (right_distance != min_wall_dist) {
      // turn 90 deg clock
      turn_right();
      move_forward();
    }
  }
  else if (left_priority) {
    while (left_distance == min_wall_dist) {
      left_distance = getDistance(left_trig_pin, left_echo_pin);
      front_distance = getDistance(front_trig_pin, front_echo_pin);
      right_distance = getDistance(right_trig_pin, right_echo_pin);
      if (front_distance > min_obj_dist)
        // move forward
        move_forward();
      else {
        // stop
        stop_robot();
        // check sensors
        //        left_distance = getDistance(left_trig_pin, left_echo_pin);
        //        front_distance = getDistance(front_trig_pin, front_echo_pin);
        //        right_distance = getDistance(right_trig_pin, right_echo_pin);

        // turn 90 deg anticlock
        turn_right();

        left_distance = getDistance(left_trig_pin, left_echo_pin);
        front_distance = getDistance(front_trig_pin, front_echo_pin);
        right_distance = getDistance(right_trig_pin, right_echo_pin);
      }
    }
    while (right_distance != min_wall_dist) {
      // turn 90 deg clock
      turn_left();
      move_forward();
    }
  }

  left_distance = getDistance(left_trig_pin, left_echo_pin);
  front_distance = getDistance(front_trig_pin, front_echo_pin);
  right_distance = getDistance(right_trig_pin, right_echo_pin);
}

int getDistance(int trigPin, int echoPin) {
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

void move_forward() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
  digitalWrite(inp3, HIGH);
  digitalWrite(inp4, LOW);
}

void reverse() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  digitalWrite(inp1, LOW);
  digitalWrite(inp2, HIGH);
  digitalWrite(inp3, LOW);
  digitalWrite(inp4, HIGH);
}

void turn_left() {
  analogWrite(enA, 182);
  analogWrite(enB, 182);

  digitalWrite(inp1, LOW);
  digitalWrite(inp2, HIGH);
  digitalWrite(inp3, HIGH);
  digitalWrite(inp4, LOW);
}

void turn_right() {
  analogWrite(enA, 182);
  analogWrite(enB, 182);

  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
  digitalWrite(inp3, LOW);
  digitalWrite(inp4, HIGH);
}

void stop_robot() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

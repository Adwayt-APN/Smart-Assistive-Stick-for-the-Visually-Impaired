const int trigPin = 7;
const int echoPin = 6;

long duration;
int distance;

int m=8;//ir sensor
int b = 13;//buzzer
int w=2;//water sensor


void setup() {
// put your setup code here, to run once:
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT);
pinMode(m, INPUT);
pinMode(w, INPUT);
pinMode(b, OUTPUT);// Sets the echoPin as an Input
Serial.begin(9600);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

// Calculating the distance
  distance = (duration/2) / 29.1;
  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance<=10)
  {
    tone(b, 1000); // Send 1KHz sound signal...
    delay(1000); // ...for 1 sec
    noTone(b); // Stop sound...
    delay(1000);
  }

  else if(distance >10 && distance<=20)
  {
    tone(b, 4000); // Send 4KHz sound signal...
    delay(1000); // ...for 1 sec
    noTone(b); // Stop sound...
    delay(1000);
  }

  else if(distance>20 && distance<50)
  {
    tone(b, 8000); // Send 8KHz sound signal...
    delay(1000); // ...for 1 sec
    noTone(b); // Stop sound...
    delay(1000);
  }

  else
  {
    digitalWrite(b, LOW);
  }

  int q =digitalRead(m);
  Serial.print("The IR Sensor Reading is: ");
  Serial.println(q);

  if (q==0)
  {
    digitalWrite(b, HIGH);
  }

  else
  {
    digitalWrite(b, LOW);
  }

  int P =digitalRead(w);
  Serial.print("The Water Level Sensor reading is: ");
  Serial.print(P);

  if (P==0)
  {
    digitalWrite(b, LOW);
  }

  else
  {
    digitalWrite(b, HIGH);
  }


}

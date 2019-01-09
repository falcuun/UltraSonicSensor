
const int ECHO_PIN = 5;
const int TRIGGER_PIN = 3;

int distance_CM = 0;
int distance_IN = 0;

void setup()
{
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial.begin(9600);
}

void loop()
{
    digitalWrite(TRIGGER_PIN, LOW); // Clear The sensor
    delayMicroseconds(5); // Wait for 5 uS
    digitalWrite(TRIGGER_PIN, HIGH); // Send Impulse to the Trigger pin to sensor
    delayMicroseconds(10); // Wait for 10 uS
    digitalWrite(TRIGGER_PIN, LOW); // Clear The Sensor

    distance_CM = pulseIn(ECHO_PIN, HIGH) / 58;
    distance_IN = pulseIn(ECHO_PIN, HIGH) / 148;

    Serial.println(distance_CM);
    delay(1000);
}

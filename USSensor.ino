
const int ECHO_PIN = 5; // Echo Pin on Sensor that sends data back
const int TRIGGER_PIN = 3; // Trigger Pin on Sensor that receives the trigger impulse

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

    distance_CM = pulseIn(ECHO_PIN, HIGH) / 58; // Calculating distance in CMs
    distance_IN = pulseIn(ECHO_PIN, HIGH) / 148; // Calculating distance in Inches

    Serial.println(distance_CM); // Printing Distance (Example is in CMs)
    delay(1000); // Wait for one second before sending the next wave
}

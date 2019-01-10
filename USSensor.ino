#define SAFE_DISTANCE_CM 25   // Safe distance from the Sensor in CM
#define CLOSE_DISTANCE_CM 15  // Close Distance to the Sensor in CM
#define DANGER_DISTANCE_CM 10 // Dangerously clse to the Sensor in CM

#define SAFE_DISTANCE_IN 10  // Safe distance from the Sensor in IN
#define CLOSE_DISTANCE_IN 6  // Close Distance to the Sensor in IN
#define DANGER_DISTANCE_IN 4 // Dangerously clse to the Sensor in IN

const int ECHO_PIN = 5;    // Echo Pin on Sensor that sends data back
const int TRIGGER_PIN = 3; // Trigger Pin on Sensor that receives the trigger impulse
const int GREEN_LED = 8;   // Pin for Green LED
const int RED_LED = 9;     // Pin for Red LED

int distance_CM = 0; // Initial Distance in CM
int distance_IN = 0; // Initial Distance in IN

void setup()
{
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    digitalWrite(TRIGGER_PIN, LOW);  // Clear The sensor
    delayMicroseconds(5);            // Wait for 5 uS
    digitalWrite(TRIGGER_PIN, HIGH); // Send Impulse to the Trigger pin to sensor
    delayMicroseconds(10);           // Wait for 10 uS
    digitalWrite(TRIGGER_PIN, LOW);  // Clear The Sensor

    distance_CM = pulseIn(ECHO_PIN, HIGH) / 58; // Calculating distance in CMs
    //distance_IN = pulseIn(ECHO_PIN, HIGH) / 148; // Calculating distance in Inches

    Serial.println(distance_CM); // Printing Distance (Example is in CMs)

    delayMicroseconds(65); // Wait for one second before sending the next wave
}
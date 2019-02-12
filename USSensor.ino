#define SAFE_DISTANCE_CM 25   // Safe distance from the Sensor in CM
#define CLOSE_DISTANCE_CM 15  // Close Distance to the Sensor in CM
#define DANGER_DISTANCE_CM 10 // Dangerously clse to the Sensor in CM

#define SAFE_DISTANCE_IN 10  // Safe distance from the Sensor in IN
#define CLOSE_DISTANCE_IN 6  // Close Distance to the Sensor in IN
#define DANGER_DISTANCE_IN 4 // Dangerously clse to the Sensor in IN

/*
const int ECHO_PIN = 5;    // Echo Pin on Sensor that sends data back
const int TRIGGER_PIN = 3; // Trigger Pin on Sensor that receives the trigger impulse
const int GREEN_LED = 8;   // Pin for Green LED
const int RED_LED = 9;     // Pin for Red LED
*/

const int ECHO_PINS[4] = {3, 5, 6, 9};
const int TRIGGER_PINS[4] = {2, 4, 7, 8};

int distance_CM = 0; // Initial Distance in CM
int distance_IN = 0; // Initial Distance in IN

void setup()
{
    for (int i = 0; i < sizeof(ECHO_PINS) / sizeof(int); i++)
    {
        pinMode(ECHO_PINS[i], INPUT);
    }
    for (int i = 0; i < sizeof(TRIGGER_PINS) / sizeof(int); i++)
    {
        pinMode(TRIGGER_PINS[i], OUTPUT);
    }
    // pinMode(GREEN_LED, OUTPUT);
    // pinMode(RED_LED, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    /*
    digitalWrite(TRIGGER_PIN, LOW);  // Clear The sensor
    delayMicroseconds(5);            // Wait for 5 uS
    digitalWrite(TRIGGER_PIN, HIGH); // Send Impulse to the Trigger pin to sensor
    delayMicroseconds(10);           // Wait for 10 uS
    digitalWrite(TRIGGER_PIN, LOW);  // Clear The Sensor
    */

    for (int i = 0; i < sizeof(ECHO_PINS) / sizeof(int); i++)
    {
        digitalWrite(TRIGGER_PINS[i], LOW);
        delayMicroseconds(5);
        digitalWrite(TRIGGER_PINS[i], HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIGGER_PINS[i], LOW);
        int duration = pulseIn(ECHO_PINS[i], HIGH);
        distance_CM = duration / 58;
        distance_IN = duration / 148;
        delayMicroseconds(65);

        switch(ECHO_PINS[i]){
            case 3: Serial.print("BACK DISTANCE: "); break;
            case 5: Serial.print("RIGHT DISTANCE: "); break;
            case 6: Serial.print("FRONT DISTANCE: "); break;
            case 9: Serial.print("LEFT DISTANCE: "); break;
        }

        Serial.println(distance_CM);
        delay(1000);
    }
    /*
    int duration = pulseIn(ECHO_PIN, HIGH);
    distance_CM = duration / 58;  // Calculating distance in CMs
    distance_IN = duration / 148; // Calculating distance in Inches

    distance_notifier(1, 8, 9);         // Call distance Notifier Method
    delayMicroseconds(65); // Wait for one second before sending the next wave
    delay(1000);
    Serial.println(distance_CM);
    */
}

/*
 * This method chooses distance unit and then compares
 * the provided distance with predefined safety values
 * and makes the LEDs blink according to the safety level
 * by sending the PIN Number and The interval of blinking
 */
void distance_notifier(int distance_flag, int RED_LED, int GREEN_LED)
{
    int distance;
    switch (distance_flag)
    {
    case 1:
        distance = distance_CM;
        if (distance < SAFE_DISTANCE_CM)
        {
            blink_LEDs(RED_LED, GREEN_LED, RED_LED, 700);
            if (distance < CLOSE_DISTANCE_CM)
            {
                blink_LEDs(RED_LED, GREEN_LED, RED_LED, 400);
                if (distance < DANGER_DISTANCE_CM)
                {
                    blink_LEDs(RED_LED, GREEN_LED, RED_LED, 100);
                }
            }
        }
        else
        {
            blink_LEDs(GREEN_LED, GREEN_LED, RED_LED, 1000);
        }
        break;
    case 2:
        distance = distance_IN;
        if (distance < SAFE_DISTANCE_IN)
        {
            blink_LEDs(RED_LED, GREEN_LED, RED_LED, 700);
            if (distance < CLOSE_DISTANCE_IN)
            {
                blink_LEDs(RED_LED, GREEN_LED, RED_LED, 400);
                if (distance < DANGER_DISTANCE_IN)
                {
                    blink_LEDs(RED_LED, GREEN_LED, RED_LED, 100);
                }
            }
        }
        else
        {
            blink_LEDs(GREEN_LED, GREEN_LED, RED_LED, 1000);
        }
        break;
    }
}

int LED_STATE = HIGH;             // Initial LED State
unsigned long previousMillis = 0; // Initial Millis

/*
 * This method sends signal to provided pin for the LED to turn on
 * It also waits for the provided amount of time before turning LED off
 * for the blinking effect
 */
void blink_LEDs(int LED_Pin, int GREEN_LED, int RED_LED, int interval)
{
    int currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        if (LED_STATE == LOW)
        {
            LED_STATE = HIGH;
        }
        else
        {
            LED_STATE = LOW;
        }
        if (LED_Pin == GREEN_LED)
        {
            digitalWrite(LED_Pin, LED_STATE);
            digitalWrite(RED_LED, LOW);
        }
        else if (LED_Pin == RED_LED)
        {
            digitalWrite(LED_Pin, LED_STATE);
            digitalWrite(GREEN_LED, LOW);
        }
    }
}

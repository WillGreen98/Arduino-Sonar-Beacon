#include <Arduino.h>
#include <NewPing.h>

#define LEFT_TRIG_PIN 5
#define LEFT_ECHO_PIN 4

#define RIGHT_TRIG_PIN 3
#define RIGHT_ECHO_PIN 2

#define left_Sonar_LED 7
#define right_Sonar_LED 6

#define MIN_DISTANCE 2
#define MAX_DISTANCE 400

NewPing left_Sonar_Beacon(LEFT_TRIG_PIN, LEFT_ECHO_PIN, MAX_DISTANCE);
NewPing right_Sonar_Beacon(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN, MAX_DISTANCE);

void setup() {
    Serial.begin(115200);

    pinMode(LEFT_TRIG_PIN, OUTPUT);
    pinMode(LEFT_ECHO_PIN, INPUT);

    pinMode(RIGHT_TRIG_PIN, OUTPUT);
    pinMode(RIGHT_ECHO_PIN, INPUT);

    pinMode(left_Sonar_LED, LOW);
    pinMode(right_Sonar_LED, LOW);
}

void loop() {
    long duration_Left = pulseIn(LEFT_ECHO_PIN, HIGH);
    long duration_Right = pulseIn(RIGHT_ECHO_PIN, HIGH);

    long left_Distance_CM = duration_Left * 340 * (pow(10, -4) / 2);
    long right_Distance_CM = duration_Right * 340 * (pow(10, -4) / 2);

    long left_Distance_IN = duration_Left * 340 * (pow(10, -4) / 2) * 2.54;
    long right_Distance_IN = duration_Right * 340 * (pow(10, -4) / 2) * 2.54;

    Serial.print("Left Ping Distance: ");
    Serial.print(left_Sonar_Beacon.ping_cm(MAX_DISTANCE));
    Serial.println("cm");

    Serial.print("Right Ping Distance: ");
    Serial.print(right_Sonar_Beacon.ping_cm(MAX_DISTANCE));
    Serial.println("cm");

    delay(500);
    if(left_Distance_CM >= 2.0) {
        pinMode(left_Sonar_LED, HIGH);
    } else {
        Serial.print("Left Ping Distance: ");
        Serial.print(left_Sonar_Beacon.ping_cm(MAX_DISTANCE));
        Serial.println("cm");
    }

    delay(500);
    if(right_Distance_CM >= 2.0) {
        pinMode(right_Sonar_LED, HIGH);
    } else {
        Serial.print("Right Ping Distance: ");
        Serial.print(right_Sonar_Beacon.ping_cm(MAX_DISTANCE));
        Serial.println("cm");
    }

    if(left_Distance_CM >= MAX_DISTANCE || right_Distance_CM >= MAX_DISTANCE) {
        Serial.print("Greater than max distance");
    }
}

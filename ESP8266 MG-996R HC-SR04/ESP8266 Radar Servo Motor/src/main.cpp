#include <Arduino.h>
#include "mynetwork.h"
#include <Servo.h>
#include <Ultrasonic.h>

////////////////////////
// Servo motor MG 996R
////////////////////////
// defines pins numbers
#define SERVO_MOTOR_PIN D7
Servo servo;
int angle = 0;
bool rightToLeft = true;
int step =10;

////////////////////////
// Ultrasound distance HC-SR04
////////////////////////
// defines pins numbers
#define TRIGGER D2
#define ECHO    D1
Ultrasonic ultrasonic(TRIGGER, ECHO);  // An ultrasonic sensor HC-04
// defines variables
long duration, distance;

void setup()
{
        //start serial interface for debuging...
        Serial.begin(115200);
        delay(1000);
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);
        mynetwork_init();
        digitalWrite(LED_BUILTIN, HIGH);

        servo.attach(SERVO_MOTOR_PIN); //D4
        ultrasonic.setTimeout(4000UL);


}


void loop()
{
        //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        servo.write(angle);
        delay(1000);
        if(rightToLeft) angle+=step;
        else angle-=step;

        if(angle >= 180 ) rightToLeft = false;
        if(angle <= 0 ) rightToLeft = true;

        distance = ultrasonic.read(CM);

        sendUDP("<angle>"+String(angle));
        sendUDP("<distance_CM>"+String(distance));
        sendUDP("<rightToLeft>"+String(rightToLeft));
        Serial.println(String(angle)+"°   \t"+String(distance)+" CM     \t");
}

#include <AFMotor.h>
#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>

AF_DCMotor MOTOR_3(3, MOTOR12_64KHZ);
AF_DCMotor MOTOR_4(4, MOTOR12_64KHZ);

int EXT_SERVO = 9;
Servo servo;
int angle = 0; 

unsigned long lastCommandTime = 0;
unsigned long commandTimeout = 1000; 

void reset()
{
    resetExtinguisher();
    lastCommandTime = 0;
    angle = 0;
    MOTOR_3.run(BACKWARD);
    MOTOR_4.run(BACKWARD);

    delay(5000);
    
    MOTOR_3.run(RELEASE);
    MOTOR_4.run(RELEASE);
}

void triggerExtinguisher()
{
    for (angle = 0; angle < 180; angle++)
    {
        servo.write(angle);
        delay(15);
    }
}

void resetExtinguisher()
{
    for(angle = 180; angle > 0; angle--) {
        servo.write(angle);
        delay(15);
    }
}

void receiveEvent(int bytes)
{
    lastCommandTime = millis(); 

    while (Wire.available())
    {
        char c = Wire.read();
        if (c == 'F')
        {
            MOTOR_3.run(FORWARD);
            MOTOR_4.run(FORWARD);
        }
        else if (c == 'B')
        {
            MOTOR_3.run(BACKWARD);
            MOTOR_4.run(BACKWARD);
        }
        else if (c == 'L')
        {
            MOTOR_3.run(BACKWARD);
            MOTOR_4.run(FORWARD);
        }
        else if (c == 'R')
        {
            MOTOR_3.run(FORWARD);
            MOTOR_4.run(BACKWARD);
        }
        else if (c == 'S')
        {
            MOTOR_3.run(RELEASE);
            MOTOR_4.run(RELEASE);
        }
        else if (c == 'E')
        {
            triggerExtinguisher();
        }
        else if (c == 'RST')
        {
            reset();
        }
        else
        {
            MOTOR_3.run(RELEASE);
            MOTOR_4.run(RELEASE);
        }
        delay(1);
    }
}

void initMotors()
{
    MOTOR_3.setSpeed(100);
    MOTOR_3.run(RELEASE);
    MOTOR_4.setSpeed(100);
    MOTOR_4.run(RELEASE);

    servo.attach(EXT_SERVO);

}

void setup()
{
    Wire.begin(9);
    Wire.onReceive(receiveEvent);

    initMotors();
}

void loop() {

    if (millis() - lastCommandTime > commandTimeout)
    {
        MOTOR_3.run(RELEASE);
        MOTOR_4.run(RELEASE);
    }

}
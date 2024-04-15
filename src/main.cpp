#include <AFMotor.h>
#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>


int testRunTimer = 10;
int timer = 0;

AF_DCMotor MOTOR_3(3, MOTOR12_64KHZ);
AF_DCMotor MOTOR_4(4, MOTOR12_64KHZ);
AF_DCMotor LED_1(1, MOTOR12_64KHZ);
AF_DCMotor LED_2(2, MOTOR12_64KHZ);

int EXT_SERVO1 = 9;//servo2
int EXT_SERVO2 = 10;//servo1
Servo servo_trigger;
Servo servo_hose;

int angle = 0;
char currentCommand = 'z';
bool swingHose = false;

unsigned long lastCommandTime = 0;
unsigned long commandTimeout = 3000; // Changed to 3 seconds

void resetExtinguisher()
{
    for (angle = 180; angle > 0; angle--)
    {
        servo_trigger.write(angle);
        delay(15);
    }
    swingHose = false;
}

void reset()
{
    resetExtinguisher();
    lastCommandTime = millis(); // Resetting the timer when the reset function is called
    angle = 0;
    MOTOR_3.run(BACKWARD);
    MOTOR_4.run(BACKWARD);

    delay(5000);

    MOTOR_3.run(RELEASE);
    MOTOR_4.run(RELEASE);

    Serial.println("System reset.");
}

void triggerExtinguisher()
{
    servo_trigger.write(0);
    delay(300);
    servo_trigger.write(180);
    swingHose = true;
}

void executeCommand(char c)
{
    if (c == 'F')
    {
        MOTOR_3.run(FORWARD);
        MOTOR_4.run(FORWARD);
    }
    else if(c == 'G'){
        MOTOR_3.run(FORWARD);
        MOTOR_4.run(FORWARD);
        delay(30000);
    }
    else if (c == 'B')
    {
        MOTOR_3.run(BACKWARD);
        MOTOR_4.run(BACKWARD);
    }
    else if (c == 'L')
    {
        // MOTOR_3.run(BACKWARD);
        MOTOR_4.run(FORWARD);
    }
    else if (c == 'R')
    {
        MOTOR_3.run(FORWARD);
        // MOTOR_4.run(BACKWARD);
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
    else if (c == 'X')
    {
        reset();
    }
    else
    {
        MOTOR_3.run(RELEASE);
        MOTOR_4.run(RELEASE);
    }

    Serial.print("Received command: ");
    Serial.println(c);

    // Update last command time
    lastCommandTime = millis();
}

void receiveEvent(int bytes)
{
    while (Wire.available())
    {
        char c = Wire.read();
        executeCommand(c);
    }
}

void initMotors()
{
    MOTOR_3.setSpeed(255);
    MOTOR_3.run(RELEASE);
    MOTOR_4.setSpeed(255);
    MOTOR_4.run(RELEASE);

    servo_trigger.attach(EXT_SERVO1);
    servo_hose.attach(EXT_SERVO2);
}

void initLEDs()
{
    LED_1.setSpeed(255);
    LED_2.run(RELEASE);
    LED_2.setSpeed(255);
    LED_1.run(RELEASE);
}

void setup()
{
    pinMode(LED_BUILTIN,OUTPUT);
    Serial.begin(9600);
    Wire.begin(9);
    Wire.onReceive(receiveEvent);

    initMotors();
    initLEDs();
}

void loop()
{
    // if(testRunTimer>timer){
    //     delay(1);
    //     timer++;
    //     Serial.print(timer);
    //     servo_hose.write(0);
    //     servo_trigger.write(0);
    //     MOTOR_3.run(FORWARD);
    //     MOTOR_4.run(FORWARD);
    //     delay(3000);
    //     servo_hose.write(45);
    //     servo_trigger.write(180);
    //     MOTOR_3.run(RELEASE);
    //     MOTOR_4.run(RELEASE);
    //     delay(300);

    //     return;
    // }
    if (swingHose)
    {
        servo_hose.write(0);
        delay(300);
        servo_hose.write(45);
        delay(300);
    }
}

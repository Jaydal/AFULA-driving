#include <AFMotor.h>
#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <FireValidator.h>
#include <MusicPlayer.h>

#define FWD 'F'
#define BWD 'B'
#define RIGHT 'R'
#define LEFT 'L'
#define RIGHT_BW 'C'
#define LEFT_BW 'D'
#define STOP 'S'
#define EXTINGUISH 'E'
#define RESET_MOTOR 'X'
#define FLAME_IR 'I'
#define FLAME_IR_MOTOR 'M'
#define WANG_WANG 'W'
#define NONE 'N'
#define VALIDATE 'V'
#define MANEUVER_LEFT 'Z'
#define MANEUVER_RIGHT 'A'
#define SOUND 'O'

#define VALIDATE_FIRE_IR_MID [&]() { return fireValidator.ValidateWithIR(FLM_IR_MID); }()
#define VALIDATE_FIRE_IR_LEFT [&]() { return fireValidator.ValidateWithIR(FLM_IR_LEFT); }()
#define VALIDATE_FIRE_IR_RIGHT [&]() { return fireValidator.ValidateWithIR(FLM_IR_RIGHT); }()

int FLM_IR_MID = A0;
int FLM_IR_LEFT = A1;
int FLM_IR_RIGHT = A2;

int testRunTimer = 10;
int timer = 0;
int triggerMs=1000;
int fireMidCtr = 0;
int fireLeftCtr = 0;
bool trigger = false;
int fireRightCtr = 0;
bool resetInitiated = false;

//fire validation
FireValidator fireValidator;

AF_DCMotor MOTOR_3(3, MOTOR12_64KHZ);
AF_DCMotor MOTOR_4(4, MOTOR12_64KHZ);
AF_DCMotor LED_BLUE_MTR(2, MOTOR12_64KHZ);
// AF_DCMotor EXT_TRIG(1, MOTOR12_64KHZ);
AF_DCMotor MOTOR_TRIGGER(1, MOTOR12_64KHZ);

int LED_RED = 10;//servo2
int EXT_SERVO2 = 9;//servo1
int SPK_1 = 2;
int SPEAKER_PIN = 2;
Servo servo_led;
Servo servo_hose;

//extras
MusicPlayer music;

int angle = 0;
char currentCommand = 'z';
bool swingHose = false;
bool validateIR = false;
bool validateIRWithMotor = false;
char currentCommandRequest = ' ';
bool fireDetected = false;
int fireOutCounter = 0;
bool startSiren = false;

unsigned long lastCommandTime = 0;
unsigned long commandTimeout = 3000; // Changed to 3 seconds

void sendCommand(){
//   Serial.print("Command Requested: ");
//   Serial.println(currentCommandRequest);
  Wire.write(currentCommandRequest);
}

void switchRedLED(bool on=true, int pwm = 255){
    digitalWrite(LED_RED,on?pwm:0);
}

void resetIRValues()
{
    fireMidCtr = 0;
    fireLeftCtr = 0;
    fireRightCtr = 0;
    validateIR=false;
}

void reset()
{
    // resetExtinguisher();
    // MOTOR_3.setSpeed(255);
    // MOTOR_4.setSpeed(255);
    lastCommandTime = millis(); // Resetting the timer when the reset function is called
    angle = 0;
    MOTOR_3.run(BACKWARD);
    MOTOR_4.run(BACKWARD);
    delay(1000);
    MOTOR_3.run(RELEASE);
    MOTOR_4.run(RELEASE);

    validateIR = false;
    validateIRWithMotor = false;
    fireDetected = false;
    currentCommandRequest = NONE;
    trigger = false;
    swingHose = false;

    resetIRValues();

    Serial.println("System reset.");
}

// void fireSiren(int durationMillis) {
//   int minFreq = 500;  // Minimum frequency
//   int maxFreq = 3000; // Maximum frequency
//   int step = 10;      // Frequency step size
  
//   for (int freq = minFreq; freq < maxFreq; freq += step) {
//     tone(SPK_1, freq);
//     delay(5); // Adjust delay for speed control
//   }

//   for (int freq = maxFreq; freq > minFreq; freq -= step) {
//     tone(SPK_1, freq);
//     delay(5); // Adjust delay for speed control
//   }

//   delay(durationMillis);
//   noTone(SPK_1); // Stop tone after specified duration
// }

// void wailingSiren(int durationMillis) {
//   int tone1 = 1000; // First tone frequency
//   int tone2 = 2000; // Second tone frequency
//   int switchTime = 500; // Time between switching tones (milliseconds)

//   unsigned long startTime = millis(); // Start time of the wailing
  
//   while (millis() - startTime < durationMillis) {
//     tone(SPK_1, tone1);
//     delay(switchTime / 2);
//     noTone(SPK_1);
//     delay(switchTime / 2);

//     tone(SPK_1, tone2);
//     delay(switchTime / 2);
//     noTone(SPK_1);
//     delay(switchTime / 2);
//   }
// }

// void emergencySiren(int durationMillis) {
//   int tone1 = 1500; // First tone frequency
//   int tone2 = 2500; // Second tone frequency
//   int pulseDuration = 100; // Duration of each tone pulse (milliseconds)

//   unsigned long startTime = millis(); // Start time of the emergency siren

//   while (millis() - startTime < durationMillis) {
//     tone(SPK_1, tone1);
//     delay(pulseDuration);
//     noTone(SPK_1);
//     delay(pulseDuration);
    
//     tone(SPK_1, tone2);
//     delay(pulseDuration);
//     noTone(SPK_1);
//     delay(pulseDuration);
//   }
// }

// void mixedSiren(int durationMillis) {
//   int tone1 = 1500; // First tone frequency for emergency siren
//   int tone2 = 2000; // Second tone frequency for emergency siren
//   int tone3 = 600;  // First tone frequency for fire siren
//   int tone4 = 3000; // Second tone frequency for fire siren
//   int pulseDuration = 100; // Duration of each tone pulse (milliseconds)
//   int switchTime = 500; // Time between switching tones (milliseconds)

//   unsigned long startTime = millis(); // Start time of the mixed siren

//   while (millis() - startTime < durationMillis) {
//     // Play emergency siren tone
//     for (int i = 0; i < 3; i++) {
//       tone(SPEAKER_PIN, tone1);
//       delay(pulseDuration);
//       noTone(SPEAKER_PIN);
//       delay(pulseDuration);
//       tone(SPEAKER_PIN, tone2);
//       delay(pulseDuration);
//       noTone(SPEAKER_PIN);
//       delay(pulseDuration);
//     }
//     // Play fire siren tone
//     for (int i = 0; i < 3; i++) {
//       tone(SPEAKER_PIN, tone3);
//       delay(pulseDuration);
//       noTone(SPEAKER_PIN);
//       delay(pulseDuration);
//       tone(SPEAKER_PIN, tone4);
//       delay(pulseDuration);
//       noTone(SPEAKER_PIN);
//       delay(pulseDuration);
//     }
//     delay(switchTime);
//   }
// }

// void dubstepSound() {
//     delay(100);
//     // tone(SPEAKER_PIN, 50); // Low-frequency tone
//     // delay(300); // Duration of the bassline

//     // // Rhythmic pattern
//     // tone(SPEAKER_PIN, 500); // Higher-frequency tone
//     // delay(50); // Short delay
//     // noTone(SPEAKER_PIN); // Silence
//     // delay(50); // Short delay

//     // tone(SPEAKER_PIN, 300); // Mid-frequency tone
//     // delay(100); // Short delay
//     // noTone(SPEAKER_PIN); // Silence
//     // delay(100); // Short delay
// }

void beep(int spk = SPK_1){
   for( int i = 0; i<500;i++){
      digitalWrite(spk , HIGH);
      delayMicroseconds(500);
      digitalWrite(spk, LOW );
      delayMicroseconds(500);
   }
}

void blinkLEDS(int freq = 2)
{
    for (int i = 0; i < freq; i++)
    {
        int ctr = 0;
        LED_BLUE_MTR.setSpeed(0);
        LED_BLUE_MTR.run(FORWARD);
        do
        {
            LED_BLUE_MTR.setSpeed(ctr);
            servo_led.write(255-ctr);
            ctr++;
            delay(1);
        } while (ctr <= 255);
        delay(200);
        do
        {
            LED_BLUE_MTR.setSpeed(ctr);
            servo_led.write(255-ctr);
            ctr--;
            delay(1);
        } while (ctr != 0);

        LED_BLUE_MTR.run(RELEASE);
        delay(100);
    }
}

void wangWang(int freq = 1)
{
    int ctr = 0;
    do{
        ctr++;
        for (int i = 100; i < 2000; i += 10)
        {                   // Increase frequency
            tone(SPK_1, i); // Play tone
            delay(5);       // Small delay for smooth transition
        }

        // Falling part of the siren
        for (int i = 2000; i > 100; i -= 10)
        {                   // Decrease frequency
            tone(SPK_1, i); // Play tone
            delay(5);       // Small delay for smooth transition
        }
    }
    while (ctr < freq);
    noTone(SPK_1);
}


void executeCommand(char c)
{
    if (c == FWD)
    {
        MOTOR_3.setSpeed(255);
        MOTOR_4.setSpeed(255);

        MOTOR_3.run(FORWARD);
        MOTOR_4.run(FORWARD);
    }
    else if(c == 'G'){
        MOTOR_3.run(FORWARD);
        MOTOR_4.run(FORWARD);
        delay(30000);
    }
    else if (c == BWD)
    {
        MOTOR_3.setSpeed(255);
        MOTOR_4.setSpeed(255);

        MOTOR_3.run(BACKWARD);
        MOTOR_4.run(BACKWARD);
    }
    else if (c == LEFT)
    {
        // MOTOR_3.setSpeed(10);
        MOTOR_3.run(RELEASE);// 150 speed
        MOTOR_4.run(FORWARD);
    }
    else if (c == RIGHT)
    {
        // MOTOR_4.setSpeed(10);
        MOTOR_4.run(RELEASE);// 150 speed
        MOTOR_3.run(FORWARD);
    }
    else if (c == LEFT_BW)
    {
        // MOTOR_3.setSpeed(10);
        MOTOR_3.run(RELEASE);// 150 speed
        MOTOR_4.run(BACKWARD);
    }
    else if (c == RIGHT_BW)
    {
        // MOTOR_4.setSpeed(150);
        MOTOR_4.run(RELEASE);// 150 speed
        MOTOR_3.run(BACKWARD);
    }
    else if (c == STOP)
    {
        MOTOR_3.setSpeed(255);
        MOTOR_4.setSpeed(255);
        MOTOR_3.run(RELEASE);
        MOTOR_4.run(RELEASE);
    }
    else if (c == EXTINGUISH)
    {
        //triggerExtinguisher();
        swingHose = true;
        // MOTOR_TRIGGER.run(FORWARD);
        // delay(triggerMs);
        // MOTOR_TRIGGER.run(RELEASE);
    }
    else if (c == RESET_MOTOR)
    {
        //MOTOR_TRIGGER.run(BACKWARD);
        // delay(triggerMs);
        // MOTOR_TRIGGER.run(RELEASE);
        resetInitiated = true;
    }
    else if (c == FLAME_IR){
        validateIR = true;
        validateIRWithMotor = false;
    }
    else if(c == FLAME_IR_MOTOR){
        validateIR = true;
        validateIRWithMotor = true;
    }
    else if(c==WANG_WANG){
        // startSiren = true;
    }
    else if(c==SOUND){
        beep();
    }
    else
    {
        MOTOR_3.run(RELEASE);
        MOTOR_4.run(RELEASE);
        // EXT_TRIG.run(RELEASE);
        LED_BLUE_MTR.run(RELEASE);
        switchRedLED(false);
        validateIR = false;
        validateIRWithMotor = false;
    }

    Serial.print("Received command: ");
    Serial.println(c);

    // Update last command time
    lastCommandTime = millis();
}

void wireReceiveEvent(int bytes)
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
    MOTOR_4.setSpeed(255);
    MOTOR_TRIGGER.setSpeed(255);

    servo_hose.attach(EXT_SERVO2);
    servo_hose.write(15);
}

void initComponents()
{
    // LED_BLUE_MTR.setSpeed(255);
    // LED_BLUE_MTR.run(RELEASE);
    
    //pinMode(LED_RED,OUTPUT);
    //digitalWrite(LED_RED,HIGH);
    servo_led.attach(LED_RED);
    pinMode(SPK_1, OUTPUT);
}

bool FireValidatedWithIR(){
    return (fireMidCtr+fireLeftCtr+fireRightCtr)>0;
}

void triggerExt()
{
    MOTOR_TRIGGER.run(FORWARD);
    delay(triggerMs);
    servo_hose.write(0);
    delay(500);
    servo_hose.write(45);
    delay(500);
    servo_hose.write(23);
    delay(800);
    MOTOR_TRIGGER.run(BACKWARD);
    delay(triggerMs);
    MOTOR_TRIGGER.run(RELEASE);
}

void setup()
{
    pinMode(LED_BUILTIN,OUTPUT);
    Serial.begin(115200);
    // Wire.begin();
    Wire.begin(9);
    Wire.onReceive(wireReceiveEvent);
    Wire.onRequest(sendCommand);
    initMotors();
    initComponents();
}

void loop()
{
    if(resetInitiated){
        reset();
        resetInitiated = false;
        swingHose = false;
    }
    if (swingHose)
    {
        triggerExt();
        beep(SPK_1);
        //wangWang();
    }

    if(startSiren){
        // blinkLEDS(2);
        // wangWang();
        startSiren = false;
    }

    if(validateIR){
        if (validateIRWithMotor){
            Serial.println("Driving Forward...");
            executeCommand(FWD);
            //dubstepSound();
            delay(200);
            //();
            beep();
            executeCommand(STOP);
        }

        Serial.println("Flame IR Initiated");
        fireMidCtr += VALIDATE_FIRE_IR_MID;
        delay(1);
        fireLeftCtr += VALIDATE_FIRE_IR_LEFT;
        delay(1);
        fireRightCtr += VALIDATE_FIRE_IR_RIGHT;
        delay(1);

        if (validateIRWithMotor && !FireValidatedWithIR()){
            return;
        }

        if(fireMidCtr>0){
            Serial.println("Fire is detected in the middle...");
            executeCommand(STOP);
            currentCommandRequest = FLAME_IR;
            resetIRValues();
            if(validateIRWithMotor){
                validateIRWithMotor = false;
            }
            return;
        }
        else if(FireValidatedWithIR()){
            currentCommandRequest = VALIDATE;
            Serial.println("Maneuvering until fire is detected in the middle...");
        }
        else{
            fireOutCounter++;
            if(fireOutCounter>10){
                currentCommandRequest = NONE;
                executeCommand(STOP);
                resetIRValues();
                return;
            }
        }

        if(fireLeftCtr > fireMidCtr){
            //dubstepSound();
            delay(500);
            currentCommandRequest = MANEUVER_RIGHT;
            Serial.println("Fire is detected from the left...");
            executeCommand(RIGHT_BW);
            delay(600);
            executeCommand(BWD);
            delay(200);
            executeCommand(FWD);
            delay(300);
            executeCommand(STOP);
        }

        if(fireRightCtr > fireMidCtr){
            //dubstepSound();
            delay(500);
            currentCommandRequest = MANEUVER_LEFT;
            Serial.println("Fire is detected from the right...");
            executeCommand(LEFT_BW);
            delay(600);
            executeCommand(BWD);
            delay(200);
            executeCommand(FWD);
            delay(300);
            executeCommand(STOP);
        }
        
        resetIRValues();
        if (validateIRWithMotor){
           validateIR = true;
        }

    }
}

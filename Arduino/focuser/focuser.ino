// ASCOM focuser arduino sketch
// ascom-jolo-focuser github project
// 
// Author: jolo drjolo@gmail.com
// ver. Carbon8 10.12.2014
// 
#include <dht.h>
#include <EEPROM.h>
#include <AccelStepper.h>
#include <Timer.h>

#define DEVICE_RESPONSE "Jolo Carbon8 focuser"
#define FIRMWARE "2.2"


// EEPROM addresses
#define FOCUSER_POS_START 900
#define CONFIG_VERSION "ls1"
#define CONFIG_START 800

struct {
 // This is for mere detection if they are your settings
  char version[4];
  
  int stepperSpeed; byte pwmRun; byte pwmStop; int acc; 
  byte buzzer; long maxPos; byte pwm1; byte pwm2; byte pwm3;
} ctx = {
  100, 100, 0, 500,
  1, 1000000, 0,0,0
};

struct {
  byte type;
  float temp;
  float hum;
  float dew;
  byte heaterPWM;
} sensor;

// EXT
#define PWM1_PIN 6
#define PWM2_PIN 9
#define PWM3_PIN 5
#define ADC_PIN A3

// Buzzer config
#define BUZZER_PIN 12
#define BUZ_LED_PIN 4

// Temperature sensor config
#define TEMP_CYCLE 5000      // config
#define TEMP_SENSOR_PIN 11
dht DHT;

// Stepper config
#define STEPPER_PWM_PIN 10
AccelStepper stepper = AccelStepper(AccelStepper::HALF4WIRE, 13, A0, A1, A2);  
  
Timer timer;

// Global vars
boolean positionSaved;               // Flag indicates if stepper position was saved as new focuser position
String inputString;                  // Serial input command string (terminated with \n)

int tempCycleEvent;
int buzzCycleEvent;

void loop() 
{
  stepper.run();
  checkStepper();

  timer.update();
}







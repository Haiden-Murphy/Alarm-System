/**
 * Statment of Authorship: 
 * I, Haiden Murphy, student number 000839028 
 * certify that this material is my original work. No other person's 
 * work has been used without due acknowledgment and I have not made 
 * my workavailable to anyone else.
*/

/**
 * Class: COMP-10184 – Mohawk College
 * Title: PIR Sensor Test Application
 * 
 * Description: This application is meant to resemble a simple alarm 
 * system using a PIR sensor. This alarm uses a countdown and if it 
 * reaches 0 the alrm will activate. If a button is pressed before 
 * the countdown reaches 0 the alarm will disable. If the button is 
 * pressed a second time the alarm will be re-enabled where thw PIR 
 * sensor will look for motion to begin the countdown again.
 * 
 * Author: Haiden Murphy
 * Student ID #: 000839028
 * Date: Oct 18, 2022
*/

#include <Arduino.h> 

// digital input pin definitions 
#define PIN_PIR D5 
#define PIN_BUTTON D6
//DELAY definitions that help avoid hard wired numerical constants in 
//the program
#define DELAY 10
#define BUTTON_DELAY 200 
//different case definitions
//disabled alarm state
#define ALARM_DISABLED  0
//enabled alarm state 
#define ALARM_ENABLE    1
//start the countdown when alarm is enabled
#define ALARM_COUNTDOWN 2
//alarm is activated and had reached 0 in the countdown
#define ALARM_ACTIVE    3 
//The alarm state is set to enable the alarm, wich begins the 
//switch statement and processes
int iAlarmState = ALARM_ENABLE;
//control timer is created as an integer wich will be used in the
//countdown in the switchfunction()
int timer = 10;
//bPIR is to become 0 which allows the switch statmnet to begin
//in the enabled case
int bPIR = 0;
// *************************************************************

/**
 * Purpouse: switchfunction() holds the switch statment used to switch 
 * through the applications different states (alarm states). These 
 * states are called cases. Each case plays an important role in the 
 * function of the program
*/
void switchfunction()
{//switchfunc
  //switch statement that has four different cases based on each state 
  //the alarm application can be in eg. ALARM_DISABLED, ALARM_ENABLED,
  //ALARM_COUNTDOWN, ALARM_ACTIVE.
  switch (iAlarmState) 
  {//switchI

    //---------------------ALARM_DISABLED-----------------------
    case ALARM_DISABLED:
      delay(50);
      //when the alarm is disabled the led will appear off to the user
      digitalWrite(LED_BUILTIN, HIGH);
      //uses a delay definition set as 200
      delay(BUTTON_DELAY); 
      //if the button is activated (pressed) while in disabled state
      //send a println and set the new alarm state to ALARM_ENABLE
      if(digitalRead(PIN_BUTTON) == LOW)
      {//bPressedD
        Serial.println("Button pressed: Alarm Enabled ");
        //sets the new case to enable the alarm
        iAlarmState = ALARM_ENABLE;
      }//bPressedD
      //breaks from the code without repeating unecasarialy
      break;

    //-----------------------ALARM_ENABLE------------------------
    case ALARM_ENABLE:
      //if bPIR is greater than 0
      if(bPIR > 0) 
      {//ifbPIR>0
        //the alarm state is set to count down
        iAlarmState = ALARM_COUNTDOWN;
      }//ifbPIR>0
      else
      {//elsebPIR
        //turns the led off
        digitalWrite(LED_BUILTIN, HIGH);
        //the alarm state is sent to the enable case
        iAlarmState = ALARM_ENABLE;
      }//elsebPIR
      break;

    //---------------------ENABLE_COUNTDOWN----------------------
    case ALARM_COUNTDOWN:
      Serial.println(" ");
      Serial.println("------------------------------------------");
      Serial.println("COMP-10184 - Alarm System");
      Serial.println("Name: Haiden Murphy");
      Serial.println("Student ID: 000839028");
      Serial.println("------------------------------------------");
      Serial.println("Motion Detected! - Alarm will sound in 10s!");
      Serial.println(" ");
      //Serial prints the timer count as it is negativley incremented 
      //each time (shows count down to user)
      Serial.print(" || ");
      Serial.print(timer);
      Serial.print(" || ");
      //While the cound down timer dosent equal 0
      while(timer != 0)
      {//whCount
        //Combination of delays and digital writes that turn the built
        //in led on and of about 4x per second
        delay(250);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(250);
        digitalWrite(LED_BUILTIN, LOW);
        delay(250);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(250);
        digitalWrite(LED_BUILTIN, LOW);

        //incraments the count down timer each time the loop is gone 
        //through
        timer--;
        //Serial prints the timer count as it is negativley incremented 
        //each time (shows count down to user) in the while loop
        Serial.print(" || ");
        Serial.print(timer);
        Serial.print(" || ");
        //uses a delay definition set as 200
        delay(BUTTON_DELAY);
        //If statment that checks if the button has been pressed soetime
        //during the countdown wich will set the new alarm state to disabled
        if(digitalRead(PIN_BUTTON) == LOW)
        {//ifBon
          Serial.println(" ");
          Serial.println(" ");
          Serial.println("Button pressed: Alarm Disabled ");
          //switches the alarm case to disabled
          iAlarmState = ALARM_DISABLED;
          //the timer is set to delay wich is 10
          timer = DELAY;
          //if timer is equal to 10 then break
          if(timer == DELAY)
          {//ifdelay
            //one second delay
            delay(1000);
            break;
          }//ifdelay
        }//ifBon
      }//whCount

      //if the control timer reaches 0 then the alarm will become activated
      if(timer == 0)
      {//iftimer0
        Serial.println(" ");
        Serial.println(" ");
        Serial.println("<<< ALARM ACTIVATED: INTRUDER ALERT >>>");
        Serial.println("------------------------------------------");
        //sets the new case to active
        iAlarmState = ALARM_ACTIVE;
      }//iftimer0
      break;

    //---------------------ENABLE_COUNTDOWN----------------------
    case ALARM_ACTIVE:
      //sets the new case to active again, which keeps the alarm in this state 
      //unless the user restarts the program
      iAlarmState = ALARM_ACTIVE;
      break;

    //--------------------------DEFAULT--------------------------
    default:
      //if the program cannot reach the other cases this error message will be 
      //sent as default to alert the user
      Serial.println("ERROR");
      break;
  }//switchI
}//switchfunc
// *************************************************************

/**
 * Purpose: The setup function allows the serial terminal to begin, then the 
 * compnent locations are declared and their proper configurations. eg. the 
 * led is set to output, the PIR sensor is set as input, and button is also 
 * set as an input type.
*/
void setup() 
{//setup
  // configure the USB serial monitor 
  Serial.begin(115200);
  // configure the LED output 
  pinMode(LED_BUILTIN, OUTPUT); 
  // PIR sensor is an INPUT 
  pinMode(PIN_PIR, INPUT);
  // Button is an INPUT 
  pinMode(PIN_BUTTON, INPUT_PULLUP);
}//setup
// ************************************************************* 

/**
 * purpouse: loop function that the program runs through. Here the variable bPIR
 * is made, and the switch function is called.
*/
void loop() 
{//loop
  // read PIR sensor (true = Motion detected!).  As long as there 
  // is motion, this signal will be true.  About 2.5 seconds after  
  // motion stops, the PIR signal will become false. 
  bPIR = digitalRead(PIN_PIR);
  // switchfunction is called on and the switch statmnet belonging 
  // to it is used depending on the iAlarmState.
  switchfunction();
}//loop



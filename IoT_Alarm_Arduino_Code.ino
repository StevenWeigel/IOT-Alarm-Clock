/* 
  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  String userText;
  int frequency_user;
  CloudSchedule time2;
  bool backlight;
  bool lightBlink;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <utility/wifi_drv.h>
#include <LiquidCrystal.h>
#include <TimeLib.h>

bool switchOn;


//lcd(rs,en,d4,d5,d6,d7)
LiquidCrystal lcd(6,7,8,9,10,11);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
  
  switchOn = false;
  // Defined in thingProperties.h
  initProperties();
  noTone(1);
  pinMode(5,OUTPUT);
  digitalWrite(5, HIGH); 
  
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

  int i = 255; //green
  int j = 0; //red
  int k = 0; //blue
  bool iFade = true;
  bool jFade = false;
  bool kFade = false;
  int alarm = 400;
  int n = 0;
  bool alarmOn = false;
  bool flag0 = false;
  bool flag1 = true;
  bool flag2 = true;
  
void loop() {
  ArduinoCloud.update();
  
  
  if (flag0)
  {
    int hour0;
    String amPm;
    setTime(ArduinoCloud.getLocalTime());
    if (hour() < 1)
    {
      hour0 = 12;
    }
    else if (hour() > 12)
    {
      hour0 = hour() - 12;
    }
    else
    {
      hour0 = hour();
    }
    if (hour() >= 12)
    {
      amPm = "PM";
    }
    else
    {
      amPm = "AM";
    }
    if (second() == 0)
    {
      lcd.clear();
      lcd.setCursor(0,1);
      if (time2.isActive() || lightBlink)
      {
        lcd.print(userText);
        flag2 = true;
      }
    }
    String s = String(hour0) + ":" + String(minute()) + ":" + String(second()) + " " + amPm;
    lcd.setCursor(0,0);
    lcd.print(s);
  }
 
 if (!backlight)
 {
   digitalWrite(5, LOW); 
 }
 else
 {
   digitalWrite(5, HIGH); 
 }

    if (time2.isActive() || lightBlink)
    {
      alarm = frequency_user;
      if (flag1)
      {
       lcd.begin(16,2);
       lcd.setCursor(0,1);
       lcd.print(userText);
       flag1 = false;
       flag2 = true;
       flag0 = true;
      }
      
      if (n % 25 == 0)
      {
        if (!alarmOn)
        {
          tone(1, alarm);
        }
        else
        {
          noTone(1);
        }
        alarmOn = !alarmOn;
      }
      n++;
      WiFiDrv::analogWrite(25, i);
      WiFiDrv::analogWrite(26, j);
      WiFiDrv::analogWrite(27, k);
      if (iFade)
      {
        if (j != 255)
        {
          j++;
        }
        if (j == 255)
        {
          i--;
          if (i == 0)
          {
            iFade = false;
            jFade = true;
          }
        }
      }
      else if (jFade)
      {
        if (k != 255)
        {
          k++;
        }
        if (k == 255)
        {
          j--;
          if (j == 0)
          {
            jFade = false;
            kFade = true;
          }
        }
      }
      else if (kFade)
      {
        if (i != 255)
        {
          i++;
        }
        if (i == 255)
        {
          k--;
          if (k == 0)
          {
            kFade = false;
            iFade = true;
          }
        }
      }
    }
    else
    {
      WiFiDrv::analogWrite(25, 0);
      WiFiDrv::analogWrite(26, 0);
      WiFiDrv::analogWrite(27, 0);
      noTone(1);
      if (flag2)
      {
        lcd.setCursor(0,1);
        lcd.clear();
        flag2 = false;
        flag1 = true;
      }
    }
}

/*
  Since LightBlink is READ_WRITE variable, onLightBlinkChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLightBlinkChange()  
{
    
}



/*
  Since Time2 is READ_WRITE variable, onTime2Change() is
  executed every time a new value is received from IoT Cloud.
*/
void onTime2Change()  {
  
}



/*
  Since TimeRead is READ_WRITE variable, onTimeReadChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTimeReadChange()  
{
  // Add your code here to act upon TimeRead change
}

/*
  Since UserText is READ_WRITE variable, onUserTextChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onUserTextChange()  {
  // Add your code here to act upon UserText change
  flag1 = true;
}

/*
  Since FrequencyUser is READ_WRITE variable, onFrequencyUserChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onFrequencyUserChange()  {
  // Add your code here to act upon FrequencyUser change
}


/*
  Since Backlight is READ_WRITE variable, onBacklightChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBacklightChange()  {
  // Add your code here to act upon Backlight change
}

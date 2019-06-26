/*
Contributors: Corey LePine, Libby Moore, Jake S. (6/25/19)
 
Sources: 
Balloon Shield Rev. 1.0
Test Code - Jesse Austin 11/20/14
Updated 12/16/2014 - Chris Koehler for CCCE Workshop 2015
-Modified from WRSG Arduino Workshop Code
Updated 01/04/2017 for OpenLog  
   
*/

/// Libraries
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>


/// Definitions
   
   /*
   Ammonia Sensor Definitions
   MAKE SURE TO CALBIRATE (get Ro) EACH TIME YOU USE THE DEVICE
  */
  // Tina (MQ137 A Sensor - Bacteria)
  double Rl = 47; // Load resistance used in circuti
  double ratio = 3.6; // Ratio of Rs/Ro
  double Vc = 5; // Input Voltage
  double b = 0.482587; // intercept based on MQ137 Datasheet
  double m = -0.292481; // slope based on MQ137 Datasheet 
  double Ro = 230; 

  // Trevor (MQ137 B Sensor - Cracked) 
  double RlB = 20; // Load resistance used in circuit
  double ratioB = 3.7; // Ratio of Rs/Ro
  double VcB = 5; // Input Voltage
  double bB = 0.971; // Intercept based
  double mB = -0.48531; // slope based
  double RoB = 177.15; 
   
  
  /*
   Temperature Sensor Definitions
  */
   // Temp Sensor A
   int temp1;
   float temp1Volt;
   float temp1C;
   float temp1F;

   // Temp Sensor B
    int temp2;
    float temp2Volt;
    float temp2C;
    float temp2F;

  /*
   Pressure Sensor Definitions
  */

  // Pressure Sensor A
    int pressureA;
    float pressureVoltA;
    float psiA;
    
  // Pressure Sensor B
    int pressureB;
    float pressureVoltB;
    float psiB;
  /*
   Hummidty Sensor Definitions
  */
    int humidity;
    float humidityVolt;
    float RH;

  /*
   Accelerameter  Definitions
  */
   // Accelerometer X  
    int accelX;
    float accelXVolt;
    float accelXG;

  // Accelerometer Y
    int accelY;
    float accelYVolt;
    float accelYG;
    
  // Accelerometer Z
    int accelZ;
    float accelZVolt;
    float accelZG;

  /*
   Switch Definitions
  */

  /*
   Clock Definitions
  */
     #if defined(ARDUINO_ARCH_SAMD)
     // for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
        #define Serial SerialUSB
     #endif

     RTC_DS1307 rtc;

     char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  /*
   SD Card Definitions
  */

String Textfile = "balloon.txt";
File myFile; //can name this whatever, and you can add more files but that might get complicated

  /*
   Battery Gauge Definitions
  */

void setup() 
{
  Serial.begin(9600);
 
  Serial.println("Header for sensors");

  /*
   Switch Setup
  */

  /*
   Clock Setup
  */
   #ifndef ESP8266
     while (!Serial); // for Leonardo/Micro/Zero
   #endif

     if (! rtc.begin()) 
     {
       Serial.println("Couldn't find RTC");
       while (1);
     }

     if (! rtc.isrunning()) 
     {
       Serial.println("RTC is NOT running!");
       // following line sets the RTC to the date & time this sketch was compiled
       rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
       // This line sets the RTC with an explicit date & time, for example to set
       // January 21, 2014 at 3am you would call:
       // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
     }

  /*
   SD Card Setup
  */
 // put your setup code here, to run once:
      while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

// Print Column Headers
      myFile = SD.open(Textfile, FILE_WRITE);
      
      if (myFile) {
      Serial.println("Data Opened...");
      }
      else {
        Serial.println("Failed to Open File");
      }
  

  /*
   Battery Gauge Setup
  */
}

void loop() 
{
  
  /*
   Ammonia Sensor Loop
  */

  /// Tina
  double analog_value = 0;
  double VRL;
  double Rs;
  for(int average = 1; average <= 500; average++)
  {
    analog_value = analog_value + analogRead(0); ////////////////////// ANALOG
  }
  analog_value = analog_value/500;
  
  VRL = analog_value*(5.0/1023); // convert analog readings to voltage
  Rs = ((Vc*Rl)/VRL) - Rl; // compute Rs using the formula from the website 

  // Calibrate MQ137; do in clean air then apply ammonia
  //Ro = Rs/ratio;
  //Serial.print("MQ137 Ro: ");
  //Serial.println(Ro);

  // Get PPM MQ137
  double PPM = pow(10, ((log10(Rs/Ro)-b)/m));//use formula to calculate ppm
  Serial.print("Tina Ammtonia PPM: ");
  Serial.println(PPM);

  /// Sammie
  double analog_valueB = 0;
  double VRLB; 
  double RsB; 
  for (int ave = 1; ave <= 500; ave++)
  {
    analog_valueB = analog_valueB + analogRead(1); ////////////////////// ANALOG
  }
  analog_valueB = analog_valueB/500;

  VRLB = analog_valueB*(5.0/1023); // convert analog readings to voltage
  RsB = ((VcB*RlB)/VRLB) - RlB; // compute Rs using the formula from the website

  // Calibrate MQ135; do in clean air then apply ammonia
  //RoB = RsB/ratioB;
  //Serial.print("MQ135 Ro: ");
  //Serial.println(RoB);

  // Get PPM MQ135
  double PPMB = pow(10, ((log10(RsB/RoB)-bB)/mB));//use formula to calculate ppm
  Serial.print("Sam Air Quiality: ");
  Serial.println(PPMB);
  Serial.println();

  delay(1000);

  /*
   Temperature Sensor Loop
  */
 // Temp Sensor A
 temp1 = analogRead(0); ////////////////////// ANALOG
 temp1Volt = temp1*(5.0/1023);
 temp1C = (temp1Volt - 0.5)/(0.01);
 temp1F = (temp1C*(9.0/5.0) + 32);
 //Serial.print(",");    
 //Serial.print(temp1F, 2);
 
 // Temp Sensor B 
 temp2 = analogRead(1); ////////////////////// ANALOG
 temp2Volt = temp2*(5.0/1023);
 temp2C = (temp2Volt - 0.5)/(0.01);
 temp2F = (temp2C*(9.0/5.0) + 32);
 //Serial.print(",")
 //Serial.print(temp2F, 2);

  /*
   Pressure Sensor Loop
  */
 
 // Pressure Sensor A
 pressureA = analogRead(3); ////////////////////// ANALOG
 pressureVoltA = pressureA*(5.0/1023);
 psiA = (pressureVoltB - 0.5)*(15.0/4.0);
 //Serial.print(",");    
 //Serial.print(psiA, 2);
 
 
 // Pressure Sensor B 
 pressureB = analogRead(3); ////////////////////// ANALOG
 pressureVoltB = pressureB*(5.0/1023);
 psiB = (pressureVoltB - 0.5)*(15.0/4.0);
 //Serial.print(",");    
 //Serial.print(psiB, 2);
 
  /*
   Hummidty Sensor Loop
  */
 humidity = analogRead(2); ////////////////////// ANALOG
 humidityVolt = humidity*(5.0/1023);
 RH = (((humidityVolt/5.0)-0.16)/0.0062);
 //Serial.print(",");    
 //Serial.print(RH, 2);
 
  /*
   Accelerameter  Loop
  */
 // X Accel
 accelX = analogRead(4); ////////////////////// ANALOG
 accelXVolt = accelX*(5.0/1023);
 accelXG = (accelXVolt - (3.3/2))/(0.330);
 //Serial.print(",");    
 //Serial.print(accelXG,3);
 
 // Y Accel
 accelY = analogRead(4); ////////////////////// ANALOG
 accelYVolt = accelY*(5.0/1023);
 accelYG = (accelYVolt - (3.3/2))/(0.330);
 //Serial.print(",");    
 //Serial.print(accelXG,3);
 
 // Z Accel
 accelZ = analogRead(4); ////////////////////// ANALOG
 accelZVolt = accelZ*(5.0/1023);
 accelZG = (accelZVolt - (3.3/2))/(0.330);
 //Serial.print(",");    
 //Serial.print(accelXG,3);

  /*
   Switch Loop
  */

  /*
   Clock Loop
  */
 
    DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
    
    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now + TimeSpan(7,12,30,6));
    
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    
    Serial.println();
    delay(3000);

  /*
   SD Card Loop
  */

// open file
      myFile = SD.open(Textfile, FILE_WRITE);

//   put your main code here, to run repeatedly:
///////////////////////////////////////////////////////
//use myFile.print() wherever you want to save to SD -- Works the same as Serial.print()





//////////////////////////////////////////////////////
     myFile.close();

  /*
   Battery Gauge Loop
  */

}

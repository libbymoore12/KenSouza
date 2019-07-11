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
#include "MAX17043.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "LowPower.h"


/// Definitions

// Analog Port Assignments
int portAmmonia137 = 1;
int portAmmonia135 = 1;
int portPresA = 0;
int portPresB = 0;
int portTempA = 3;
int portTempB = 3;
int portAccelX = 6;
int portAccelY = 7;
int portAccelZ = 8;
int portHum = 2;

//Digital Pin Assignments
int JarDigitalPin = 8;

 /*
   Clock Definitions
  */

     #if defined(ARDUINO_ARCH_SAMD)
     // for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
        #define Serial SerialUSB
     #endif

     RTC_DS1307 rtc;
     
// CHANGE THIS TO DATE OF FLIGHT !!
    float OVERRIDE = 5; //CHANGE TO 1 AT FLIGHT

     char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
     float LaunchTime = 1564186020/OVERRIDE;
     float LaunchTime24 = LaunchTime-(24*3600); //24 hours before launch

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

  // Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
  
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
   Accelerometer  Definitions
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
   SD Card Definitions
  */

String Textfile = "DemoSat.txt";
File myFile; //can name this whatever, and you can add more files but that might get complicated

uint32_t timeStamp = 0;

  /*
   Battery Gauge Definitions
  */

  MAX17043 batteryMonitor;

void setup() 
{
  Wire.begin();
  Serial.begin(9600);
  
/*
 * Temperature Setup
 */
 
   // Start up the library
  sensors.begin();
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

  if (!SD.begin(53)) {
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

  Serial.println("Time, Battery (V), Battery (%), Tina (PPM),Tina (Analog), Trevor (PPM), Trevor (Analog), TempA (F), TempB (F), PressA (psi), PressB (psi), Hum (%?), AccelX (m/s^2), AccelY (m/s^2), AccelZ (m/s^2)");

   pinMode(8, OUTPUT);

}


void loop() {




/// SD Card Loop

  myFile = SD.open(Textfile, FILE_WRITE);
  //use myFile.print() wherever you want to save to SD -- Works the same as Serial.print()

  // Time Loop

    DateTime now = rtc.now();
    timeStamp = now.unixtime(); 
    //Check if more than 24 hours before
      
    if(now.unixtime() < LaunchTime24)
    {
      Serial.print("Before Pre-heat Time...");
      myFile.print("Before Pre-heat Time...");
    //Don't turn on any sensors:
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    

    
    }
    
    //  Check if 24 hours before
    
    if((now.unixtime()<LaunchTime) && (now.unixtime()>LaunchTime24))
    {
      Serial.print("Pre-heating...");
      myFile.print("Pre-heating...");
    //Turn on Ammonia Sensor here:
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    digitalWrite(JarDigitalPin, HIGH);
    //delay(1000);
    //digitalWrite(JarDigitalPin, LOW);

    
    }

    //Check if Launch Time
    
    if(now.unixtime()>LaunchTime)
    {
      Serial.print("All Sensors on");
    //Turn on all sensors here:
    digitalWrite(JarDigitalPin, HIGH);
    //delay(1000);
    //digitalWrite(JarDigitalPin, LOW);
    //delay(1000);
    }
   

  Serial.print(timeStamp);
  Serial.print(", ");

  myFile.print(timeStamp);
  myFile.print(", ");


///Battery Gauge Loop

  batteryMonitor.reset();
  batteryMonitor.quickStart();
  delay(500);

  float cellVoltage = batteryMonitor.getVCell();
  //Serial.print("Voltage:\t\t");
  Serial.print(cellVoltage, 4);
  Serial.print(", ");

  myFile.print(cellVoltage, 4);
  myFile.print(", ");
  

  float stateOfCharge = batteryMonitor.getSoC();
  //Serial.print("State of charge:\t");
  Serial.print(stateOfCharge);
  Serial.print(", ");

  myFile.print(stateOfCharge);
  myFile.print(", ");


  ///Ammonia Sensor Loop
  
    /// Tina
    double analog_value = 0;
    double VRL;
    double Rs;
    for(int average = 1; average <= 500; average++)
    {
      analog_value = analog_value + analogRead(portAmmonia137); ////////////////////// ANALOG
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
    Serial.print(PPM);
    Serial.print(", ");

    myFile.print(PPM);
    myFile.print(", ");

    Serial.print(analogRead(portAmmonia137));
    Serial.print(", ");

    myFile.print(analogRead(portAmmonia137));
    myFile.print(", ");
  
    /// Trevor
    double analog_valueB = 0;
    double VRLB; 
    double RsB; 
    for (int ave = 1; ave <= 500; ave++)
    {
      analog_valueB = analog_valueB + analogRead(portAmmonia135); ////////////////////// ANALOG
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
    Serial.print(PPMB);
    Serial.print(", ");

    myFile.print(PPMB);
    myFile.print(", ");

    Serial.print(analogRead(portAmmonia135));
    Serial.print(", ");

    myFile.print(analogRead(portAmmonia135));
    myFile.print(", ");
  
  
  ///Temperature Sensor Loop
  sensors.requestTemperatures();
  
   // Temp Sensor A
   //temp1 = analogRead(portTempA); ////////////////////// ANALOG
   //temp1Volt = temp1*(5.0/1023);
   //temp1C = (temp1Volt - 0.5)/(0.01);
   //temp1F = (temp1C*(9.0/5.0) + 32);
   temp1F = sensors.getTempFByIndex(portTempA);
   Serial.print(temp1F);
   Serial.print(", ");

   myFile.print(temp1F);
   myFile.print(", ");
   
   // Temp Sensor B 
   //temp2 = analogRead(portTempB); ////////////////////// ANALOG
   //temp2Volt = temp2*(5.0/1023);
   //temp2C = (temp2Volt - 0.5)/(0.01);
   //temp2F = (temp2C*(9.0/5.0) + 32);
   temp2F = sensors.getTempFByIndex(portTempB);
   Serial.print(temp2F);
   Serial.print(", ");

   myFile.print(temp2F);
   myFile.print(", ");
  
  
  ///Pressure Sensor Loop
   // Pressure Sensor A
   pressureA = analogRead(portPresA); ////////////////////// ANALOG
   pressureVoltA = pressureA*(5.0/1023);
   psiA = (pressureVoltB - 0.5)*(15.0/4.0);
   Serial.print(psiA);
   Serial.print(", ");

   myFile.print(psiA);
   myFile.print(", ");
   
   
   // Pressure Sensor B 
   pressureB = analogRead(portPresB); ////////////////////// ANALOG
   pressureVoltB = pressureB*(5.0/1023);
   psiB = (pressureVoltB - 0.5)*(15.0/4.0);
   Serial.print(psiB);
   Serial.print(", ");

   myFile.print(psiB);
   myFile.print(", ");
   
  
  ///Hummidty Sensor Loop
   humidity = analogRead(portHum); ////////////////////// ANALOG
   humidityVolt = humidity*(5.0/1023);
   RH = (((humidityVolt/5.0)-0.16)/0.0062);
   Serial.print(RH);
   Serial.print(", ");

   myFile.print(RH);
   myFile.print(", ");
   
  
  ///Accelerameter  Loop
   // X Accel
   accelX = analogRead(portAccelX); ////////////////////// ANALOG
   accelXVolt = accelX*(5.0/1023);
   accelXG = (accelXVolt - (3.3/2))/(0.330);
   Serial.print(accelXG);
   Serial.print(", ");

   myFile.print(accelXG);
   myFile.print(", ");
   
   // Y Accel
   accelY = analogRead(portAccelY); ////////////////////// ANALOG
   accelYVolt = accelY*(5.0/1023);
   accelYG = (accelYVolt - (3.3/2))/(0.330);
   Serial.print(accelYG);
   Serial.print(", ");

   myFile.print(accelYG);
   myFile.print(", ");
   
   // Z Accel
   accelZ = analogRead(portAccelZ); ////////////////////// ANALOG
   accelZVolt = accelZ*(5.0/1023);
   accelZG = (accelZVolt - (3.3/2))/(0.330);
   Serial.print(accelZG);

   myFile.print(accelZG);


  Serial.println();
  myFile.println();
  
  // Close the SD Card
  myFile.close();


}

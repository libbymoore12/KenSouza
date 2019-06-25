/* Balloon Shield Rev. 1.0
   Test Code - Jesse Austin 11/20/14
   Updated 12/16/2014 - Chris Koehler for CCCE Workshop 2015
      -Modified from WRSG Arduino Workshop Code
   Updated 01/04/2017 for OpenLog   
   
   Sensor Code for:
   - Temperature x2
   - Humidity
   - Pressure
   - Accelerometer
   - 6 LED Visual Display */

// Definitions
// Temperature Sensor #1    
    int temp1;
    float temp1Volt;
    float temp1C;
    float temp1F;
    
// Temperature Sensor #2   
    int temp2;
    float temp2Volt;
    float temp2C;
    float temp2F;
   
// Humidity Sensor    
    int humidity;
    float humidityVolt;
    float RH;
    
// Presure Sensor         
    int pressure;
    float pressureVolt;
    float psi;
    
// Accelerometer X  
    int accelX;
    float accelXVolt;
    float accelXG;
    
// Accelerometer Z
    int accelZ;
    float accelZVolt;
    float accelZG;
    
// Time keeper 
// The time stamp used when recording data points
    uint32_t timeStamp = 0;  

// Textfile
    String Textfile = "balloon.txt";

 // Libraries
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
// put your setup code here, to run once:

      Serial.begin(9600);
      while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");


// setup the LED Visual Display
      pinMode(3, OUTPUT);  //Arduino on
      pinMode(4, OUTPUT);  //Internal Temp
      pinMode(5, OUTPUT);  //External Temp
      pinMode(6, OUTPUT);  //Humidity
      pinMode(7, OUTPUT);  //Pressure
      pinMode(9, OUTPUT);  //Accels

// turn on Arduino LED
      digitalWrite(3, HIGH);  // Leave on while power is on 

// Print Column Headers
      myFile = SD.open(Textfile, FILE_WRITE);
      
      if (myFile) {
      Serial.println("Data Opened...");
      }
      else {
        Serial.println("Failed to Open File");
      }
      
      Serial.println("Time,Temp1F,Temp2F,RH,Pres,AccX,AccZ");
      myFile.println("Time,Temp1F,Temp2F,RH,Pres,AccX,AccZ");
      myFile.close();
}

void loop() { 
//   put your main code here, to run repeatedly:

// open file
      myFile = SD.open(Textfile, FILE_WRITE);

//   Turn script running leds OFF at begining of loop
     digitalWrite(4, LOW);
     digitalWrite(5, LOW);
     digitalWrite(6, LOW);
     digitalWrite(7, LOW);
     digitalWrite(9, LOW);
     
     delay(500);  //Amount of time between samples (milliseconds)
     
// Log the time
     timeStamp = millis();
     Serial.print(timeStamp);
     myFile.print(timeStamp);       
             
     temp1 = analogRead(A0);
     temp1Volt = temp1*(5.0/1023);
     temp1C = (temp1Volt - 0.5)/(0.01);
     temp1F = (temp1C*(9.0/5.0) + 32);
     Serial.print(",");    
     Serial.print(temp1F, 2);
     myFile.print(",");    
     myFile.print(temp1F, 2);
     //digitalWrite(4, HIGH);
 
     temp2 = analogRead(A1);
     temp2Volt = temp2*(5.0/1023);
     temp2C = (temp2Volt - 0.5)/(0.01);
     temp2F = (temp2C*(9.0/5.0) + 32);
     Serial.print(",");    
     Serial.print(temp2F, 2);
     myFile.print(",");    
     myFile.print(temp2F, 2);
     //digitalWrite(5, HIGH);
    
     humidity = analogRead(A2);
     humidityVolt = humidity*(5.0/1023);
     RH = (((humidityVolt/5.0)-0.16)/0.0062);
     Serial.print(",");    
     Serial.print(RH, 2);
     myFile.print(",");    
     myFile.print(RH, 2);
     //digitalWrite(6, HIGH);

     pressure = analogRead(A3);
     pressureVolt = pressure*(5.0/1023);
     psi = (pressureVolt-0.5)*(15.0/4.0); 
     Serial.print(",");    
     Serial.print(psi, 2);
     myFile.print(",");    
     myFile.print(psi, 2);
     digitalWrite(7, HIGH);
     
     accelX = analogRead(A4);
     accelXVolt = accelX*(5.0/1023);
     accelXG = (accelXVolt - (3.3/2))/(0.330);
     Serial.print(",");    
     Serial.print(accelXG,3);
     myFile.print(",");    
     myFile.print(accelXG,3);

     accelZ = analogRead(A5);
     accelZVolt = accelZ*(5.0/1023);
     accelZG = (accelZVolt - (3.3/2))/(0.330);
     Serial.print(",");    
     Serial.print(accelZG,3);
     myFile.print(",");    
     myFile.print(accelZG,3);
     //digitalWrite(9, HIGH);
     
     Serial.println();
     myFile.println();
     myFile.close();

}

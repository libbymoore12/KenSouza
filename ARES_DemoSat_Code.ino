
/*
Contributors: Corey LePine, Libby Moore, Jake S. (6/25/19)
 
Sources: 
Balloon Shield Rev. 1.0
Test Code - Jesse Austin 11/20/14
Updated 12/16/2014 - Chris Koehler for CCCE Workshop 2015
-Modified from WRSG Arduino Workshop Code
Updated 01/04/2017 for OpenLog  
   
*/


   
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

  // Sammie (MQ137 B Sensor - Cracked)
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

  /*
   SD Card Definitions
  */

  /*
   Battery Gauge Definitions
  */

void setup() 
{
  Serial.begin(9600);

  /*
   Temperature Sensor Setup
  */

  /*
   Pressure Sensor Setup
  */

  /*
   Hummidty Sensor Setup
  */

  /*
   Accelerameter  Setup
  */

  /*
   Switch Setup
  */

  /*
   Clock Setup
  */

  /*
   SD Card Setup
  */

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
    analog_value = analog_value + analogRead(0);
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
    analog_valueB = analog_valueB + analogRead(1);
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

  /*
   Pressure Sensor Loop
  */

  /*
   Hummidty Sensor Loop
  */

  /*
   Accelerameter  Loop
  */

  /*
   Switch Loop
  */

  /*
   Clock Loop
  */

  /*
   SD Card Loop
  */

  /*
   Battery Gauge Loop
  */

}

int Rl = 47; // Load resistance used in circuti
double ratio = 3.6; // Ratio of Rs/Ro
int Vc = 5; // Input Voltage
double b = 0.482587; // intercept based on MQ137 Datasheet
double m = -0.292481; // slope based on MQ137 Datasheet 
double Ro = 192.42; 
// 
int Rl135 = 20; // Load resistance used in circuit for MQ135
double ratio135 = 3.7; // Ratio of Rs/Ro for MQ135
int Vc135 = 5; // Input Voltage
double b135 = 0.971; // Intercept based on MQ135
double m135 = -0.48531; // slope based on MQ135
double Ro135 = 126.25; 

void setup() 
{
  Serial.begin(9600);
  pinMode(0,INPUT);
}

void loop() 
{
  int analog_value = 0;
  float VRL;
  float Rs;
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

    int analog_value135 = 0;
  float VRL135; 
  float Rs135; 
  for (int ave = 1; ave <= 500; ave++)
  {
    analog_value135 = analog_value135 + analogRead(1);
  }
  analog_value135 = analog_value135/500;

  VRL135 = analog_value135*(5.0/1023); // convert analog readings to voltage
  Rs135 = ((Vc135*Rl135)/VRL135) - Rl135; // compute Rs using the formula from the website

  // Calibrate MQ135; do in clean air then apply ammonia
  //Ro135 = Rs135/ratio135;
  //Serial.print("MQ135 Ro: ");
  //Serial.println(Ro135);

  // Get PPM MQ137
  double PPM = pow(10, ((log10(Rs/Ro)-b)/m));//use formula to calculate ppm
  Serial.print("Tina Ammtonia PPM: ");
  Serial.println(PPM);
  
  // Get PPM MQ135
  double PPM135 = pow(10, ((log10(Rs135/Ro135)-b135)/m135));//use formula to calculate ppm
  Serial.print("Sam Ammonia PPM: ");
  Serial.println(PPM135);
  Serial.println();
  
  delay(1000);
}

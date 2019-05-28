//works for reading in basic temperature data and printing to the serial monitor

int value=0;

void setup() // set up the electronics
{
  pinMode(A0,INPUT);
  Serial.begin(9600);
  
}

void loop() // continous check to use by electronics
{ 
  value = analogRead(A0);
  Serial.println(value);
  
  delay(10);
}

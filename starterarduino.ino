//just kidding this is the actual one

void setup() 
{
 Serial.begin(9600);
 pinMode(12,INPUT);
 
}

void loop() 
{
  int onOff=digitalRead(12);
  Serial.println(onOff);
delay(50);

}

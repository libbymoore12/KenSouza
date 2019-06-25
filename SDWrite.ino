// Declare Variables
String Textfile = "balloon.txt";
 
 // Libraries
#include <SPI.h>
#include <SD.h>

File myFile; //can name this whatever, and you can add more files but that might get complicated

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

// Print Column Headers
      myFile = SD.open(Textfile, FILE_WRITE);
      
      if (myFile) {
      Serial.println("Data Opened...");
      }
      else {
        Serial.println("Failed to Open File");
      }
      
}

void loop() { 

// open file
      myFile = SD.open(Textfile, FILE_WRITE);

//   put your main code here, to run repeatedly:
///////////////////////////////////////////////////////
//use myFile.print() wherever you want to save to SD -- Works the same as Serial.print()





//////////////////////////////////////////////////////
     myFile.close();

}

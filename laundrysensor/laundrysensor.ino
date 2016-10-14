#include <SoftwareSerial.h>
#include <TimeLib.h>

SoftwareSerial wifi(11, 10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(11, INPUT);
  pinMode(10, OUTPUT);
 
  Serial.write("Starting\r\n");
  
  wifi.begin(9600);
  while (!wifi)
  {
  }
  wifi.setTimeout(250);
}

void loop() {
  String input = "";
 
  if ( wifi.available() > 0)
  {
    input = wifi.readString();
   
    if (input.length() == 3)
    {
      if (input[0] == '0' || input[0] == '3' && input[1] == '\r' && input[2] == '\n')
      {

        int value = 0;
        for (int i = 0; i < 25; i++)
        {
          value += analogRead(input[0] == '0' ? 0 : 3);
          delay(1);
        }
        
        wifi.println(value/25);
      }
    }
  }

  delay(250);
}

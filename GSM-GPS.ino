#include <TinyGPS.h>
#include <SoftwareSerial.h>
SoftwareSerial Gsm(7, 8); // rx - 8, tx - 7
char phone_no[] = "##########"; //replace with phone no. to get sms
 
TinyGPS gps;  //Creates a new instance of the TinyGPS object


int button =6;
 
void setup()
{
  Serial.begin(9600);
  Gsm.begin(9600);  
 
}
 
void loop()
{

  if (digitalRead(button) == HIGH)
  {


    Gsm.print("AT+CMGF=1\r"); 
    delay(400);
    Gsm.print("AT+CMGS=\"");
    Gsm.print(phone_no);
    Gsm.println("\"");
    
    delay(300);
    Gsm.print("This is a SOS message. Please tap the link following this message for directions");
    Serial.print(",");
    delay(200);
    Gsm.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    Gsm.println();
    delay(10000);


    bool newData = false;
    unsigned long chars;
    unsigned short sentences, failed;
 
    // For one second we parse GPS data and report some key values
    for (unsigned long start = millis(); millis() - start < 1000;)
    {
      while (Serial.available())
      {
        char c = Serial.read();
        Serial.print(c);
        if (gps.encode(c)) 
          newData = true;  
      }
    }
 
    if (newData)      //If newData is true
    {
      float flat, flon;
      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);   
      Gsm.print("AT+CMGF=1\r"); 
      delay(400);
      Gsm.print("AT+CMGS=\"");
      Gsm.print(phone_no);
      Gsm.println("\"");
    
      delay(300);
      Gsm.print("Tap on this link for location: ");
      Gsm.print("http://maps.google.com/maps?q=loc:");
    
    // Gsm.print("Latitude = ");
      Gsm.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    //Gsm.print(" Longitude = ");
      Serial.print(",");
      Gsm.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
      delay(200);
      Gsm.println((char)26); // End AT command with a ^Z, ASCII code 26
      delay(200);
      Gsm.println();
      delay(20000);


  
    }
  }

  else
  {  
    bool newData = false;
    unsigned long chars;
    unsigned short sentences, failed;
 
    // For one second we parse GPS data and report some key values
    for (unsigned long start = millis(); millis() - start < 1000;)
    {
      while (Serial.available())
      {
        char c = Serial.read();
        Serial.print(c);
        if (gps.encode(c)) 
          newData = true;  
      }
    } 
 
    if (newData)      //If newData is true
    {
       float flat, flon;
      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);   
      Gsm.print("AT+CMGF=1\r"); 
      delay(400);
      Gsm.print("AT+CMGS=\"");
      Gsm.print(phone_no);
      Gsm.println("\"");
    
      delay(300);
      Gsm.print("http://maps.google.com/maps?q=loc:");
    
    // Gsm.print("Latitude = ");
      Gsm.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
      //Gsm.print(" Longitude = ");
      Serial.print(",");
      Gsm.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
      delay(200);
      Gsm.println((char)26); // End AT command with a ^Z, ASCII code 26
      delay(200);
      Gsm.println();
      delay(20000);
 
    }
 
    Serial.println(failed);
 // if (chars == 0)
   // Serial.println("** No characters received from GPS: check wiring **");
  }
}

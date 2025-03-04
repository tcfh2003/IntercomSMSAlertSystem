#include <SoftwareSerial.h>

#define SIM_RX 14
#define SIM_TX 15
#define BUTTON 19

SoftwareSerial SIMSerial(SIM_RX, SIM_TX);
const String phoneNumber = "+40741xxxxxx";

void setup(){
  Serial.begin(9600);
  Serial.println("Initializing...");
  pinMode(BUTTON, INPUT);
  SIMSerial.begin(9600);
  delay(500);

  SIMSerial.println("AT");          // check if SIM module is on
  printSIMSerial();
  SIMSerial.println("ATI");         // check SIM module model
  printSIMSerial();
  SIMSerial.println("AT+CMGF=1");   // set SIM module SMS format to ASCII
  printSIMSerial();
  
  sendSMS("Initialization Successful");
}

void loop(){
  if(digitalRead(BUTTON) == HIGH){
    sendSMS("Button was pressed! Alarm Triggered!");
  }
}

void printSIMSerial(){
  while(SIMSerial.available() != 0){
    Serial.println(SIMSerial.read());
  }
}

void sendSMS(String smsText){
  Serial.println("Send SMS: " + smsText);
  SIMSerial.println("AT+CMGS=\"" + phoneNumber + "\"");
  printSIMSerial();
  SIMSerial.println(smsText);
  printSIMSerial();
  SIMSerial.println((char)26)       // Send SUB char = Ctrl + Z
  printSIMSerial();
}
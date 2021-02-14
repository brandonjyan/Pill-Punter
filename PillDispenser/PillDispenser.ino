#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <WiFiServer.h>



//Code from the Arduino example programs "AP_SimpleWebServer" and "WiFiWebServer"
//Arduino controls which gets data over wifi to control the pill releasing mechanisms

#include "Arduino.h"
#include "ESP8266.h"
#include "Servo.h"
#include "StepperMotor.h"

// Pin Definitions
#define WIFI_PIN_TX  11
#define WIFI_PIN_RX 10
#define SERVOSM_PIN_SIG 2
#define STEPPER_PIN_STEP  4
#define STEPPER_PIN_DIR 3

// object initialization
ESP8266 wifi(WIFI_PIN_RX,WIFI_PIN_TX);
Servo servoSM;
StepperMotor stepper(STEPPER_PIN_STEP,STEPPER_PIN_DIR);

// stepper vars
const int servoSMRestPosition   = 0;  //Starting position
const int servoSMTargetPosition = 100; //Position when event is detected

// wifi 
char ssid[] = "WIFI-SSID";      // your network SSID (name)
char pass[] = "PASSWORD";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS; //status of wifi
WiFiServer server(80); //declare server object and spedify port, 80 is port used for internet

void setup() {
  //Uncomment serial for debugging and to see details of WiFi connection
 // Serial.begin(9600);
 // while (!Serial) {
     // wait for serial port to connect. Needed for native USB port only
//  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
  //  Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
 //   Serial.print("Attempting to connect to SSID: ");
 //   Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();
  // you're connected now, so print out the status:
 // printWifiStatus();

  // attach servo on pin 9 to the servo object
  servoSM.attach(SERVOSM_PIN_SIG);
  servoSM.write(servoSMRestPosition);
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
   // Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
       // Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Value at A0 is ");
            client.print(analogRead(A0));
            client.print("<br>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was GET /0, /1, /2, /3, or /4:
        if (currentLine.endsWith("GET /0")) {
          stepper.step(1, 1000);     // GET /0 spins the motor to move the head to the 1st column, pushes the pill in the 1st column, and spins the head back to the original position
          servoSM.write(servoSMTargetPosition);
          delay(500);
          servoSM.write(servoSMRestPosition);
          delay(500);                               
          stepper.step(0, 1000); 
        }
        if (currentLine.endsWith("GET /1")) {
          stepper.step(1, 2000);     // GET /1 spins the motor to move the head to the 2nd column, pushes the pill in the 2nd column, and spins the head back to the original position
          servoSM.write(servoSMTargetPosition);
          delay(500);
          servoSM.write(servoSMRestPosition);
          delay(500);                               
          stepper.step(0, 2000); 
        }
        if (currentLine.endsWith("GET /2")) { 
          stepper.step(1, 3000);     // GET /2 spins the motor to move the head to the 3rd column, pushes the pill in the 3rd column, and spins the head back to the original position
          servoSM.write(servoSMTargetPosition);
          delay(500);
          servoSM.write(servoSMRestPosition);
          delay(500);                               
          stepper.step(0, 3000); 
        }
        if (currentLine.endsWith("GET /3")) {
          stepper.step(1, 4000);     // GET /3 spins the motor to move the head to the 4th column, pushes the pill in the 4th column, and spins the head back to the original position
          servoSM.write(servoSMTargetPosition);
          delay(500);
          servoSM.write(servoSMRestPosition);
          delay(500);                               
          stepper.step(0, 4000); 
        }
        if (currentLine.endsWith("GET /4")) {     
          stepper.step(1, 5000);     // GET /4 spins the motor to move the head to the 5th column, pushes the pill in the 5th column, and spins the head back to the original position
          servoSM.write(servoSMTargetPosition);
          delay(500);
          servoSM.write(servoSMRestPosition);
          delay(500);                               
          stepper.step(0, 5000); 
        }
    }
    // close the connection:
    client.stop();
   // Serial.println("client disconnected");
  }
}}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

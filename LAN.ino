/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <RCSwitch.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);
RCSwitch mySwitch = RCSwitch();

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
String readString;

int led1pin = 39;
int led2pin = 37;
int led3pin = 35;
int led4pin = 31;
int led5pin = 29;
int led6pin = 27;
int led7pin = 25;
int led8pin = 23;

bool ledState1 = false;
bool ledState2 = false;
bool ledState3 = false;
bool ledState4 = false;
bool ledState5 = false;
bool ledState6 = false;
bool ledState7 = false;
bool ledState8 = false;


int data;

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // star
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  mySwitch.enableReceive(0);
  
  pinMode(led1pin, OUTPUT); 
  pinMode(led2pin, OUTPUT);
  pinMode(led3pin, OUTPUT);
  pinMode(led4pin, OUTPUT);
  pinMode(led5pin, OUTPUT);
  pinMode(led6pin, OUTPUT);
  pinMode(led7pin, OUTPUT);
  pinMode(led8pin, OUTPUT);

}

void loop()
{
  
  
  if (mySwitch.available() > 0){
    data = mySwitch.getReceivedValue(); 
    Serial.println(data);
    remoteControl();
    mySwitch.resetAvailable();
  }
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)

  {
    Serial.println("new client");

    while (client.connected())
    {
      if (client.available())

      {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100)

        {
          Serial.println(digitalRead(led1pin));
          
          //store characters to string
          readString += c;
          //Serial.print(c);


          Serial.write(c);
          // if you've gotten to the end of the line (received a newline
          // character) and the line is blank, the http request has ended,
          // so you can send a reply
          //if HTTP request has ended
          if (c == '\n') {
            Serial.println(readString); //print to serial monitor for debuging
//--------------------------------------------------------------------------------------------------------
// Needed to Display Site:
client.println("HTTP/1.1 200 OK"); //send new page
            client.println("Content-Type: text/html");
            client.println();
            client.println("<HTML>");
            client.println("<HEAD>");
            client.print("<script>setTimeout(function(){window.location.href='/'}, 10000)</script>");

//--------------------------------------------------------------------------------------------------------
//-------------------------------------------------

 

            client.println("<TITLE>Home Automation</TITLE>");

            //STYLE CSS
            client.println("<style>");
            client.println("@media (min-width: 360px)");
            client.println("{");
            client.println("button{font-size: 50px; margin-left: 10px; margin-bottom: 20px;}");
            client.println("h2{font-size: 50px; margin-left: 10px}");
            client.println("h1{font-size: 70px}");
            client.println("}");
            client.println("</style>");
            
            client.println("</HEAD>");
            client.println("<BODY>");
            
            client.println("<h1>Remote Switch Control</h1>");

            //DEFINING BUTTONS
            //SWITCH 1
            client.println("<div style='display: flex'>");
            client.println("<h2>Switch 1</h2>");
            client.println("<button onclick='window.location.href=\"/?light1on\"\'>ON</button>");
            client.println("<button onclick='window.location.href=\"/?light1off\"\'>OFF</button>");
            lightHandler();
            (ledState1 == true) ? client.println("<h2 style='margin-left: 10px'>ON</h2>") 
            : client.println("<h2 style='margin-left: 10px'>OFF</h2>");
            client.println("</div>");

            //SWITCH 2
            client.println("<div style='display: flex'>");
            client.println("<h2>Switch 2</h2>");
            client.println("<button onclick='window.location.href=\"/?light2on\"\'>ON</button>");
            client.println("<button onclick='window.location.href=\"/?light2off\"\'>OFF</button>");
            lightHandler();
            (ledState2 == true) ? client.println("<h2 style='margin-left: 10px'>ON</h2>") 
            : client.println("<h2 style='margin-left: 10px'>OFF</h2>");
            client.println("</div>");

            //SWITCH 3
            client.println("<div style='display: flex'>");
            client.println("<h2>Switch 3</h2>");
            client.println("<button onclick='window.location.href=\"/?light3on\"\'>ON</button>");
            client.println("<button onclick='window.location.href=\"/?light3off\"\'>OFF</button>");
            lightHandler();
            (ledState3 == true) ? client.println("<h2 style='margin-left: 10px'>ON</h2>") 
            : client.println("<h2 style='margin-left: 10px'>OFF</h2>");
            client.println("</div>");
            
            //SWITCH 4
            client.println("<div style='display: flex'>");
            client.println("<h2>Switch 4</h2>");
            client.println("<button onclick='window.location.href=\"/?light4on\"\'>ON</button>");
            client.println("<button onclick='window.location.href=\"/?light4off\"\'>OFF</button>");
            lightHandler();
            (ledState4 == true) ? client.println("<h2 style='margin-left: 10px'>ON</h2>") 
            : client.println("<h2 style='margin-left: 10px'>OFF</h2>");
            client.println("</div>");

            //SWITCH 5
            client.println("<div style='display: flex'>");
            client.println("<h2>Switch 5</h2>");
            client.println("<button onclick='window.location.href=\"/?light5on\"\'>ON</button>");
            client.println("<button onclick='window.location.href=\"/?light5off\"\'>OFF</button>");
            lightHandler();
            (ledState5 == true) ? client.println("<h2 style='margin-left: 10px'>ON</h2>") 
            : client.println("<h2 style='margin-left: 10px'>OFF</h2>");
            client.println("</div>");

            //SWITCH 6
            client.println("<div style='display: flex'>");
            client.println("<h2>Switch 6</h2>");
            client.println("<button onclick='window.location.href=\"/?light6on\"\'>ON</button>");
            client.println("<button onclick='window.location.href=\"/?light6off\"\'>OFF</button>");
            lightHandler();
            (ledState6 == true) ? client.println("<h2 style='margin-left: 10px'>ON</h2>") 
            : client.println("<h2 style='margin-left: 10px'>OFF</h2>");
            client.println("</div>");

            //SWITCH 7
            client.println("<div style='display: flex'>");
            client.println("<h2>Switch 7</h2>");
            client.println("<button onclick='window.location.href=\"/?light7on\"\'>ON</button>");
            client.println("<button onclick='window.location.href=\"/?light7off\"\'>OFF</button>");
            lightHandler();
            (ledState7 == true) ? client.println("<h2 style='margin-left: 10px'>ON</h2>") 
            : client.println("<h2 style='margin-left: 10px'>OFF</h2>");
            client.println("</div>");

            //SWITCH 8
            client.println("<div style='display: flex'>");
            client.println("<h2>Switch 8</h2>");
            client.println("<button onclick='window.location.href=\"/?light8on\"\'>ON</button>");
            client.println("<button onclick='window.location.href=\"/?light8off\"\'>OFF</button>");
            lightHandler();
            (ledState8 == true) ? client.println("<h2 style='margin-left: 10px'>ON</h2>") 
            : client.println("<h2 style='margin-left: 10px'>OFF</h2>");
            client.println("</div>");

            client.println("<div style='display: flex'>");
            client.println("<h2>All switchs</h2>");
            client.println("<button onclick='window.location.href=\"/?lightallon\"\'>ON</button>");
            client.println("<button onclick='window.location.href=\"/?lightalloff\"\'>OFF</button>");
            client.println("</div>");


    
            
            client.println("</BODY>");
            client.println("</HTML>");

            delay(1);
            //stopping client
            client.stop();

            
            //-------------------------------------------------
            // Code which needs to be Implemented:
            



            //clearing string for next read
            readString="";

            // give the web browser time to receive the data
            delay(1);
            // close the connection:
            client.stop();
            Serial.println("client disonnected");

          }
        }
      }
    }
  }
}

void lightHandler(){
  //SWITCH 1
  if(readString.indexOf("?light1on") >0)//checks for on
            {
              digitalWrite(led1pin, HIGH); 
              ledState1 = true;// set pin 8 high
            }
            else{
              if(readString.indexOf("?light1off") >0)//checks for off
              {
                digitalWrite(led1pin, LOW);
                ledState1 = false;
              }
            }

   //SWITCH 2

   if(readString.indexOf("?light2on") >0)//checks for on
            {
              digitalWrite(led2pin, HIGH); 
              ledState2 = true;
            }
            else{
              if(readString.indexOf("?light2off") >0)//checks for off
              {
                digitalWrite(led2pin, LOW); 
                ledState2 = false;   
              }
            }
    //SWITCH 3
    if(readString.indexOf("?light3on") >0)//checks for on
            {
              digitalWrite(led3pin, HIGH);
              ledState3 = true;
            }
            else{
              if(readString.indexOf("?light3off") >0)//checks for off
              {
                digitalWrite(led3pin, LOW);
                ledState3 = false;// set pin 8 low
              }
            }
    //SWITCH 4
    if(readString.indexOf("?light4on") >0)//checks for on
            {
              digitalWrite(led4pin, HIGH);
              ledState4 = true;
            }
            else{
              if(readString.indexOf("?light4off") >0)//checks for off
              {
                digitalWrite(led4pin, LOW);  
                ledState4 = false;// set pin 8 low
              }
            }
    //SWITCH 5
    if(readString.indexOf("?light5on") >0)//checks for on
            {
              digitalWrite(led5pin, HIGH);
              ledState5 = true;
            }
            else{
              if(readString.indexOf("?light5off") >0)//checks for off
              {
                digitalWrite(led5pin, LOW);  
                ledState5 = false;
              }
            }
    //SWITCH 6
    if(readString.indexOf("?light6on") >0)//checks for on
            {
              digitalWrite(led6pin, HIGH);
              ledState6 = true;
            }
            else{
              if(readString.indexOf("?light6off") >0)//checks for off
              {
                digitalWrite(led6pin, LOW);
                ledState6 = false;
              }
            }

    //SWITCH 7
    if(readString.indexOf("?light7on") >0)//checks for on
            {
              digitalWrite(led7pin, HIGH);
              ledState7 = true;
            }
            else{
              if(readString.indexOf("?light7off") >0)//checks for off
              {
                digitalWrite(led7pin, LOW);
                ledState7 = false;
              }
            }
   //SWITCH 8
    if(readString.indexOf("?light8on") >0)//checks for on
            {
              digitalWrite(led8pin, HIGH);
              ledState8 = true;
            }
            else{
              if(readString.indexOf("?light8off") >0)//checks for off
              {
                digitalWrite(led8pin, LOW);
                ledState8 = false;
              }
            }
    //All light
     if(readString.indexOf("?lightallon") >0)//checks for on
            {
              digitalWrite(led1pin, HIGH);
              digitalWrite(led2pin, HIGH);
              digitalWrite(led3pin, HIGH);
              digitalWrite(led4pin, HIGH);
              digitalWrite(led5pin, HIGH);
              digitalWrite(led6pin, HIGH);
              digitalWrite(led7pin, HIGH);
              digitalWrite(led8pin, HIGH);

              ledState1 = true;
              ledState2 = true;
              ledState3 = true;
              ledState4 = true;
              ledState5 = true;
              ledState6 = true;
              ledState7 = true;
              ledState8 = true;
            }
            else{
              if(readString.indexOf("?lightalloff") >0)//checks for off
              {
                digitalWrite(led1pin, LOW);
                digitalWrite(led2pin, LOW);
                digitalWrite(led3pin, LOW);
                digitalWrite(led4pin, LOW);
                digitalWrite(led5pin, LOW);
                digitalWrite(led6pin, LOW);
                digitalWrite(led7pin, LOW);
                digitalWrite(led8pin, LOW);

                ledState1 = false;
                ledState2 = false;
                ledState3 = false;
                ledState4 = false;
                ledState5 = false;
                ledState6 = false;
                ledState7 = false;
                ledState8 = false;
              }
            }


}

void remoteControl(){
  (data == 21952) ? ledState1 = !ledState1 : Serial.println("No");
    (data == 21808) ? ledState2 = !ledState2 : Serial.println("No");
    (data == 22000) ? ledState3 = !ledState3 : Serial.println("No");
    (data == 21772) ? ledState4 = !ledState4 : Serial.println("No");
    (data == 21964) ? ledState5 = !ledState5 : Serial.println("No");
    (data == 21820) ? ledState6 = !ledState6 : Serial.println("No");

    
    (ledState1 == true) ? digitalWrite(led1pin, HIGH) : digitalWrite(led1pin, LOW);
    (ledState2 == true) ? digitalWrite(led2pin, HIGH) : digitalWrite(led2pin, LOW);
    (ledState3 == true) ? digitalWrite(led3pin, HIGH) : digitalWrite(led3pin, LOW);
    (ledState4 == true) ? digitalWrite(led4pin, HIGH) : digitalWrite(led4pin, LOW);
    (ledState5 == true) ? digitalWrite(led5pin, HIGH) : digitalWrite(led5pin, LOW);
    (ledState6 == true) ? digitalWrite(led6pin, HIGH) : digitalWrite(led6pin, LOW);
    (ledState7 == true) ? digitalWrite(led7pin, HIGH) : digitalWrite(led7pin, LOW);
    (ledState8 == true) ? digitalWrite(led8pin, HIGH) : digitalWrite(led8pin, LOW);
    
    if(data == 22012){
      digitalWrite(led1pin, HIGH);
      digitalWrite(led2pin, HIGH);
      digitalWrite(led3pin, HIGH);
      digitalWrite(led4pin, HIGH);
      digitalWrite(led5pin, HIGH);
      digitalWrite(led6pin, HIGH);
      digitalWrite(led7pin, HIGH);
      digitalWrite(led8pin, HIGH);

      ledState1 = true;
      ledState2 = true;
      ledState3 = true;
      ledState4 = true;
      ledState5 = true;
      ledState6 = true;
      ledState7 = true;
      ledState8 = true;
    }
    if(data == 21763){
      digitalWrite(led1pin, LOW);
      digitalWrite(led2pin, LOW);
      digitalWrite(led3pin, LOW);
      digitalWrite(led4pin, LOW);
      digitalWrite(led5pin, LOW);
      digitalWrite(led6pin, LOW);
      digitalWrite(led7pin, LOW);
      digitalWrite(led8pin, LOW);

      ledState1 = false;
      ledState2 = false;
      ledState3 = false;
      ledState4 = false;
      ledState5 = false;
      ledState6 = false;
      ledState7 = false;
      ledState8 = false;
      
    }

   delay(500);
  
}

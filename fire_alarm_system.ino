#include <ESP8266WiFi.h>

float temp;
float vout;
float vout1;
int piezo = 5; // GPIO5 --- D1 of NodeMCU
int gasSensor;

const char* ssid = "Galaxy A1281F9"; 
const char* password = "00000001";
int ledPin = 13; // GPIO13 --- D7 of NodeMCU
WiFiServer server(80);

void setup(){
  Serial.begin(115200);
  delay(10);
  
  pinMode(A0, INPUT);
  pinMode(D0, INPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(piezo, OUTPUT);

  //Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("connecting...");
    }
  Serial.println("");
  Serial.println("WiFi connected");

  //Start the server
  server.begin();
  Serial.println("Server Started");

  //Print the IP address

  Serial.print("Use this URL to Connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  //Check if a client has connected
  WiFiClient client = server.available();
  if (!client){
    return;
  }

  //Wait until the client sends some data
  Serial.println("new client");
    while(!client.available()){
        delay(1);
  }
  // Read the first line of the request 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  vout = analogRead(D0);
  vout1 = (vout / 1023) * 5000;
  temp = (vout1 - 500) / 10;
  gasSensor = analogRead(A0);

  //Match the request
  int value = LOW;
  
  if(temp >= 80){
    digitalWrite(piezo, HIGH);
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(piezo, LOW);
    digitalWrite(ledPin, LOW);
  }
  
  if (gasSensor >= 200) {
    digitalWrite(piezo, HIGH);
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(piezo, LOW);
    digitalWrite(ledPin, LOW);
  }

  Serial.print("current temperature = ");
  Serial.print(" ");
  Serial.print(temp);
  Serial.print("\t");
  Serial.print("GasSensor = ");
  Serial.print(" ");
  Serial.print(gasSensor);
  Serial.println();
  delay(1000);

  if (request.indexOf("/piezo=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(piezo, HIGH);
    value = HIGH;
  }
  if (request.indexOf("piezo=OFF") != -1) {
    digitalWrite(ledPin, LOW);
    digitalWrite(piezo, LOW);
    value = LOW;
  }

  // client side interface

  //Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1>IoT Based Fire Detection System</h1>");
  client.print("Buzzer is now: ");
  
  if (value == HIGH) {
    client.print("ON");
  } else {
    client.print("OFF");
  }

  client.println("<br><br>");
  client.println("<a href=\"/piezo=ON\"><button>ON</button></a>");
  client.println("<a href=\"/piezo=OFF\"><button>OFF</button></a><br />");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

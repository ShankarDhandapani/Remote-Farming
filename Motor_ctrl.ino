#include <ESP8266WiFi.h>
//#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
//#include <CayenneWiFi.h>

 
const char* ssid = "Shankar";
const char* password = "15111998";
//char token[] = "olpzanp83c";
 
int ledPin = D5;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  //Cayenne.begin(token, ssid, password);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
   //Cayenne.run();
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/MOTOR=OFF") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/MOTOR=ON") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Motor status: ");
 
  if(value == HIGH) {
    client.print("OFF");  
  } else {
    client.print("ON");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/MOTOR=ON\">here</a> turn the Motor ON<br>");
  //client.println("click <button type="button"> Motor ON  </button> to");
  client.println("Click <a href=\"/MOTOR=OFF\">here</a> turn the Motor OFF<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}

#include <ESP8266WiFi.h>

// WiFi parameters
const char* ssid = "Shankar";
const char* password = "15111998";

// Pin
#define SoilSensor A0

// Host
const char* host = "dweet.io";

void setup() {

  // Start Serial
  Serial.begin(115200);
  pinMode(SoilSensor,INPUT);
  delay(10);
  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  Serial.print("Connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // Reading temperature and humidity
  int Moisture_level = analogRead(A0); 

  // This will send the request to the server
  client.print(String("GET /dweet/for/sample_test?Moisture_level=") + String(Moisture_level) + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");

  // Repeat every 10 seconds
  delay(1000);

}

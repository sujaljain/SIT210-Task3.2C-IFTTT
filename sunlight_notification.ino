#include <Wire.h>
#include <WiFiNINA.h>

const int lytSensor = A0;  // Analog pin for the light sensor

char ssid[] = "Sujal Jain";      // Your WiFi SSID
char pass[] = "12345678";  // Your WiFi password
int status = WL_IDLE_STATUS;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  pinMode(lytSensor, INPUT);
  connectWiFi();
}

void loop() {
  int lightValue = analogRead(lytSensor);
  
  if (lightValue < 500) { // Taken 500 as threshold value for light
    sendNotification("Sunlight Detected!!");
  } else {
    sendNotification("No Sunlight");
  }
  
  delay(1000);  // Check sunlight every second
}

void connectWiFi() {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WiFi...");
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  Serial.println("Connected to WiFi");
}

void sendNotification(String message) {
  // Use the WiFi client to send a request to the IFTTT webhook
  if (client.connect("maker.ifttt.com", 80)) {
    client.print("GET /trigger/sunlight_detector/with/key/n_GjpfhZBXNGkTrQfi9isWgEnBrKM8pBz7aeUl67Cfc?value1=");
    client.print(message);
    client.println(" HTTP/1.1");
    client.println("Host: maker.ifttt.com");
    client.println("Connection: close");
    client.println();
  }
  delay(1000);  // Waiting for the server to respond
  client.stop();
}

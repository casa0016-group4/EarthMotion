#include <WiFiNINA.h>
#include <PubSubClient.h>

// Replace with your network credentials
const char* ssid = "CE-Hub-Student";
const char* password = "casa-ce-gagarin-public-service";

// MQTT Broker details
const char* mqtt_server = "mqtt.cetools.org";
const int mqtt_port = 1883;  // Use port 1883 for standard MQTT protocol

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  // Start the Serial communication
  Serial.begin(9600);

  // Connect to WiFi
  setup_wifi();

  // Setup MQTT callbacks and connect
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void setup_wifi() {
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  String messageTemp;

  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  
  Serial.println(messageTemp);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");

      // Subscribe to topics
      client.subscribe("student/CASA0019/G4/magnitude");
      client.subscribe("student/CASA0019/G4/location");
      client.subscribe("student/CASA0019/G4/time");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
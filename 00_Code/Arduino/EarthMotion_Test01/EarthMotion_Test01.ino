#include <WiFiNINA.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// Replace with your network credentials
const char* ssid = "CE-Hub-Student";
const char* password = "casa-ce-gagarin-public-service";

// MQTT Broker details
const char* mqtt_server = "mqtt.cetools.org";
const int mqtt_port = 1883;  // Use port 1883 for standard MQTT protocol

WiFiClient wifiClient;
PubSubClient client(wifiClient);

LiquidCrystal lcd(7, 8, 5, 4, 3, 2);

char locationMessage[64];  // Assuming maximum length for location
char magnitudeMessage[16];  // Assuming maximum length for magnitude and LCD can display 16 characters

Servo myServo1;
const int servoPin = 9;  // Pin to which you connect the servo

Servo myServo2;
const int servoPin2 = 10;  // Pin to which you connect the second servo

void setup() {
  Serial.begin(9600);

  // Connect to WiFi
  setup_wifi();

  // Setup MQTT callbacks and connect
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  lcd.begin(16, 2);

  myServo1.attach(servoPin);
  myServo2.attach(servoPin2);  // Add this line to assign a pin for the second servo
}

void setup_wifi() {
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

  // Update LCD display
  if (strcmp(topic, "student/CASA0019/G4/location") == 0) {
    strncpy(locationMessage, messageTemp.c_str(), sizeof(locationMessage));
  } else if (strcmp(topic, "student/CASA0019/G4/magnitude") == 0) {
    // Use toFloat() to convert the string to a floating-point number
    float magnitudeValue = messageTemp.toFloat();

    // Use dtostrf() to convert the floating-point number to a string, keeping 2 decimal places
    dtostrf(magnitudeValue, 3, 2, magnitudeMessage);

    // Truncate the string to fit the LCD
    magnitudeMessage[15] = '\0';  // Assuming the LCD can display only 16 characters
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(locationMessage);

  lcd.setCursor(0, 1);
  lcd.print("Magnitude: ");
  lcd.print(magnitudeMessage);

  // Delay for a period of time
  delay(5000);

  if (strcmp(topic, "student/CASA0019/G4/magnitude") == 0) {
    // Use toFloat() to convert the string to a floating-point number
    float magnitudeValue = messageTemp.toFloat();

    // Control servo angle based on your requirements, adjust the mapping relationship accordingly
    int servoAngle = map(magnitudeValue, 0, 9.0, 0, 90);
    myServo1.write(servoAngle);
    myServo2.write(servoAngle);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("arduinoClient")) {
      Serial.println("connected");

      client.subscribe("student/CASA0019/G4/magnitude");
      client.subscribe("student/CASA0019/G4/location");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Scroll and display location from left to right
  scrollText(("Location:" + String(locationMessage)).c_str(), 0, 0, true);

  lcd.setCursor(0, 1);
  lcd.print("Magnitude: " + String(magnitudeMessage));

  // Scroll and display location from right to left
  scrollText(("Location:" + String(locationMessage)).c_str(), 0, 0, false);

  // Delay for a period of time
  delay(200);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Delay for a period of time
  delay(200);
}

void scrollText(const char* text, int x, int y, bool leftToRight) {
  int textLength = strlen(text);

  if (leftToRight) {
    for (int i = 0; i <= textLength; i++) {
      lcd.setCursor(x, y);
      lcd.print(text + i);

      // Delay for a period of time to control the scrolling speed
      delay(300);

      // Clear the current position
      lcd.setCursor(x, y);
      for (int j = 0; j < strlen(text + i); j++) {
        lcd.print(" ");
      }
      
      // Delay for a period of time to maintain the current position display
      delay(100);
    }
  } else {
    for (int i = textLength - 1; i >= 0; i--) {
      lcd.setCursor(x, y);
      lcd.print(text + i);

      // Delay for a period of time to control the scrolling speed
      delay(300);

      // Clear the current position
      lcd.setCursor(x, y);
      for (int j = 0; j < strlen(text + i); j++) {
        lcd.print(" ");
      }

      // Delay for a period of time to maintain the current position display
      delay(100);
    }
  }
}

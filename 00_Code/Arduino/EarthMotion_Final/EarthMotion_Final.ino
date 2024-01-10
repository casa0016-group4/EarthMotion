#include <WiFiNINA.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

// Replace with your network credentials
const char* ssid = "SECRET_SSID";
const char* password = "SECRET_PASSWORD";

// MQTT Broker details
const char* mqtt_server = "mqtt.cetools.org";
const int mqtt_port = 1883;  // Use port 1883 for standard MQTT protocol

WiFiClient wifiClient;
PubSubClient client(wifiClient);

LiquidCrystal lcd(7, 8, 5, 4, 3, 2);

char locationMessage[64];  // Assuming maximum length for location
char magnitudeMessage[16];  // Assuming maximum length for magnitude, and LCD can display 16 characters

Servo myServo1;
const int servoPin = 9;  // Pin to which you connect the first servo

Servo myServo2;
const int servoPin2 = 10;  // Pin to which you connect the second servo

#define LED_PIN    13  // Replace with the data input pin of your LED strip
#define NUMPIXELS  60  // Replace with the number of pixels in your LED strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

const int buzzerPin = 12;  // Replace with the pin to which you connect the buzzer

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

  // Initialize the LED strip
  strip.begin();
  strip.show();  // Initialize all pixels to off

  // Initialize the buzzer
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);  // Initial state: buzzer off
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

// Declare the setColor function
void setColor(int red, int green, int blue);

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

  // Delay for a certain period
  delay(5000);

  if (strcmp(topic, "student/CASA0019/G4/magnitude") == 0) {
    // Use toFloat() to convert the string to a floating-point number
    float magnitudeValue = messageTemp.toFloat();

    // Control servo angle, adjust the mapping relationship according to your needs
    int servoAngle = map(magnitudeValue, 0, 9.0, 0, 90);
    myServo1.write(servoAngle);
    myServo2.write(servoAngle);

    // Control LED strip color
    if (magnitudeValue <= 3.0) {
      setColor(0, 5, 0);  // Green
    } else if (magnitudeValue <= 5.0) {
      setColor(5, 5, 0);  // Yellow
    } else {
      setColor(5, 0, 0);  // Red
      // If the magnitude value is greater than or equal to 5.0, turn on the buzzer
      digitalWrite(buzzerPin, HIGH);
    }
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

  // Scroll the location from left to right
  scrollText(("Location:" + String(locationMessage)).c_str(), 0, 0, true);

  lcd.setCursor(0, 1);
  lcd.print("Magnitude: " + String(magnitudeMessage));

  // Scroll the location from right to left
  scrollText(("Location:" + String(locationMessage)).c_str(), 0, 0, false);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Turn off the buzzer
  digitalWrite(buzzerPin, LOW);
}

void scrollText(const char* text, int x, int y, bool leftToRight) {
  int textLength = strlen(text);

  if (leftToRight) {
    for (int i = 0; i <= textLength; i++) {
      lcd.setCursor(x, y);
      lcd.print(text + i);

      // Delay for a certain period to control the scrolling speed
      delay(300);

      // Clear the current position
      lcd.setCursor(x, y);
      for (int j = 0; j < strlen(text + i); j++) {
        lcd.print(" ");
      }
      
      // Delay for a certain period to maintain the current position display
      delay(100);
    }
  } else {
    for (int i = textLength - 1; i >= 0; i--) {
      lcd.setCursor(x, y);
      lcd.print(text + i);

      // Delay for a certain period to control the scrolling speed
      delay(300);

      // Clear the current position
      lcd.setCursor(x, y);
      for (int j = 0; j < strlen(text + i); j++) {
        lcd.print(" ");
      }

      // Delay for a certain period to maintain the current position display
      delay(100);
    }
  }
}

// Function to set the color of the LED
void setColor(int red, int green, int blue) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue));
  }
  strip.show();
}

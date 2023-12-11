#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <LiquidCrystal.h>

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

void setup() {
  Serial.begin(9600);

  // Connect to WiFi
  setup_wifi();

  // Setup MQTT callbacks and connect
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  lcd.begin(16, 2);
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

  // 更新LCD显示
  if (strcmp(topic, "student/CASA0019/G4/location") == 0) {
    strncpy(locationMessage, messageTemp.c_str(), sizeof(locationMessage));
  } else if (strcmp(topic, "student/CASA0019/G4/magnitude") == 0) {
    // 使用 toFloat() 将字符串转换为浮点数
    float magnitudeValue = messageTemp.toFloat();

    // 使用 dtostrf() 将浮点数转换为字符串，保留2位小数
    dtostrf(magnitudeValue, 3, 2, magnitudeMessage);

    // 截断字符串以适应LCD
    magnitudeMessage[15] = '\0';  // 假设LCD上只能显示16个字符
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(locationMessage);

  lcd.setCursor(0, 1);
  lcd.print("Magnitude: ");
  lcd.print(magnitudeMessage);

  // 延时一段时间
  delay(5000);
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

  // 先从左到右滚动显示location
  scrollText(("Location:" + String(locationMessage)).c_str(), 0, 0, true);

  lcd.setCursor(0, 1);
  lcd.print("Magnitude: " + String(magnitudeMessage));

  // 再从右到左滚动显示location
  scrollText(("Location:" + String(locationMessage)).c_str(), 0, 0, false);

  // 延时一段时间
  delay(200);
}

void scrollText(const char* text, int x, int y, bool leftToRight) {
  int textLength = strlen(text);

  if (leftToRight) {
    for (int i = 0; i <= textLength; i++) {
      lcd.setCursor(x, y);
      lcd.print(text + i);

      // 延时一段时间，控制滚动速度
      delay(300);

      // 清空当前位置
      lcd.setCursor(x, y);
      for (int j = 0; j < strlen(text + i); j++) {
        lcd.print(" ");
      }
      
      // 延时一段时间，保持当前位置显示
      delay(100);
    }
  } else {
    for (int i = textLength - 1; i >= 0; i--) {
      lcd.setCursor(x, y);
      lcd.print(text + i);

      // 延时一段时间，控制滚动速度
      delay(300);

      // 清空当前位置
      lcd.setCursor(x, y);
      for (int j = 0; j < strlen(text + i); j++) {
        lcd.print(" ");
      }

      // 延时一段时间，保持当前位置显示
      delay(100);
    }
  }
}

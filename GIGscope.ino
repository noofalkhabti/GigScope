#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_WIFI";
const char* password = "PASSWORD";

const char* serverName = "https://gigscope-api.com/data";

int vehiclesDetected = 0;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {

  // مثال بيانات
  vehiclesDetected = random(5,50);

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{";
    jsonData += "\"city\":\"Riyadh\",";
    jsonData += "\"vehicles_detected\":" + String(vehiclesDetected);
    jsonData += "}";

    int httpResponseCode = http.POST(jsonData);

    Serial.println(httpResponseCode);

    http.end();
  }

  delay(10000);
}
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <store_single_time.h>
#include <WiFiClientSecure.h>




void http_post(int pointer) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient https;
    WiFiClientSecure wifiClient;
    wifiClient.setInsecure();


    const char* url = "https://api.aperol.life/chugs";

    // Specify the URL
    https.begin(wifiClient, url);

    // Specify content-type header
    https.addHeader("content-type", "application/json");

    // Send the POST request with the JSON data
    String jsonData = get_json_string(pointer);
    Serial.println(jsonData);
    int httpResponseCode = https.POST(jsonData);

    // Check the response code
    if (httpResponseCode > 0) {
      String response = https.getString();
      Serial.println(httpResponseCode); // HTTP response code
      Serial.println(response);         // Response from server
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    // End the connection
    https.end();
  } else {
    Serial.println("Error in WiFi connection");
  }

  // Wait for some time before sending the next request
  delay(10000);
}

void send_all_files() {
    for (int i = 0; i <= file_pointer; i++)
    {
        http_post(i);
    }
    
}

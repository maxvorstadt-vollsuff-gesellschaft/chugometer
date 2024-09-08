#include <ArduinoJson.h>
#include <store_single_time.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <HTTPClient.h>

bool http_post(int pointer) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient https;
    WiFiClientSecure *wifiClient = new WiFiClientSecure;
    wifiClient->setInsecure();

    const char* url = "https://api.aperol.life/chugs";

    // Specify the URL
    https.begin(*wifiClient, url);

    // Specify content-type header
    https.addHeader("content-type", "application/json");

    // Send the POST request with the JSON data
    String jsonData = get_json_string(pointer);
    Serial.println(jsonData);
    int httpResponseCode = https.POST(jsonData);

    // Check the response code
    if (httpResponseCode > 0) {
      String response = https.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
      if (httpResponseCode == 200) {
        https.end();
        delete wifiClient;
        return true;
      }
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
      return false;
    }
  } else {
    Serial.println("Error in WiFi connection");
    return false;
  }
  return false;
}

void send_all_files() {
    for (int i = 0; i <= file_pointer; i++)
    {
      if (http_post(i)) {
        Serial.print("success syncing file ");
        Serial.println(i);
        remove_json_file(i);
        init_json_file(i);
      } else {
        Serial.print("failed syncing file ");
        Serial.println(i);
      }
      delay(500);
    }
    
}

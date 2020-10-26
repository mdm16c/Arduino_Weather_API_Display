#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

char* ssid = "suddenlink.net-64CD";
char* password = "6CL2W4996600269";

#define API_KEY "cb6e62ec0c18cc3d61a9c5cbcafce516"
String currentWeather = "http://api.openweathermap.org/data/2.5/weather?q=London,uk&appid=" + String(API_KEY);

unsigned long lastTime = 0;
unsigned long timerDelay = 10000; //10 seconds

void setup()
{
  //wifi setup for http request
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("API Call will be made every " + String(timerDelay/1000) + " seconds.");
}

void loop()
{
  //runs once every 10 seconds
  if ((millis() - lastTime) > timerDelay) {
    
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      
      HTTPClient http;
      
      // open weather map api url
      http.begin(currentWeather.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();

      // if get request is successful
      // consider changing this to when it is equal to 200
      if (httpResponseCode > 0) {
        Serial.println("HTTP Response code: " + String(httpResponseCode));
        String jsonResponse = http.getString();
        Serial.println(jsonResponse);
      }
      //failed call
      else {
        Serial.println("Error code: " + String(httpResponseCode));
      }
      
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

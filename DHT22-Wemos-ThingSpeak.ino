/* Write up for Connecting a Wemos with a DHT Sensor to ThingSpeak
*  
*  Using a mixture of sources for the code make up.
* 
*  Uses information written by ladyada, and is public domain.
*  Additional commentary by Geoffrey Baum - 2016
*  
*  Depends on Adafruit DHT Arduino Library (not the Universal Library)
*  https://github.com.adafruit/DHT-sensor-library
*/

#include <DHT.h> // DHT.h library
#include <ESP8266WiFi.h> // ESP8266Wifi.h library

#define DHTPIN D4         // This is the Pin you are connecting the sensor to on the Wemos
#define DHTTYPE DHT22     // This can be changed if your are using a different DHT sensor

const char* ssid     = "WiFi_Network_Name";      // Change to be your WiFi networks name
const char* password = "WiFi_Password";         // Change to be your WiFi password
const char* host = "api.thingspeak.com";
const char* writeAPIKey = "CY6NNBAW26AB84SX";   // Change the XXXXXXX to your ThingSpeak writeAPI

DHT dht(DHTPIN, DHTTYPE, 15);

void setup() {
  // initialize sensor
  dht.begin();
   delay(1000);
   
 // Connect to WiFi network  
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

   if (isnan(humidity) || isnan(temperature)) {
    return;
   }

 // make TCP connections
   WiFiClient client;
   const int httpPort = 80;
   if (!client.connect(host, httpPort)) {
    return; 
   }

   String url = "/update?key=";
   url+=writeAPIKey;
   url+="&field1=";   
   url+=String(temperature);
   url+="&field2=";
   url+=String(humidity);
   url+="\r\n";

   // Request to the server
   client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");
     delay(1000);           

}

/* DHT Shield or Stand alone sensor for use with WEMOS sensor
 *  
 *  Uses information written by ladyada, and is public domain.
 *  Additional commentary by Geoffrey Baum - 2016
 *  
 *  Depends on Adafruit DHT Arduino Library (not the Universal Library)
 *  https://github.com.adafruit/DHT-sensor-library
 */
#include <DHT.h>
#define DHTPIN D4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302) If you are using different DHT sensor change this
                        // value to the appropriate one. I.e. DHT11 for the DHT 11 sensor
                        // or DHT21 for the DHT 21 (AM2301) sensors.

// Pin 1 is connected to power, Pin 2 is the DHTPIN, and Pin 4 is the GROUND.
  // NOTE: Remember if you are using a stand alone sensor and not a prefabricated board
  // that you will need to place a 10K resistor between pin 2 (data) and pin 1 (power).
  // 
  // Initialize the sensor.
 
DHT dht(DHTPIN, DHTTYPE);

 
 
void setup() 
{
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
}
 
void loop() 
{
  // Wait a few seconds between measurements.
  delay(60000);  // This is set for a minute delay but change it whichever value you prefer
                 // but remember these devices are a bit slow. So I'd recommend at least 250.
 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
 
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // If you want to compute the heat index in Farenheit (default) or Celsius uncomment the lines
  // below to allow you to get that data. This includes uncommenting the lines at the end of the
  // Serial.print section.
  
  //float hif = dht.computeHeatIndex(f, h);
  //float hic = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.println(" *F\t");
  //  Serial.print("Heat index: ");
  //  Serial.print(hic);
  //  Serial.print(" *C ");
  //  Serial.print(hif);
  //  Serial.println(" *F");
 
}

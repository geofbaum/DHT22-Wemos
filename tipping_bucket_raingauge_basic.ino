// This is an example that can be replicated for a homemade tipping bucket gauge
// or a gauge that is from one of the larger commercial home weather companies
// such as Davis or Rainwise among others. It simply requires that you are accessing
// a two wire system. This example was used with a Rainwise Rain Gauge and it will
// be updated with other examples to show how this type of system could be used for
// wireless transmission of the data plus hopefully also still allowing a simplistic
// datalogger to still be involved to allow for those always probable loss of connection
// between a sensor and whichever type of network you might want to connect to wirelessly.

const byte interruptPin = 3;
#define CALIBRATE_FACTOR 0.0254 // amount of rain per rain bucket tip e.g. 5 is .05mm
const int interval = 500;
volatile unsigned long tiptime = millis();

void setup(){
  Serial.begin(9600);

  // Set up our digital pin as an interrupt
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), count, FALLING);
}

void loop() {
}

volatile unsigned long rain_count=0;

// This next section is most likely unnecessary
double getUnitRain()
{

  unsigned long reading=rain_count;
  rain_count=1;
  double unit_rain=reading*0.254;
    
  return unit_rain;
}

void count() {
  // Grab the current ms count for common calculations
  unsigned long curtime = millis();
  
  // Make sure we don't record bounces
  if ((curtime - tiptime) < interval) {
    return;
  }

  // How long since the last tip?
  unsigned long tipcount = curtime - tiptime;
  tiptime = curtime;
  
  // Calculate mm/hr from period between cup tips
  double rainrate = 914400.0 / tipcount; // This number probably needs to be changed
  
  // Calculating rain amount based on each recorded tip
  // There is probably a better way to do this which I will update with in the future
  float rain = rain_count++;
  rain = rain * 0.0254;  // 0.0254 mm = 0.01 in resolution of the tippping bucket rain gauge
  
  Serial.print("Cup tip: ");
  Serial.print(tipcount);
  Serial.println("ms");  
  
  Serial.print("Rain rate: ");
  Serial.print(rainrate);
  Serial.println("mm/hr");  

  Serial.print("Rain total: ");
  Serial.print(rain, 4);
  Serial.println(" mm ");
}

#include<Wire.h>
#include <SparkFun_MicroPressure.h>
#include <HX711.h>

#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN 3

HX711 scale;
long initial_weight = 0;

SparkFun_MicroPressure mpr; // Use default values with reset and EOC pins unused
double Timer = 0;

void setup() {
  // Initalize UART, I2C bus, and connect to the micropressure sensor
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(1833);
  scale.tare(); //Reset the scale to 0
  initial_weight = -1 * scale.get_units();
  Serial.println("initial_weight = " + String(initial_weight));
  Wire.begin();
  mpr.begin();
  Timer = millis();
}

void loop() {
  if(millis() - Timer > 100){
    Timer = millis();
    Serial.println(String(Timer/1000.) + "," + String(mpr.readPressure(),4)+ "," + String(initial_weight + scale.get_units()));
  }
}

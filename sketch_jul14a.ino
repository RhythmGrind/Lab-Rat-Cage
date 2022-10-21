#include <DHT.h>

#define DHTPIN 3   
#define DHTTYPE DHT11  
#define fan 4
#define fans 5

int maxTemp = 60;
//Temperature Range: 0°C to 50°C. Humidity Range: 20% to 90%

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(fan, OUTPUT);
  pinMode(fans, OUTPUT);
  Serial.begin(9600); 
  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  if( t > maxTemp) {
      digitalWrite(fan, HIGH);
      digitalWrite(fans, HIGH);
  } else {
     digitalWrite(fan, LOW); 
     digitalWrite(fans, LOW); 
  }
  
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");

}

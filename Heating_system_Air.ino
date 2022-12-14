#include <DHT.h>

#define DHTPIN A0   
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

float ki,kd,kp;
float target_temp;
float current_temp;
float error;
float error_sum;
float last_error;
float m1p;
float Time = 0;
int T;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  error_sum = 0;
  last_error = 0;
  m1p = 0;
  pinMode(12,OUTPUT);
  pinMode(A0,INPUT);
 kp = 60;
 ki = 0.0001;
 kd = 0.1;
 target_temp = 33; 
 Time = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
// measure temperature
  delay(2000);
  float t = dht.readTemperature();
//current_temp=(-13.69+sqrt(4*(-0.047080247127421)*(T-16.748913849260685)+13.710444752632158*13.710444752632158))/ (2*(-0.047080247127421));

          error = target_temp - t;
          error_sum += error;
            m1p = kp * error + ki * error_sum + kd * (error - last_error);
              //Serial.print("Temperature: "); 
              Serial.println(t);
              //Serial.println(" *C ");
  
          // if(millis() - Time > 1000){
          //   Time = millis();
          //   Serial.println(current_temp);
//            Serial.println("current_temp = " + String(current_temp));
            //Serial.println("m1sp = " + String(m1p));
            // }
          
          // setting M1
          
          if (m1p > 0) {
            if ((m1p) > 1023){
              analogWrite(12,1023);
            }
            else{
              analogWrite(12,m1p);
            }
            
          }
          else {
            analogWrite(12,0);
          }
          
          last_error = error;
}

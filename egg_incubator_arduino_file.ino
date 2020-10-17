#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

int motor1_ena=3; //motor 
int motor1_in1=4;
int motor1_in2=5;

int motor1_enb=6;//coolfan
int motor1_in3=7;
int motor1_in4=8;


int relaypin=10;
int Pump=A1;

int sensorPin=A0;

int highTemp=42;

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 


// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
 
  dht.begin();

   
       pinMode(motor1_ena,OUTPUT);
       pinMode(motor1_enb,OUTPUT);
       
       pinMode(motor1_in1,OUTPUT);
       pinMode(motor1_in2,OUTPUT);
       pinMode(motor1_in3,OUTPUT);
       pinMode(motor1_in4,OUTPUT); 
       
       analogWrite(motor1_ena,75);//motor speed
       analogWrite(motor1_enb,255);//cool fan speed

       pinMode(Pump,OUTPUT);
       
       pinMode(relaypin,OUTPUT);
       digitalWrite(relaypin,HIGH);//heater and heater fan are going to be on 

        
        
      digitalWrite(motor1_in1,HIGH);//motor is starting rotating. I have placed a button to control motor. 
      digitalWrite(motor1_in2,LOW);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);//show the temp in centidegree
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");

  int sensorValue=analogRead(sensorPin);
  Serial.print("WaterValue= ");
  Serial.print(sensorValue);

  if (sensorValue<500){
    analogWrite(Pump,255);
  }
  else{
    analogWrite(Pump,0);
  }
  
   
    if(t>=highTemp)
       {
       digitalWrite(relaypin,LOW);//heater and heater fan are going to be off
       digitalWrite(motor1_in3,HIGH);//cool fan is going to be on
       digitalWrite(motor1_in4,LOW);
       }
       if(t<40)
       {
       digitalWrite(motor1_in3,LOW);//cool fan is going to be off
       digitalWrite(motor1_in4,LOW);
       digitalWrite(relaypin,HIGH); //heater and heater fan are going to be on
       }
  
}

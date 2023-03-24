#include <dht11.h>
#define DHT11PIN 9

dht11 DHT11;

void
  setup()
{
  Serial.begin(9600);
 
}

void loop()
{
  Serial.println();


  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");

  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature(C): ");
  
  Serial.println((float)DHT11.temperature, 2);
  
  Serial.print(" fahrenheit : ");
  Serial.print((DHT11.temperature*9.0)/5.0+32.0);
  delay(3000);

}

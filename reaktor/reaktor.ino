#include <Wire.h>
#include <L3G.h>
#include <Adafruit_BMP085.h>


L3G gyro;
Adafruit_BMP085 bmp;

// m - Member g - Gloobal a - Atrbute 

struct ReactorReadings
{
  int32_t mGyroX;
  int32_t mGyroY;
  int32_t mGyroZ;
  float mBarT;  //zmienic aby nie było zmieno przecinkowej
  int32_t mBarP;
};

ReactorReadings gReactorReadings;

void PutGyroData(ReactorReadings* aRR, int32_t aX, int32_t aY, int32_t aZ)
{
  aRR->mGyroX = aX;
  aRR->mGyroY = aY;
  aRR->mGyroZ = aZ;
}

void  PutBarData(ReactorReadings* aRR, float aT, int32_t aP)
{
  aRR->mBarT = aT;
  aRR->mBarP = aP;
}

void SendData(ReactorReadings* aRR)
{
   Serial.print(aRR->mGyroX);
   Serial.print(", ");
   Serial.print(aRR->mGyroY);
   Serial.print(", ");
   Serial.print(aRR->mGyroZ);
   Serial.print(", ");
   
   Serial.print(aRR->mBarT);
   Serial.print(", ");
   Serial.print(aRR->mBarP);
    
   Serial.print('\n');
}
void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
}

void loop() {
  gyro.read();
  PutGyroData(&gReactorReadings, (int32_t)gyro.g.x, (int32_t)gyro.g.y, (int32_t)gyro.g.z);
  PutBarData(&gReactorReadings, bmp.readTemperature(), bmp.readPressure());
  SendData(&gReactorReadings);  
  delay(100);
}

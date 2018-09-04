#include <Wire.h>
#include <L3G.h>

L3G gyro;

// m - Member g - Gloobal a - Atrbute 

struct ReactorReadings
{
  int mGyroX;
  int mGyroY;
  int mGyroZ;
};

ReactorReadings gReactorReadings;

void PutGyroData(ReactorReadings* aRR, int aX, int aY, int aZ)
{
  aRR->mGyroX = aX;
  aRR->mGyroY = aY;
  aRR->mGyroZ = aZ;
}
void SendData(ReactorReadings* aRR)
{
   Serial.print(aRR->mGyroX);
    Serial.print(", ");
   Serial.print(aRR->mGyroY);
    Serial.print(", ");
   Serial.print(aRR->mGyroZ);
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
}
void loop() {
  gyro.read();
    PutGyroData(&gReactorReadings, gyro.g.x, gyro.g.y, gyro.g.z);
    SendData(&gReactorReadings);  
  delay(100);
}

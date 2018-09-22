#include <Wire.h>
#include <L3G.h>
#include <Adafruit_BMP085.h>
#include <HMC5883L.h>

HMC5883L mag;
L3G gyro;
Adafruit_BMP085 bmp;

// m - Member g - Gloobal a - Atrbute 

struct ReactorReadings
{
  int32_t mGyroX;
  int32_t mGyroY;
  int32_t mGyroZ;
  int32_t mBarT;  //zmienic aby nie było zmieno przecinkowej
  int32_t mBarP;
  int32_t mMagX;
  int32_t mMagY;
  int32_t mMagZ;
  
};

ReactorReadings gReactorReadings;

void PutGyroData(ReactorReadings* aRR, int32_t aX, int32_t aY, int32_t aZ)
{
  aRR->mGyroX = aX;
  aRR->mGyroY = aY;
  aRR->mGyroZ = aZ;
}
void PutMagData(ReactorReadings* aRR, int32_t aMX, int32_t aMY, int32_t aMZ)
{
  aRR->mMagX = aMX;
  aRR->mMagY = aMY;
  aRR->mMagZ = aMZ;
}
void  PutBarData(ReactorReadings* aRR, int32_t aT, int32_t aP)
{
  aRR->mBarT = aT;
  aRR->mBarP = aP;
}

void SendData(ReactorReadings* aRR)
{
  //Gyro
   Serial.print(aRR->mGyroX);
   Serial.print(", ");
   Serial.print(aRR->mGyroY);
   Serial.print(", ");
   Serial.print(aRR->mGyroZ);
   Serial.print(", ");
 //Barometr  
   Serial.print(aRR->mBarT);
   Serial.print(", ");
   Serial.print(aRR->mBarP);
   Serial.print(", ");
 //Magnetro
   Serial.print(aRR->mMagX);
   Serial.print(", ");
   Serial.print(aRR->mMagY);
   Serial.print(", ");
   Serial.print(aRR->mMagZ);
   
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
  gyro.enableDefault();
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
  while (!mag.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    delay(500);
  }
  mag.setRange(HMC5883L_RANGE_1_3GA);
  mag.setMeasurementMode(HMC5883L_CONTINOUS);
  mag.setDataRate(HMC5883L_DATARATE_15HZ);
  mag.setSamples(HMC5883L_SAMPLES_1);
}


void loop() {
  gyro.read();
  Vector mag_raw = mag.readRaw();
  PutGyroData(&gReactorReadings, (int32_t)gyro.g.x, (int32_t)gyro.g.y, (int32_t)gyro.g.z);
  PutBarData(&gReactorReadings, bmp.readRawTemperature(), bmp.readRawPressure());
  PutMagData(&gReactorReadings,(int32_t)mag_raw.XAxis, (int32_t)mag_raw.YAxis, (int32_t)mag_raw.ZAxis);
  SendData(&gReactorReadings);  
  delay(100);
}

#include <MPU9250_WE.h>
#include <Wire.h>
#define MPU9250_ADDR 0x68

MPU9250_WE myMPU9250 = MPU9250_WE(MPU9250_ADDR);
void setup() {
  Serial.begin(115200);
  Wire.begin();
  if(!myMPU9250.init()){
    Serial.println("MPU9250 does not respond");
  }
  else{
    Serial.println("MPU9250 is connected");
  }

    Serial.println("Position you MPU9250 flat and don't move it - calibrating...");
  delay(1000);
  myMPU9250.autoOffsets();
  Serial.println("Done!");

  myMPU9250.setSampleRateDivider(5);

  myMPU9250.setAccRange(MPU9250_ACC_RANGE_4G); // 2g, 4g, 8g, 16g are availible but the higher the range the lower the acuracy
  myMPU9250.enableAccDLPF(true);//tbh idk
  myMPU9250.setAccDLPF(MPU9250_DLPF_6);// yyyy

}

void loop() {
  xyzFloat accRaw = myMPU9250.getAccRawValues();
  xyzFloat accCorrRaw = myMPU9250.getCorrectedAccRawValues();
  xyzFloat gValue = myMPU9250.getGValues();
  float resultantG = myMPU9250.getResultantG(gValue);
  
  Serial.println("Raw acceleration values (x,y,z):");
  Serial.print(accRaw.x);
  Serial.print("   ");
  Serial.print(accRaw.y);
  Serial.print("   ");
  Serial.println(accRaw.z);
  Serial.println("Corrected ('calibrated') acceleration values (x,y,z):");
  Serial.print(accCorrRaw.x);
  Serial.print("   ");
  Serial.print(accCorrRaw.y);
  Serial.print("   ");
  Serial.println(accCorrRaw.z);
  Serial.println("g values (x,y,z):");
  Serial.print(gValue.x);
  Serial.print("   ");
  Serial.print(gValue.y);
  Serial.print("   ");
  Serial.println(gValue.z);
  Serial.print("Resultant g: ");
  Serial.println(resultantG); // should always be 1 g if only gravity acts on the sensor.
  Serial.println();
  
  delay(1000);
}
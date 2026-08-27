#include <MPU9250_WE.h>
#include <Wire.h>
#define MPU9250_ADDR 0x68
#define MPU9250_ADDR2 0x69
bool connected = true;

MPU9250_WE myMPU9250 = MPU9250_WE(MPU9250_ADDR);
MPU9250_WE alsomyMPU9250 = MPU9250_WE(MPU9250_ADDR2);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if(!myMPU9250.init()){
    Serial.println("MPU9250 0x68 does not respond");
    connected = false;
  }
  else{
    Serial.println("MPU9250 0x68 is connected");
  }
  if(!alsomyMPU9250.init()){
    Serial.println("MPU9250 0x69 does not respond");
    connected = false;
  }
  else{
    Serial.println("MPU9250 0x69 is connected");
  }
  if (connected == false)
  {
    while(true)
    {

    }
  }

    Serial.println("Position you MPU9250 flat and don't move it - calibrating...");
  delay(1000);
  myMPU9250.autoOffsets();
  alsomyMPU9250.autoOffsets();
  Serial.println("Done!");

 //for accel
  myMPU9250.setSampleRateDivider(5);
  myMPU9250.setAccRange(MPU9250_ACC_RANGE_4G); // 2g, 4g, 8g, 16g are availible but the higher the range the lower the acuracy
  myMPU9250.enableAccDLPF(true);//tbh idk
  myMPU9250.setAccDLPF(MPU9250_DLPF_6);// yyyy

  alsomyMPU9250.setSampleRateDivider(5); // same thing for 0x69
  alsomyMPU9250.setAccRange(MPU9250_ACC_RANGE_4G);
  alsomyMPU9250.enableAccDLPF(true);
  alsomyMPU9250.setAccDLPF(MPU9250_DLPF_6);

  //for gryo
  myMPU9250.enableGyrDLPF();

  alsomyMPU9250.enableGyrDLPF();
}

void loop() {
  xyzFloat gValue = myMPU9250.getGValues();
  xyzFloat alsogValue = alsomyMPU9250.getGValues();
  xyzFloat gyr = myMPU9250.getGyrValues();
  xyzFloat alsogyr = alsomyMPU9250.getGyrValues();

  Serial.println("Gyroscope Data from 0x68 in degrees/s (x,y,z):");
  Serial.print(gyr.x);
  Serial.print("   ");
  Serial.print(gyr.y);
  Serial.print("   ");
  Serial.println(gyr.z);  
  Serial.print("   ");
  Serial.println("Gyroscope Data from 0x69 in degrees/s (x,y,z):");
  Serial.print(gyr.x);
  Serial.print("   ");
  Serial.print(gyr.y);
  Serial.print("   ");
  Serial.println(gyr.z);  
  Serial.print("   ");
  Serial.println("Acceleration from 0x68 in g values (x,y,z):");
  Serial.print(gValue.x);
  Serial.print("   ");
  Serial.print(gValue.y);
  Serial.print("   ");
  Serial.println(gValue.z);
  Serial.println();
  Serial.println("Acceleration from 0x69 in g values (x,y,z):");
  Serial.print(gValue.x);
  Serial.print("   ");
  Serial.print(gValue.y);
  Serial.print("   ");
  Serial.println(gValue.z);
  Serial.println();
  
  delay(1000);
}
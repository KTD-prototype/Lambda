//copied from : https://ssk0109.hatenablog.com/entry/2018/12/13/014117

#include <MPU9250_asukiaaa.h>

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 26
#define SCL_PIN 25
#endif

MPU9250 mySensor;

#include <ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>

ros::NodeHandle nh;

sensor_msgs::Imu imu;
sensor_msgs::MagneticField mag;
ros::Publisher pubimu("imu/data_raw", &imu);
ros::Publisher pubmag("imu/mag", &mag);

void setup() {
  while(!Serial);
  Serial.begin(115200);
  Serial.println("started");

#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN); // SDA, SCL
#else
  Wire.begin();
#endif

  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

  // You can set your own offset for mag values
  // mySensor.magXOffset = -50;
  // mySensor.magYOffset = -55;
  // mySensor.magZOffset = -10;

  sensorId = mySensor.readId();
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(pubimu);
  nh.advertise(pubmag);
}
float gXOffset= 2.50, gYOffset=-1.40, gZOffset= 1.47;
//float sumgX, sumgY, sumgZ;
//int n=1;
void loop() {
  Serial.println("sensorId: " + String(sensorId));
  float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;
  mySensor.accelUpdate();
  aX = mySensor.accelX() ;
  aY = mySensor.accelY() ;
  aZ = mySensor.accelZ() ;
  //aSqrt = mySensor.accelSqrt();
  Serial.println("accelX: " + String(aX));
  Serial.println("accelY: " + String(aY));
  Serial.println("accelZ: " + String(aZ));
  //Serial.println("accelSqrt: " + String(aSqrt));

  mySensor.gyroUpdate();
  gX = mySensor.gyroX()-gXOffset;
  gY = mySensor.gyroY()-gYOffset;
  gZ = mySensor.gyroZ()-gZOffset;
  Serial.println("gyroX: " + String(gX));
  Serial.println("gyroY: " + String(gY));
  Serial.println("gyroZ: " + String(gZ));
  
  /*
  sumgX = (sumgX*(n-1)+ gX)/n;
  sumgY = (sumgY*(n-1)+ gY)/n;
  sumgZ = (sumgZ*(n-1)+ gZ)/n;
  Serial.println("sumgyroX: " + String(sumgX));
  Serial.println("sumgyroY: " + String(sumgY));
  Serial.println("sumgyroZ: " + String(sumgZ));
  n=n+1;
  */
 
  mySensor.magUpdate();
  mX = mySensor.magX();
  mY = mySensor.magY();
  mZ = mySensor.magZ();
  mDirection = mySensor.magHorizDirection();
  Serial.println("magX: " + String(mX));
  Serial.println("maxY: " + String(mY));
  Serial.println("magZ: " + String(mZ));
  Serial.println("horizontal direction: " + String(mDirection));
  
  Serial.println("at " + String(millis()) + "ms");
  Serial.println(""); // Add an empty line
  
  imu.header.frame_id = "imu_link";
  imu.header.stamp = nh.now();
  imu.angular_velocity.x = gX;
  imu.angular_velocity.y = gY;
  imu.angular_velocity.z = gZ; // [rad/sec]
  imu.linear_acceleration.x = aX;      
  imu.linear_acceleration.y = aY;  
  imu.linear_acceleration.z = aZ; 
  pubimu.publish(&imu);
  
  mag.header.frame_id = "imu_link";
  mag.header.stamp = nh.now();
  mag.magnetic_field.x = mX;
  mag.magnetic_field.y = mY;
  mag.magnetic_field.z = mZ; // [μT]
  pubmag.publish(&mag);

  nh.spinOnce();
  delay(1);
}

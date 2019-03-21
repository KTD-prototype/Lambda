//refered http://www.lucidarme.me/?p=5057


void MPU9250_Initialization() {
  //MPU9250測定レンジを決定
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_1000_DPS);
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);

  //地磁気センサのバイパスモードを設定
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
  //地磁気センサの最初の測定を一回だけリクエスト
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01);
}


void MPU9250_PostureAngle() {
  //when accleraration more or less than 1G is loaded to sensor(resultant vector of ax,ay,az),  ACCroll and ACCpitch will offset from true value.
  //so if then, smallen the coefficient for complementary filter
  float ACCvectorSUM = sqrt(pow(data[0], 2) + pow(data[1], 2) + pow(data[2], 2));
  k = 0.05 * (1 / pow((pow(ACCvectorSUM - 1, 2) + 1), 6));

  //calculate pitch and roll by accelerometer with LPF
  //ピッチ方向+90度回転をデフォルト値（=0度）とするため、最後にピッチのみ回転をかける。
  ACCroll = 0.05 * ACCroll + 0.95 * (atan2(data[1],  data[2]) * 180 / M_PI);
  ACCpitch = 0.05 * ACCroll + 0.95 * (atan2(data[0], sqrt(pow(data[1], 2) + pow(data[2], 2))) * 180 / M_PI);
  //ACCyaw = sqrt ( ACCvectorSUM - ACCroll * ACCroll - ACCpitch * ACCpitch);
  //ACCpitch = cos(-pitch) * ACCpitch + sin(-pitch) * ACCyaw;

  //calculate pitch/roll/yaw by gyrosensor (About pitch & roll, using Complementary Filter)
  //90度ピッチさせた状態で使うので、ロール計算にyaw角のdata[5]、ヨー計算にroll角のdata[3]を使用する。
  roll = (1 - k) * (roll + data[3]  / SAMPLINGRATE) + k * ACCroll;
  pitch = (1 - k) * (pitch + (-1 * data[4]) / SAMPLINGRATE) + k * ACCpitch; //ピッチの角速度データが正負逆で入っているようだ。
  if (abs(data[5]) < 0.05) {
    yaw = yaw;
  }
  else yaw = yaw + data[5] / SAMPLINGRATE;
}



//アドレス「Address」にあるI2CデバイスからNバイトの値を読み取る関数。
//読み取りバイトをデータ配列内のレジスタ「register」に書き込む。
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
  //set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  //read Nbytes
  Wire.requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while (Wire.available())
    Data[index++] = Wire.read();
}


//バイト型データ「Data」を「Address」にあるレジスタ「Register」にかきこむ　
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data) {
  //Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}


//MPU9250のキャリブレーション。1000サンプルの平均値をオフセット
void MPU9250_Calibration() {
  int i = 0;
  float SUMax = 0, SUMay = 0, SUMaz = 0, SUMgx = 0, SUMgy = 0, SUMgz = 0;
  while (i < 1000) {
    MPU9250_Sensordata(Calib[0], Calib[1], Calib[2], Calib[3], Calib[4], Calib[5]);
    SUMax += data[0];
    SUMay += data[1];
    SUMaz += data[2];
    SUMgx += data[3];
    SUMgy += data[4];
    SUMgz += data[5];
    i++;
  }
  Calib[0] = SUMax / 1000;
  Calib[1] = SUMay / 1000;
  Calib[2] = SUMaz / 1000;
  Calib[3] = SUMgx / 1000;
  Calib[4] = SUMgy / 1000;
  Calib[5] = SUMgz / 1000;
}


//加速度、角速度の生データ読み出し
void MPU9250_Sensordata(float Cax, float Cay, float Caz, float Cgx, float Cgy, float Cgz) {
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);
  data[0] = -(Buf[0] << 8 | Buf[1]);
  data[1] = -(Buf[2] << 8 | Buf[3]);
  data[2] = (Buf[4] << 8 | Buf[5]);

  //Gyroscope
  data[3] = -(Buf[8] << 8 | Buf[9]);
  data[4] = -(Buf[10] << 8 | Buf[11]);
  data[5] = (Buf[12] << 8 | Buf[13]);

  data[0] = ACC_SCALE * data[0] / 32768;// - Cax;
  data[1] = ACC_SCALE * data[1] / 32768;// - Cay;
  data[2] = ACC_SCALE * data[2] / 32768;// - Caz;
  data[3] = GYR_SCALE * data[3] / 32768 - Cgx;
  data[4] = GYR_SCALE * data[4] / 32768 - Cgy;
  data[5] = GYR_SCALE * data[5] / 32768 - Cgz;
}

void FLAG() {
  flag = 1;
}



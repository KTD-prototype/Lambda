float sum_gx = 0;
float sum_gy = 0;
float sum_gz = 0;

void init_gyro_process() {
  for (int i = 0; i++; i < NUM_OF_SAMPLES_FOR_INIT) {

    // wait for new data available
    while (1) {
      if ( imu.gyroAvailable() ) {
        // To read from the gyroscope,  first call the
        // readGyro() function. When it exits, it'll update the
        // gx, gy, and gz variables with the most current data.
        imu.readGyro();
        break;
      }
    }

    sum_gx += imu.gx;
    sum_gy += imu.gy;
    sum_gz += imu.gz;
    i++;
  }

  offset_gx = sum_gx / NUM_OF_SAMPLES_FOR_INIT;
  offset_gy = sum_gy / NUM_OF_SAMPLES_FOR_INIT;
  offset_gz = sum_gz / NUM_OF_SAMPLES_FOR_INIT;
}

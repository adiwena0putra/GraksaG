#include "graksastring.h"

void construct_MSG_Accel(float ax, float ay, float az, string* AccelStr)
{
    *AccelStr = to_string(0xd) + "ITB" + ";" + to_string(GRAKSA_MSG_ID_ACCEL) +  ";" + to_string(ax) + ";" + to_string(ay) + ";" + to_string(az);
}

void construct_MSG_Gyro(float gx, float gy, float gz, string* GyroStr)
{
    *GyroStr = to_string(0xd) + "ITB" + ";" + to_string(GRAKSA_MSG_ID_GYRO) + ";" + to_string(gx) + ";" + to_string(gy) + ";" + to_string(gz);
}

void construct_MSG_Alt(float alt, string* AltStr)
{
    *AltStr = to_string(0xd) + "ITB" + ";" + to_string(GRAKSA_MSG_ID_ALT) + ";" + to_string(alt);
}

void construct_MSG_GPS(double lon, double lat, string* GPSStr)
{
    *GPSStr = to_string(0xd) + "ITB" + ";" + to_string(GRAKSA_MSG_ID_GPS) + ";" + to_string(lon) + ";" + to_string(lat);
}

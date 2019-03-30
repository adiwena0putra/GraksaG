#ifndef GRAKSASTRING_H
#define GRAKSASTRING_H
/*
 * STRUKTUR MESSAGE (dikirimkan dalam string)
 * BYTE 1           Start of Frame
 * BYTE 2-4         Team Identifiacion
 * BYTE 5           Message Identification
 * BYTE 6-n         Payload
 * */

/* Library used */
#include <string>
using namespace std;

/* Message ID Detail */
#define GRAKSA_MSG_ID_ACCEL 0
#define GRAKSA_MSG_ID_GYRO 1
#define GRAKSA_MSG_ID_ALT 2
#define GRAKSA_MSG_ID_GPS 3

/* Construct Message */
void construct_MSG_Accel(float ax, float ay, float az, string* AccelStr);
void construct_MSG_Gyro(float gx, float gy, float gz, string* GyroStr);
void construct_MSG_Alt(float alt, string* AltStr);
void construct_MSG_GPS(double lon, double lat, string* GPSStr);

#endif // GRAKSASTRING_H

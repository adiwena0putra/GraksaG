#ifndef GRAKSALINK_H
#define GRAKSALINK_H

/*
 * STRUKTUR MESSAGE
 * BYTE 1           Start of Frame
 * BYTE 2-4         Team Identifiacion
 * BYTE 5           Message Identification
 * BYTE 6-n         Payload
 * */

/* Library used */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* Message ID Detail */
#define GRAKSA_MSG_ID_AX 0
#define GRAKSA_MSG_ID_AY 1
#define GRAKSA_MSG_ID_AZ 2
#define GRAKSA_MSG_ID_GX 3
#define GRAKSA_MSG_ID_GY 4
#define GRAKSA_MSG_ID_GZ 5
#define GRAKSA_MSG_ID_ALT 6
#define GRAKSA_MSG_ID_LON 7
#define GRAKSA_MSG_ID_LAT 8
#define GRAKSA_MSG_ID_PHOTO 9
#define GRAKSA_MSG_ID_XPOS 10
#define GRAKSA_MSG_ID_YPOS 11
#define GRAKSA_MSG_ID_ZPOS 12
#define GRAKSA_MSG_ID_ROLL 14
#define GRAKSA_MSG_ID_PITCH 15
#define GRAKSA_MSG_ID_YAW 16

/* Construct Message */
void construct_MSG_AX(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float ax);
void construct_MSG_AY(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float ay);
void construct_MSG_AZ(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float az);
void construct_MSG_GX(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float gx);
void construct_MSG_GY(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float gy);
void construct_MSG_GZ(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float gz);
void construct_MSG_ALT(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float alt);
void construct_MSG_LON(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], double lon);
void construct_MSG_LAT(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], double lat);
void construct_MSG_ROLL(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float roll);
void construct_MSG_PITCH(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float pitch);
void construct_MSG_YAW(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float yaw);


#endif // GRAKSALINK_H

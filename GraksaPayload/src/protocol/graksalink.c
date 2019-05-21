#include "graksalink.h"

/* Construct Message */
void construct_MSG_AX(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float ax)
{
    uint8_t *p_byte = (uint8_t*) &ax;
    size_t nBytes = sizeof (char)*5 + sizeof (ax);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_AX;
        } else {
            temp[i]=p_byte[i-5];
        }
    }
}

void construct_MSG_AY(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float ay)
{
    uint8_t *p_byte = (uint8_t*) &ay;
    size_t nBytes = sizeof (char)*5 + sizeof (ay);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_AY;
        } else {
            temp[i]=p_byte[i-5];
        }
    }
}

void construct_MSG_AZ(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float az)
{
    uint8_t *p_byte = (uint8_t*) &az;
    size_t nBytes = sizeof (char)*5 + sizeof (az);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_AZ;
        } else {
            temp[i]=p_byte[i-5];
        }
    }
}

void construct_MSG_GX(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float gx)
{
    uint8_t *p_byte = (uint8_t*) &gx;
    size_t nBytes = sizeof (char)*5 + sizeof (gx);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_GX;
        } else {
            temp[i]=p_byte[i-5];
        }
    }
}

void construct_MSG_GY(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float gy)
{
    uint8_t *p_byte = (uint8_t*) &gy;
    size_t nBytes = sizeof (char)*5 + sizeof (gy);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_GY;
        } else {
            temp[i]=p_byte[i-5];
        }
    }
}

void construct_MSG_GZ(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float gz)
{
    uint8_t *p_byte = (uint8_t*) &gz;
    size_t nBytes = sizeof (char)*5 + sizeof (gz);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_GZ;
        } else {
            temp[i]=p_byte[i-5];
        }
    }
}

void construct_MSG_ALT(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float alt)
{
    uint8_t *p_byte = (uint8_t*) &alt;
    size_t nBytes = sizeof (char)*5 + sizeof (alt);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_ALT;
        } else {
            temp[i]=p_byte[i-5];
        }
    }
}

void construct_MSG_LON(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float lon)
{
    uint8_t *p_byte = (uint8_t*) &lon;
    size_t nBytes = sizeof (char)*5 + sizeof (lon);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_LON;
        } else {
            temp[i]=p_byte[i-5];
        }
    }
}

void construct_MSG_LAT(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float lat)
{
    uint8_t *p_byte = (uint8_t*) &lat;
    size_t nBytes = sizeof (char)*5 + sizeof (lat);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_LAT;
        } else {
            temp[i]=p_byte[i-5];
        }
    }
}

void construct_MSG_ROLL(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float roll)
{
    uint8_t *p_byte = (uint8_t*) &roll;
    size_t nBytes = sizeof (char)*5 + sizeof (roll);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_ROLL;
        } else {
            temp[i]=p_byte[i-5];
        }
    }	
}

void construct_MSG_PITCH(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float pitch)
{
    uint8_t *p_byte = (uint8_t*) &pitch;
    size_t nBytes = sizeof (char)*5 + sizeof (pitch);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_PITCH;
        } else {
            temp[i]=p_byte[i-5];
        }
    }	
}

void construct_MSG_YAW(uint8_t **output, uint8_t SOF, uint8_t Team_ID[3], float yaw)
{
    uint8_t *p_byte = (uint8_t*) &yaw;
    size_t nBytes = sizeof (char)*5 + sizeof (yaw);
    uint8_t *temp;
    *output = NULL;
    *output = (uint8_t*) malloc(nBytes);
    temp = *output;

    for (size_t i=0; i<nBytes; i++){
        if (i==0) {
            temp[i]=SOF;
        } else if (i>=1 && i<=3 ){
            temp[i]=Team_ID[i-1];
        } else if (i==4) {
            temp[i]=GRAKSA_MSG_ID_YAW;
        } else {
            temp[i]=p_byte[i-5];
        }
    }	
}

///* Deconstruct Message */
//void deconstruct_MSG_AX(message_t *input, float *ax)
//{
//    memcpy(ax,input->payload,sizeof (*ax));
//}

//void deconstruct_MSG_AY(message_t *input, float *ay)
//{
//    memcpy(ay,input->payload,sizeof (*ay));
//}

//void deconstruct_MSG_AZ(message_t *input, float *az)
//{
//    memcpy(az,input->payload,sizeof (*az));
//}

//void deconstruct_MSG_GX(message_t *input, float *gx)
//{
//    memcpy(gx,input->payload,sizeof (*gx));
//}

//void deconstruct_MSG_GY(message_t *input, float *gy)
//{
//    memcpy(gy,input->payload,sizeof (*gy));
//}

//void deconstruct_MSG_GZ(message_t *input, float *gz)
//{
//    memcpy(gz,input->payload,sizeof (*gz));
//}

//void deconstruct_MSG_ALT(message_t *input, float *alt)
//{
//    memcpy(alt,input->payload,sizeof (*alt));
//}

//void deconstruct_MSG_LON(message_t *input, double *lon)
//{
//    memcpy(lon,input->payload,sizeof (*lon));
//}

//void deconstruct_MSG_LAT(message_t *input, double *lat)
//{
//    memcpy(lat,input->payload,sizeof (*lat));
//}

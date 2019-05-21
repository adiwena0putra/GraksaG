#include "src/payload/MPU9250-0.1.0/MPU9250.h"
#include "src/payload/TinyGPSPlus-master/TinyGPS++.h"
#include <TimerOne.h>
extern "C"{
#include "src/protocol/graksalink.h"
}
#define PIN_DEBUG A0
// Define State
#define STATE_WAIT 0
#define STATE_SEND_DATA 1

// Define other constant
#define SAMPLING_PERIODE_US 50000

// State Var
char state = STATE_WAIT;

// GPS Variable
TinyGPSPlus gps;
float lon, lat, alt;

// IMU Variable
MPU9250 mpu;
float pitch, yaw, roll;

// Camera Variable

// Protocol Variable
uint8_t teamId[3];
uint8_t *message;

void ISR_send_data(){
  // change state
  state = STATE_SEND_DATA;
}

void setup() { 
    // pin debug
    pinMode(PIN_DEBUG,OUTPUT);
    digitalWrite(PIN_DEBUG, HIGH);
  
    // serial untuk transmisi data 
    Serial.begin(57600);

    // GPS setup
    Serial1.begin(9600);
    
    // IMU setup
    Wire.begin();
    mpu.setup();
    delay(2000);
    
    // prococol setup
    teamId[0]='I';
    teamId[1]='T';
    teamId[2]='B';

    // interrupt setup
    Timer1.initialize(SAMPLING_PERIODE_US); 
    Timer1.attachInterrupt(ISR_send_data);
}

void loop() {
    if (state == STATE_SEND_DATA) {
      digitalWrite(PIN_DEBUG,LOW);
      // ambil data
      mpu.update();
      roll = mpu.getRoll();
      pitch = mpu.getPitch();
      yaw = mpu.getYaw();
      unsigned long start = millis();
      do{
        while (Serial1.available())
        {
          if (gps.encode (Serial1.read())){
            if (gps.location.isUpdated() && gps.altitude.isUpdated() ) {
              lon = gps.location.lng();
              lat = gps.location.lat();
              alt = gps.altitude.meters();
            }
          } 
        }
      }while(millis() - start < 10); 
      // kirim data
      construct_MSG_ROLL(&message,0xd,teamId,roll);
      Serial.write(message,9);
      free(message);
      construct_MSG_PITCH(&message,0xd,teamId,pitch);
      Serial.write(message,9);
      free(message);
      construct_MSG_YAW(&message,0xd,teamId,yaw);
      Serial.write(message,9);
      free(message);
      construct_MSG_LON(&message,0xd,teamId,lon);
      Serial.write(message,9);
      free(message);
      construct_MSG_LAT(&message,0xd,teamId,lat);
      Serial.write(message,9);
      free(message);
      construct_MSG_ALT(&message,0xd,teamId,alt);
      Serial.write(message,9);
      free(message); 
      state = STATE_WAIT;
    }
    digitalWrite(PIN_DEBUG,HIGH);  
}

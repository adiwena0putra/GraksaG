#include <iostream>
#include "graksastring.h"

using namespace std;

int main()
{
    float ax = rand()/12;
    float ay = rand()/23;
    float az = rand()/34;
    float gx = rand()/45;
    float gy = rand()/56;
    float gz = rand()/67;
    float alt = rand()/78;
    double lon = rand()/89;
    double lat = rand()/90;
    string AccelString;
    string GyroString;
    string AltString;
    string GPSString;
    cout << "ax: " << ax << endl;
    cout << "ay: " << ay << endl;
    cout << "az: " << az << endl;
    cout << "gx: " << gx << endl;
    cout << "gy: " << gy << endl;
    cout << "gz: " << gz << endl;
    cout << "alt: " << alt << endl;
    cout << "lon: " << lon << endl;
    cout << "lat: " << lat << endl;
    construct_MSG_Accel(ax,ay,az,&AccelString);
    construct_MSG_Gyro(gx,gy,gz,&GyroString);
    construct_MSG_Alt(alt,&AltString);
    construct_MSG_GPS(lon,lat,&GPSString);
    cout << "AccelString: " << AccelString << endl;
    cout << "AccelString size: " << AccelString.size() << endl;
    cout << "GyroString: " << GyroString << endl;
    cout << "GyroString size: " << GyroString.size() << endl;
    cout << "AltString: " << AltString << endl;
    cout << "AltString size: " << AltString.size() << endl;
    cout << "GPSString: " << GPSString << endl;
    cout << "GPSString size: " << GPSString.size() << endl;
    return 0;
}

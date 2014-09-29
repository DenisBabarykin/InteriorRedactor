#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
    double x, y, z;
    double k;
    double ox, oy, oz;

public:
    Camera(double x = 0, double y = 0, double z = 0, double k = 0, double ox = 0,
           double oy = 0, double oz = 0);

};

#endif // CAMERA_H

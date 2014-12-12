#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
    double dx, dy, dz;
    double angleOX, angleOY;

public:
    Camera();

    void AddShift(double dx, double dy, double dz);
    void AddRotation(double angleOX, double angleOY);

    double GetDX();
    double GetDY();
    double GetDZ();

    double GetAngleOX();
    double GetAngleOY();

    void Clear();
};

#endif // CAMERA_H

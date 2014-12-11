#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
    double dx, dy, dz;
    double angleOX, angleOY;

public:
    Camera();

    inline void AddShift(double dx, double dy, double dz);
    inline void AddRotation(double angleOX, double angleOY);

    inline double GetDX();
    inline double GetDY();
    inline double GetDZ();

    inline double GetAngleOX();
    inline double GetAngleOY();

    inline void Clear();
};

#endif // CAMERA_H

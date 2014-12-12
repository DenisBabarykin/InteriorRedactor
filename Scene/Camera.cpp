#include "Camera.h"

Camera::Camera()
{
    Clear();
}

void Camera::AddShift(double dx, double dy, double dz)
{
    this->dx += dx;
    this->dy += dy;
    this->dz += dz;
}

void Camera::AddRotation(double angleOX, double angleOY)
{
    this->angleOX += angleOX;
    this->angleOY += angleOY;
}

double Camera::GetDX()
{
    return dx;
}

double Camera::GetDY()
{
    return dy;
}

double Camera::GetDZ()
{
    return dz;
}

double Camera::GetAngleOX()
{
    return angleOX;
}

double Camera::GetAngleOY()
{
    return angleOY;
}

void Camera::Clear()
{
    dx = dy = dz = 0;
    angleOX = angleOY = 0;
}

#pragma once

struct VehicleState
{
    double x,y,psi,V;
    double yaw_rate,steering;
    VehicleState():x(0.0), y(0.0), psi(0.0), V(0.0), yaw_rate(0.0), steering(0.0) {}
    VehicleState(double setX, double setY, double setPsi, double setV):x(setX), y(setY), psi(setPsi), V(setV), yaw_rate(0.0),steering(0.0) {}
    VehicleState(double setX, double setY, double setPsi, double setV, double setPsiDot, double setSteering):x(setX), y(setY), psi(setPsi), V(setV), yaw_rate(setPsiDot),steering(setSteering) {}
};

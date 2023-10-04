#include "vehicle_state.h"
#include <cmath>
#include "utils.h"
/*define a structure for issuing motion commands to a vehicle. */


class MotionCommandBase //foundational blueprint for all types of motion commands.
{
    public:
        MotionCommandBase():m_velocity_command(0.0),m_steering_command(0.0){}
        virtual void startCommand(double time, VehicleState state){m_start_time = time;m_start_state = state;}
        virtual void endCommand(double time, double dt, VehicleState state){}
        virtual bool update(double time, double dt, VehicleState state){return false;}
        virtual double getVelocityCommand(){return m_velocity_command;}
        virtual double getSteeringCommand(){return m_steering_command;}
    protected:
        double m_velocity_command, m_steering_command, m_start_time;
        VehicleState m_start_state;
};

class MotionCommandStraight : public MotionCommandBase // to move the vehicle in straight line
 /*Given a certain velocity and duration, this command will make the vehicle move straight at that velocity for that duration.*/

{
    public:
    MotionCommandStraight(double command_time, double command_velocity)
        : m_command_time(command_time),
          m_command_velocity(command_velocity) {}

    bool update(double time, double dt, VehicleState state)
    /* meant to be called periodically (e.g., within a control loop) to update the motion command's internal state.*/
    {
        m_velocity_command = m_command_velocity;
        /*This means that every time the command is updated (likely every control cycle or timestep), 
        the "live" velocity command (m_velocity_command) is set to the desired constant straight-line speed (m_command_velocity).
        In other words, every update cycle, the system is being reminded, "Hey, for this straight-line command, I want you to keep going at m_command_velocity speed."*/

        return time > (m_start_time + m_command_time); 
        /* This checks if the current time has exceeded the sum of the start time and the command time. 
        signaling the control loop or system that the command is complete.*/

        /*you'd keep calling the update method to get the current velocity and steering commands until the update method returns true*/
    }

    private:
        double m_command_time, m_command_velocity;
};


class MotionCommandTurnTo : public MotionCommandBase
{
    public:
    static constexpr double TURN_ANGLE_TOLERANCE = 0.001;
    MotionCommandTurnTo(double command_heading, double command_velocity):m_command_heading(command_heading),m_command_velocity(command_velocity){}
    bool update(double time, double dt, VehicleState state)
    {
        m_velocity_command = m_command_velocity;
        double turn_angle_required = wrapAngle(m_command_heading - state.psi);
        m_steering_command = turn_angle_required * (std::signbit(state.V)?-1.0:1.0);
        return std::fabs(turn_angle_required) < TURN_ANGLE_TOLERANCE; //The purpose of this line is likely to determine if the vehicle has turned close enough to the desired heading or angle
        // to know when the update command should be stopped
    }
    private:
        double m_command_heading, m_command_velocity;
};


class MotionCommandMoveTo : public MotionCommandBase
{
    public:
    MotionCommandMoveTo(double command_x, double command_y, double command_velocity):m_command_x(command_x),m_command_y(command_y),m_command_velocity(command_velocity){}
    bool update(double time, double dt, VehicleState state)
    {
        m_velocity_command = m_command_velocity;
        double delta_x = m_command_x - state.x;
        double delta_y = m_command_y - state.y;
        double range = sqrt(delta_x*delta_x + delta_y*delta_y);
        double angle_command = atan2(delta_y,delta_x);
        double psi = wrapAngle(state.psi - (std::signbit(state.V) ?M_PI:0.0));
        double angle_error = wrapAngle(angle_command - psi);
        m_steering_command = angle_error * (std::signbit(state.V)?-1.0:1.0);
        return (range < 5.0);
    }
    private:
        double m_command_x, m_command_y, m_command_velocity;
};
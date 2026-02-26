#include "vehicle.h"
#include <math.h>

VehicleState calculateVehicleState(const SensorData *data)
{
    VehicleState state = {0};

    // Wheel RPM calculation 
    float rev_per_sample = (float)data->wheel_pulse_count / PULSES_PER_REV;
    float rev_per_sec = rev_per_sample / SAMPLE_TIME_S;
    state.wheel_rpm = rev_per_sec * 60.0f;

    //Vehicle speed 
    float wheel_circumference = 2.0f * 3.1416f * WHEEL_RADIUS_M;
    float speed_mps = rev_per_sec * wheel_circumference;
    state.vehicle_speed_kmph = speed_mps * 3.6f;

    // Reverse Logic(override logic missing, deceleration , hill hold logic etc. missing) 
    if (data->gear == -1)
    {
        state.direction = VEH_REVERSE;
        state.vehicle_speed_kmph *= -1;   // reverse speed negative
    }
    else if (data->wheel_pulse_count > 0 && state.wheel_rpm<=5 )
    {
       
        state.direction=VEH_STOPPED;
    }
    else 

        {state.direction = VEH_FORWARD;}
    
   
    
      //  state.direction = VEH_STOPPED;
    

    //Turning- defined by yaw angle only 
    if (data->yaw_deg > 5.0f)
        state.turn = TURN_RIGHT;
    else if (data->yaw_deg < -5.0f)
        state.turn = TURN_LEFT;
    else
        state.turn = TURN_STRAIGHT;

    //Torque request  
    state.torque_request = (data->accelerator_percent / 100.0f) * 250.0f;

    
    if (data->ignition == 0)
        state.vcu_state = STATE_OFF;
    else if (data->brake_pressed)
        state.vcu_state = STATE_BRAKE;
    else if (data->accelerator_percent > 0)
        state.vcu_state = STATE_DRIVE;
    else
        state.vcu_state = STATE_READY;

    return state;
}
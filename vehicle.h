#ifndef VEHICLE_H
#define VEHICLE_H

#include <stdio.h>
#include <stdint.h>


#define PULSES_PER_REV 48U
#define WHEEL_RADIUS_M 0.30f     // (30 cm wheel radius)
#define SAMPLE_TIME_S 0.1f       // (100 ms sample time)

//Vehicle Direction 
typedef enum
{
    VEH_STOPPED = 0,
    VEH_FORWARD,
    VEH_REVERSE
} VehicleDirection;


// Turning 
typedef enum
{
    TURN_STRAIGHT = 0,
    TURN_LEFT,
    TURN_RIGHT
} TurnDirection;

// VCU States

typedef enum
{
    STATE_OFF = 0,
    STATE_READY,
    STATE_DRIVE,
    STATE_BRAKE,
    STATE_FAULT
} VCUState;

// Sensor Errors 
typedef enum
{
    SENSOR_OK = 0,
    ERR_IGNITION,
    ERR_WSS,
    ERR_ACCEL,
    ERR_BRAKE,
    ERR_YAW
} SensorError;

// Sensor Data 
typedef struct
{
    uint8_t ignition;
    float wheel_pulse_count;
    uint8_t accelerator_percent;
    uint8_t brake_pressed;
    float yaw_deg;
    int8_t gear;   // (+1 = forward, -1 = reverse)
} SensorData;


typedef struct
{
    float wheel_rpm;
    float vehicle_speed_kmph;
    float torque_request;
    VehicleDirection direction;
    TurnDirection turn;
    VCUState vcu_state;
} VehicleState;

SensorError validateSensors(const SensorData *data);
VehicleState calculateVehicleState(const SensorData *data);
void stateMachine(const VehicleState *state, SensorError error);

#endif
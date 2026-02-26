#include "vehicle.h"

int main()
{
    SensorData data;
    VehicleState state;
    SensorError error;

    printf("Enter Ignition (0=OFF, 1=ON): ");
    scanf("%hhu", &data.ignition);

    printf("Enter Wheel Pulse Count (100ms): ");
    scanf("%f", &data.wheel_pulse_count);

    printf("Enter Accelerator Percentage (0-100): ");
    scanf("%hhu", &data.accelerator_percent);

    printf("Enter Brake (0=Released, 1=Pressed): ");
    scanf("%hhu", &data.brake_pressed);
    

    printf("Enter Yaw Angle (deg): ");
    scanf("%f", &data.yaw_deg);

    printf("Enter Gear (1=Forward, -1=Reverse): ");
    scanf("%hhd", &data.gear);

    error = validateSensors(&data);

    if (error == SENSOR_OK)
        state = calculateVehicleState(&data);

    stateMachine(&state, error);

    return 0;
}
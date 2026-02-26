#include "vehicle.h"

void stateMachine(const VehicleState *state, SensorError error)
{
    if (error != SENSOR_OK)
    {
        printf("\n*** FAULT MODE ***\n");

        if (error == ERR_IGNITION)
            printf("Ignition OFF\n");
        else if (error == ERR_WSS)
            printf("RED LAMP: Wheel Speed Sensor Fault\n");
        else if (error == ERR_ACCEL)
            printf("YELLOW LAMP: Accelerator Fault\n");
        else if (error == ERR_BRAKE)
            printf("YELLOW LAMP: Brake Switch Fault\n");
        else
            printf("YELLOW LAMP: Yaw Sensor Fault\n");

        return;
    }

    printf("\n--- VCU STATE ---\n");

    switch (state->vcu_state)
    {
        case STATE_OFF:   printf("VCU State: OFF\n"); break;
        case STATE_READY: printf("VCU State: READY\n"); break;
        case STATE_DRIVE: printf("VCU State: DRIVE\n"); break;
        case STATE_BRAKE: printf("VCU State: BRAKING\n"); break;
        default:          printf("VCU State: FAULT\n"); break;
    }

    if (state->direction == VEH_FORWARD)
        printf("Direction: FORWARD\n");
    else if (state->direction == VEH_REVERSE)
        printf("Direction: REVERSE\n");
    else
        printf("Direction: STOPPED\n");

    if (state->turn == TURN_LEFT)
        printf("Turning: LEFT\n");
    else if (state->turn == TURN_RIGHT)
        printf("Turning: RIGHT\n");
    else
        printf("Turning: STRAIGHT\n");

    printf("Wheel RPM: %.2f rpm\n", state->wheel_rpm);
    printf("Vehicle Speed: %.2f km/h\n", state->vehicle_speed_kmph);
    printf("Torque Request: %.2f Nm\n", state->torque_request);
}
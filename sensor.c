#include "vehicle.h"

SensorError validateSensors(const SensorData *data)
{
    if (data->ignition == 0)
        return ERR_IGNITION;

    if (data->wheel_pulse_count > 100U||data->wheel_pulse_count<=0)
        return ERR_WSS;

    if (data->accelerator_percent > 100U||data->accelerator_percent<=0)
        return ERR_ACCEL;

    if (data->brake_pressed > 1U)
        return ERR_BRAKE;

    if (data->yaw_deg < -180.0f || data->yaw_deg > 180.0f)
        return ERR_YAW;

    return SENSOR_OK;
}
int a =5;
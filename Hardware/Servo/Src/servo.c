
#include "servo.h"
#include <stdint.h>

void Servo_Init(Servo_t* servo, uint8_t servo_id, TIM_HandleTypeDef* htim, uint32_t channel) {
    servo->servo_id = servo_id;
    servo->htim = htim;
    servo->channel = channel;
    servo->pwm_duty = 0.0f;
    uint32_t frequency = HAL_RCC_GetPCLK1Freq() / (htim->Init.Prescaler + 1) / (htim->Init.Period + 1);
    if (frequency != 1000) {
        servo->htim->Init.Prescaler = 720-1;
        servo->htim->Init.Period = 100-1;
        HAL_TIM_PWM_Init(servo->htim);
    }
}

static float Servo_AngleToDuty(float angle) {
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;
    return SERVO_MIN_PULSE_WIDTH + (SERVO_MAX_PULSE_WIDTH - SERVO_MIN_PULSE_WIDTH) * (angle / 180.0f);
}

void Servo_SetAngle(Servo_t* servo, float angle) {
    servo->pwm_duty = Servo_AngleToDuty(angle);
    uint32_t pulse_length = (uint32_t)((servo->pwm_duty / 100.0f) * (servo->htim->Init.Period + 1));
    __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, pulse_length);
}
#ifndef SERVO_H
#define SERVO_H

#include "stm32f1xx_hal.h"//优先包含"main.h" 或"stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"//再包含这个文件，保证按正确顺序包含所有依赖
#include <stdint.h>

#define SERVO_MIN_PULSE_WIDTH 0.5f
#define SERVO_MAX_PULSE_WIDTH 12.5f


typedef struct{
    uint8_t servo_id;
    TIM_HandleTypeDef* htim;
    uint32_t channel;
    float pwm_duty;
}Servo_t ;

void Servo_Init(Servo_t* servo, uint8_t servo_id, TIM_HandleTypeDef* htim, uint32_t channel) ;
void Servo_SetAngle(Servo_t* servo, float angle) ;

#endif /* SERVO_H */

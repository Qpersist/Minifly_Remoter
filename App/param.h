#ifndef ___PARAM_H_
#define ___PARAM_H_
#include "stm32f10x.h"

void Param_Init(void);
void SAVE_RC_OFFSET(void);
void READ_RC_OFFSET(void);
void READ_CONF(void);
enum {
    ROLL = 3,
    PITCH=2,
    YAW=0,
    THROTTLE=1,
    AUX1,
    AUX2,
    AUX3,
    AUX4
};
extern int16_t DataTrim[8];
#endif



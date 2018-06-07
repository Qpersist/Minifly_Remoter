#ifndef ___ADC_H_
#define ___ADC_H_

#include "appconfig.h"

extern __IO uint16_t g_u16a7_ADCValue_CMS[7];


void g_v_ADCInit(void);
void g_v_AdcCalculate(void);
void KeyCheck(void);



#endif

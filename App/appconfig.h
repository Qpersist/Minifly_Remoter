#ifndef __appconfig_H
#define __appconfig_H

#include "stm32f10x.h"

typedef struct
{
	float rol;
	float pit;
	float yaw;
}T_float_angle;

typedef struct
{
	float X;
	float Y;
	float Z;
}T_float_xyz;

typedef struct
{
	int16_t X;
	int16_t Y;
	int16_t Z;
}T_int16_xyz;

typedef struct
{
	int32_t X;
	int32_t Y;
	int32_t Z;
}T_int32_xyz;



typedef struct int16_rcget
{
	int16_t ROLL;
	int16_t PITCH;
	int16_t THROTTLE;
	int16_t YAW;
	int16_t AUX1;
	int16_t AUX2;
	int16_t AUX3;
	int16_t AUX4;
	int16_t AUX5;
	int16_t AUX6;
}T_RC_Data;

typedef struct
{
	unsigned char ARMED;
}T_RC_Control;

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

extern T_int16_xyz	 g_t_Gyro_CMS;//两次综合后的传感器数据
extern T_int16_xyz	 g_t_Accel_CMS;
extern T_int16_xyz	 g_t_AccelAVG_CMS;
extern T_float_angle g_t_AttAngle_CMS;	//ATT函数计算出的姿态角
extern vs32			 g_vs_Alt_CMS;
extern T_RC_Data 	 g_t_Rc_D_CMS;		//遥控通道数据
extern T_RC_Control	 g_t_Rc_C_CMS;		//遥控功能数据
#endif

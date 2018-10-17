/*
 * app_litter_robot_3_led_sniffer.c
 *
 *  Created on: Oct 10, 2018
 *      Author: steve
 */


#include "app_litter_robot_3_led_sniffer.h"

tsCLD_MultistateInputBasic sLR3LSState;

void vHandleDeviceStateChange(teLitterRobot3StateEnum state);

void vHandleNewJoinEvent(void);

void vAPP_ZCL_DeviceSpecific_Init(void);
teZCL_Status eApp_ZLO_RegisterEndpoint(tfpZCL_ZCLCallBackFunction fptr);
void vAPP_ZCL_DeviceSpecific_UpdateIdentify(void);
void vAPP_ZCL_DeviceSpecific_SetIdentifyTime(uint16 u16Time);
void vAPP_ZCL_DeviceSpecific_IdentifyOff(void);

void vAppHandleStartup(void);
void vAppHandleRunning(ZPS_tsAfEvent* psStackEvent);

/*
 * IKS01A3Motion.cpp
 *
 *  Created on: Nov 12, 2024
 *      Author: seraphin
 */

#include <IKS01A3_Motion.h>
#include <numeric>

#include "retarget.h"
#include <iostream>

IKS01A3_Motion::IKS01A3_Motion() {}

IKS01A3_Motion::~IKS01A3_Motion() {}

void IKS01A3_Motion::enable(uint32_t instance, uint32_t function){
	IKS01A3_MOTION_SENSOR_Enable(instance, function);
}

void IKS01A3_Motion::getValue(uint32_t instance, uint32_t function, int32_t* XAxis, int32_t* YAxis, int32_t* ZAxis){
	IKS01A3_MOTION_SENSOR_Axes_t values;
	IKS01A3_MOTION_SENSOR_GetAxes(instance, instance, &values);
	*XAxis = values.x - AxisOffsets.x;
	*YAxis = values.y - AxisOffsets.y;
	*ZAxis = values.z - AxisOffsets.z;
}

void IKS01A3_Motion::init(uint32_t instance, uint32_t function){
	IKS01A3_MOTION_SENSOR_Init(instance, function);
	index_array = 0;
}

void IKS01A3_Motion::setZero(uint32_t instance, uint32_t function){
	IKS01A3_MOTION_SENSOR_GetAxes(instance, function, &AxisOffsets);
}

void IKS01A3_Motion::updateValues(uint32_t instance, uint32_t function){

	IKS01A3_MOTION_SENSOR_Axes_t values;
	IKS01A3_MOTION_SENSOR_GetAxes(instance, function, &values);

	RingBufferAxisX[index_array] = values.x - AxisOffsets.x;
	RingBufferAxisY[index_array] = values.y - AxisOffsets.y;
	RingBufferAxisZ[index_array] = values.z - AxisOffsets.z;

	index_array = (index_array + 1) % RingBufferAxisX.size();

	int32_t zero = 0;
	AxisValues.x = std::accumulate(RingBufferAxisX.cbegin(), RingBufferAxisX.cend(), zero) / static_cast<int32_t>(RingBufferAxisX.size());
	AxisValues.y = std::accumulate(RingBufferAxisY.cbegin(), RingBufferAxisY.cend(), zero) / static_cast<int32_t>(RingBufferAxisY.size());
	AxisValues.z = std::accumulate(RingBufferAxisZ.cbegin(), RingBufferAxisZ.cend(), zero) / static_cast<int32_t>(RingBufferAxisZ.size());
}

void IKS01A3_Motion::getAVGValues(int32_t* XAxis, int32_t* YAxis, int32_t* ZAxis){
	*XAxis = AxisValues.x;
	*YAxis = AxisValues.y;
	*ZAxis = AxisValues.z;
}

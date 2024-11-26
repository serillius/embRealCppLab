/*
 * IKS01A3Motion.cpp
 *
 *  Created on: Nov 12, 2024
 *      Author: seraphin
 */

#include <IKS01A3_Motion.h>
#include <numeric>

#include "retarget.h"


IKS01A3_Motion::IKS01A3_Motion() {
    StatsAxisX.insert(std::make_pair("Min", 0));
    StatsAxisY.insert(std::make_pair("Min", 0));
    StatsAxisZ.insert(std::make_pair("Min", 0));
    StatsAxisX.insert(std::make_pair("Max", 0));
    StatsAxisY.insert(std::make_pair("Max", 0));
    StatsAxisZ.insert(std::make_pair("Max", 0));
    StatsAxisX.insert(std::make_pair("AVG", 0));
    StatsAxisY.insert(std::make_pair("AVG", 0));
    StatsAxisZ.insert(std::make_pair("AVG", 0));
}

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
}

void IKS01A3_Motion::setZero(uint32_t instance, uint32_t function){
	IKS01A3_MOTION_SENSOR_GetAxes(instance, function, &AxisOffsets);
}

void IKS01A3_Motion::updateValues(uint32_t instance, uint32_t function){

	IKS01A3_MOTION_SENSOR_Axes_t values;
	IKS01A3_MOTION_SENSOR_GetAxes(instance, function, &values);

	values.x -= AxisOffsets.x;
	values.y -= AxisOffsets.y;
	values.z -= AxisOffsets.z;

	if(RingBufferAxisX.size() >= ARRAY_SIZE) {
		RingBufferAxisX.erase(RingBufferAxisX.begin());
	}
	RingBufferAxisX.push_back(values.x);

	if(RingBufferAxisY.size() >= ARRAY_SIZE) {
		RingBufferAxisY.erase(RingBufferAxisY.begin());
	}
	RingBufferAxisY.push_back(values.y);

	if(RingBufferAxisZ.size() >= ARRAY_SIZE) {
		RingBufferAxisZ.erase(RingBufferAxisZ.begin());
	}
	RingBufferAxisZ.push_back(values.z);

	int32_t zero = 0;
	AxisValues.x = std::accumulate(RingBufferAxisX.begin(), RingBufferAxisX.end(), zero) / static_cast<int32_t>(RingBufferAxisX.size());
	AxisValues.y = std::accumulate(RingBufferAxisY.begin(), RingBufferAxisY.end(), zero) / static_cast<int32_t>(RingBufferAxisY.size());
	AxisValues.z = std::accumulate(RingBufferAxisZ.begin(), RingBufferAxisZ.end(), zero) / static_cast<int32_t>(RingBufferAxisZ.size());

    //determine min and max of X-Axis
    auto itr_min = StatsAxisX.find("Min");
    auto itr_max = StatsAxisX.find("Max");
    auto minmax = std::minmax_element(RingBufferAxisX.begin(), RingBufferAxisX.end());
    itr_min->second=*minmax.first;
    itr_max->second=*minmax.second;

    //determine min and max of y-Axis
    itr_min = StatsAxisY.find("Min");
    itr_max = StatsAxisY.find("Max");
    minmax = std::minmax_element(RingBufferAxisY.begin(), RingBufferAxisY.end());
    itr_min->second=*minmax.first;
    itr_max->second=*minmax.second;

    //determine min and max of z-Axis
    itr_min = StatsAxisZ.find("Min");
    itr_max = StatsAxisZ.find("Max");
    minmax = std::minmax_element(RingBufferAxisZ.begin(), RingBufferAxisZ.end());
    itr_min->second=*minmax.first;
    itr_max->second=*minmax.second;

    //pass average to map
    auto itr_avg = StatsAxisX.find("AVG");
    itr_avg->second = AxisValues.x;
    itr_avg = StatsAxisY.find("AVG");
    itr_avg->second = AxisValues.y;
    itr_avg = StatsAxisZ.find("AVG");
    itr_avg->second = AxisValues.z;

}

void IKS01A3_Motion::getAVGValues(int32_t* XAxis, int32_t* YAxis, int32_t* ZAxis){
	auto itr_avg = StatsAxisX.find("AVG");
	*XAxis = itr_avg->second;
	itr_avg = StatsAxisY.find("AVG");
	*YAxis = itr_avg->second;
	itr_avg = StatsAxisZ.find("AVG");
	*ZAxis = itr_avg->second;
}

void IKS01A3_Motion::getMinValues(int32_t* XAxis, int32_t* YAxis, int32_t* ZAxis){
	auto itr_min = StatsAxisX.find("Min");
	*XAxis = itr_min->second;
	itr_min = StatsAxisY.find("Min");
	*YAxis = itr_min->second;
	itr_min = StatsAxisZ.find("Min");
	*ZAxis = itr_min->second;
}

void IKS01A3_Motion::getMaxValues(int32_t* XAxis, int32_t* YAxis, int32_t* ZAxis){
	auto itr_max = StatsAxisX.find("Max");
	*XAxis = itr_max->second;
	itr_max = StatsAxisY.find("Max");
	*YAxis = itr_max->second;
	itr_max = StatsAxisZ.find("Max");
	*ZAxis = itr_max->second;
}

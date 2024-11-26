/*
 * IKS01A3Motion.h
 *
 *  Created on: Nov 12, 2024
 *      Author: seraphin
 */

#ifndef SRC_IKS01A3MOTION_H_
#define SRC_IKS01A3MOTION_H_

#include "iks01a3_motion_sensors.h"
#include <vector>
#include <iterator>
#include <map>
#include <cstring>
#include <functional>
#include <iostream>
#include "util_ring_allocator_std.h"

struct StrCompare : public std::binary_function<const char*, const char*, bool> {
public:
	bool operator() (const char* str1, const char* str2) const
	{ return std::strcmp(str1, str2) < 0; }
};

typedef std::map<const char*, int32_t, StrCompare, util::ring_allocator_std< std::pair<const char* const, int32_t>>> StatsAxis_t;

class IKS01A3_Motion {
public:

	static constexpr int ARRAY_SIZE = 10;

	IKS01A3_Motion();
	virtual ~IKS01A3_Motion();

	void enable(uint32_t instance, uint32_t function);
	void getValue(uint32_t instance, uint32_t function, int32_t* XAxis, int32_t* YAxis, int32_t* ZAxis);
	void init(uint32_t instance, uint32_t function);
	void setZero(uint32_t instance, uint32_t function);
	void updateValues(uint32_t instance, uint32_t function);
	void getAVGValues(int32_t* XAxis, int32_t* YAxis, int32_t* ZAxis);
	void getMinValues(int32_t* XAxis, int32_t* YAxis, int32_t* ZAxis);
	void getMaxValues(int32_t* XAxis, int32_t* YAxis, int32_t* ZAxis);

private:
	IKS01A3_MOTION_SENSOR_Axes_t AxisValues;
	IKS01A3_MOTION_SENSOR_Axes_t AxisOffsets;

	std::vector<int32_t, util::ring_allocator_std<int32_t>> RingBufferAxisX{};
	std::vector<int32_t, util::ring_allocator_std<int32_t>> RingBufferAxisY{};
	std::vector<int32_t, util::ring_allocator_std<int32_t>> RingBufferAxisZ{};
	StatsAxis_t StatsAxisX;
	StatsAxis_t StatsAxisY;
	StatsAxis_t StatsAxisZ;

};

#endif /* SRC_IKS01A3MOTION_H_ */

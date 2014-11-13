#pragma once

#include <BWAPI.h>
#include <type_traits>

/**
 * Various utilities for working with time in Starcraft.
 *
 * Just keeping things simple for now and convert all values 
 * representing time to Latency Frame time. 
 */

/**
 * Convert Logical Frame time to Latency Frame time.
 */
template <class T>
typename std::enable_if<std::is_arithmetic<T>::value,T>::type
LOGICAL_FRAME(T x)
{
	 return x * BWAPI::Broodwar->getLatencyFrames();
}


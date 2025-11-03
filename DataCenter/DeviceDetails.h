#pragma once
#include <string>

using DeviceId = std::string;
using BatchId = std::string;
using DesignId = std::string;
struct T_DeviceDetails
{
	DeviceId name;
	BatchId batch;
	DesignId design;
};
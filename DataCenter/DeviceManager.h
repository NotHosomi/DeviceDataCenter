#pragma once
#include <string>
#include <unordered_map>

class DeviceManager
{
	DeviceManager();
public:
	static DeviceManager& Get();

	bool Load(const std::string& sDirectory);
private:
	std::unordered_map<std::string, 
};


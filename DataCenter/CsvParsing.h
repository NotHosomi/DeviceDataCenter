#pragma once
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>
#include <vector>

namespace CSV
{
	std::ifstream openFileR(std::string name);
	std::ofstream openFileW(std::string name);

	// switch to string_view if performance is poor

	std::vector<std::string> delimit(std::string s, std::string delimiter);
	std::pair<std::string, std::string> delimitOnce(std::string s, std::string delimiter);
};


#pragma once
#include <string>
#include <vector>

class PrintTable
{
public:
	PrintTable(const std::vector<std::string>& vHeaders);

	void AddRow(const std::vector<std::string>& vRow, std::string sColourCode = "");
	//void SetRow(unsigned int row, std::vector<std::string> vRow);
	//void SetCell(unsigned int row, unsigned int col, std::string contents);

	void Print(std::string sColour = "");
private:
	void PrintRow(const std::vector<std::string>& vRow);
	void UpdateColWidths(const std::vector<std::string>& vRow);
	std::vector<std::vector<std::string>> m_vRows;
	std::vector<std::string> m_vRowColours;
	std::vector<std::string> m_vHeaders;
	std::vector<int> m_vColumnWidths;
};


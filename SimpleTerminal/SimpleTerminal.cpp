// SimpleTerminal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <array>
#include <fstream>
#include "TerminalColours.h"
#include "Ingester.h"
#include "ErrorBarData.h"
#include "Grapher.h"
#include "PrintTable.h"

std::string RoundToStr(double num) { return std::to_string(static_cast<int>(num + 0.5)); }

int main()
{
	//SetConsoleOutputCP(CP_UTF8);
	std::cout << TERM_RESET;
	//"C:\\Users\\Hosomi\\OneDrive - Imperial College London\\Data\\";
	std::string dataPath = "";
	do
	{
		std::cout << "Input data path: ";
		std::cin >> dataPath;
		std::cin.clear();
	} while (!std::filesystem::exists(dataPath));

	std::string deviceId = "";
	std::string devicePath = "";
	Grapher grapher(dataPath);
	for(;;)
	{
		std::cout << "Input device ID: ";
		std::cin >> deviceId;
		std::cin.clear();
		devicePath = dataPath + "/" + deviceId;
		if (!std::filesystem::exists(devicePath))
		{
			continue;
		}

		Ingester ingest(devicePath);

		// Load EIS
		std::cout << "\nFetching EIS values..." << std::endl;
		std::map<std::string, std::array<double,3>> ImpedanceKeyvals = ingest.GetEisKeyvals();

		// EIS Table
		PrintTable EisTable({ "Electrode", "100 Hz", "1000 Hz", "1995 Hz" });
		double sum = 0.0;
		int validCount = 0;
		for (const auto& iter : ImpedanceKeyvals)
		{
			std::string colour = TERM_RED;
			if (iter.second[1] <= 20000)
			{
				sum += iter.second[0];
				validCount += 1;
				colour = TERM_GREEN;
			}
			EisTable.AddRow({iter.first, RoundToStr(iter.second[0]), RoundToStr(iter.second[1]), RoundToStr(iter.second[2]) }, colour);
		}
		EisTable.Print(TERM_YELLOW);
		std::cout << "Average: " << (sum / validCount) << std::endl;

		// EIS Plot
		std::array<T_ErrorBarD, 2> EisData = ingest.GetEisPlot();
		grapher.GraphEIS(deviceId, EisData[0], EisData[1]);

		// Load CV
		std::map<std::string, double> CscVals = ingest.CalculateCscVals();
		PrintTable CscTable({ "Electrode", "CSC (mC/cm^2)" });
		sum = 0.0;
		for (const auto& iter : CscVals)
		{
			CscTable.AddRow({ iter.first, std::to_string(iter.second) });
			std::cout << "  " << iter.first << ": " << iter.second << std::endl;
			sum += iter.second;
		}
		CscTable.Print(TERM_YELLOW);
		std::cout << "  Average: " << (sum / CscVals.size()) << std::endl;

		// CIL
		T_CilData cils = ingest.CalculateCilVals();
		std::vector<std::string> cilTableHeaders{ "Electrode #" };
		for (const auto& pulseWidth : cils.vPulseWidths) { cilTableHeaders.push_back(std::to_string(pulseWidth) + "us"); };
		PrintTable cilTable(cilTableHeaders);
		for (const auto& row : cils.mCilVals)
		{
			std::vector<std::string> rowtext{ std::to_string(row.first)};
			for (const auto& val : row.second) { rowtext.push_back(std::to_string(val)); };
			cilTable.AddRow(rowtext);
		}
		cilTable.Print();


		// Plot CIL values
		//todo
	}
}
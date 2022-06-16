#pragma once

#include <vector>
#include <string>

class DataContext {
public:
	int numberOfInfected;
	int numberOfDead;
	int numberOfRecovered;
	int numberOfTests;
	int numberOfConfirmedTests;

	std::vector<int> vectorOfInfected;
	std::vector<int> vectorOfDead;
	std::vector<int> vectorOfRecovered;
	std::vector<int> vectorOfTests;
	std::vector<int> vectorOfConfirmedTests;

	std::vector<int> vectorOfSimulationDays;

	DataContext() = default;
	DataContext(const size_t sizeOfVectors);

	~DataContext() = default;

	void SaveDataOnStep(const int currentDay);

	void SaveDataInFile(const std::string& path) const;
};

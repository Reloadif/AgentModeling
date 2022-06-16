#include <fstream>

#include "DataContext.h"

DataContext::DataContext(const size_t sizeOfVectors) : numberOfInfected(0), numberOfDead(0), numberOfRecovered(0),
													   numberOfTests(0), numberOfConfirmedTests(0) {
	vectorOfInfected.reserve(sizeOfVectors);
	vectorOfDead.reserve(sizeOfVectors);
	vectorOfRecovered.reserve(sizeOfVectors);
	vectorOfTests.reserve(sizeOfVectors);
	vectorOfConfirmedTests.reserve(sizeOfVectors);

	vectorOfSimulationDays.reserve(sizeOfVectors);
}

void DataContext::SaveDataOnStep(const int currentDay) {
	vectorOfInfected.push_back(numberOfInfected);
	vectorOfDead.push_back(numberOfDead);
	vectorOfRecovered.push_back(numberOfRecovered);
	vectorOfTests.push_back(numberOfTests);
	vectorOfConfirmedTests.push_back(numberOfConfirmedTests);

	numberOfInfected = 0;
	numberOfDead = 0;
	numberOfRecovered = 0;
	numberOfTests = 0;
	numberOfConfirmedTests = 0;

	vectorOfSimulationDays.push_back(currentDay);
}

void DataContext::SaveDataInFile(const std::string& path) const {
	std::ofstream file;
	file.open(path);

	for (int i = 0; i < vectorOfSimulationDays.size(); ++i) {
		file << vectorOfSimulationDays[i];
		if (i != vectorOfSimulationDays.size() - 1) {
			file << ",";
		}
	}

	file << std::endl;

	for (int i = 0; i < vectorOfInfected.size(); ++i) {
		file << vectorOfInfected[i];
		if (i != vectorOfInfected.size() - 1) {
			file << ",";
		}
	}

	file << std::endl;

	for (int i = 0; i < vectorOfDead.size(); ++i) {
		file << vectorOfDead[i];
		if (i != vectorOfDead.size() - 1) {
			file << ",";
		}
	}

	file << std::endl;

	for (int i = 0; i < vectorOfRecovered.size(); ++i) {
		file << vectorOfRecovered[i];
		if (i != vectorOfRecovered.size() - 1) {
			file << ",";
		}
	}

	file << std::endl;

	for (int i = 0; i < vectorOfConfirmedTests.size(); ++i) {
		file << vectorOfConfirmedTests[i];
		if (i != vectorOfConfirmedTests.size() - 1) {
			file << ",";
		}
	}

	file.close();
}

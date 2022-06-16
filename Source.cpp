#include <iostream>
#include <random>
#include <numeric>
#include <algorithm>

#include "Agent.h"
#include "MockAgent.h"
#include "DataContext.h"

#define DISEASE_TRANSMISSION_RATE 5
#define DISEASE_TRANSMISSION_RATE_IN_PUBLIC_TRANSPORT 2
#define NUMBER_OF_SOCIAL_CONNECTIONS 15
#define NUMBER_OF_SOCIAL_CONNECTIONSIN_PUBLIC_TRANSPORT 35
#define NUMBER_OF_SIMULATION_DAYS 60
#define TEST_FAILURE_PROBABILITY 10
#define START_OF_ACTIVE_TESTING 8

std::random_device GlobalDev;
std::mt19937 GlobalGen(GlobalDev());

bool ProbabilityOfInfection() {
	return (GlobalGen() % 100) < DISEASE_TRANSMISSION_RATE;
}

bool ProbabilityOfInfectionInPublicTransport() {
	return (GlobalGen() % 100) < DISEASE_TRANSMISSION_RATE_IN_PUBLIC_TRANSPORT;
}

bool ProbabilityOfDying(const int age) {
	bool result = false;
	int randomValue = GlobalGen() % 44001;

	if (age <= 10) {
		result = false;
	}
	else if (10 < age && age <= 30 && randomValue < 2) {
		result = true;
	}
	else if (30 < age && age <= 40 && randomValue < 3) {
		result = true;
	}
	else if (40 < age && age <= 50 && randomValue < 4) {
		result = true;
	}
	else if (50 < age && age <= 60 && randomValue < 13) {
		result = true;
	}
	else if (60 < age && age <= 70 && randomValue < 36) {
		result = true;
	}
	else if (70 < age && age <= 80 && randomValue < 80) {
		result = true;
	}
	else if (80 < age && randomValue < 148) {
		result = true;
	}

	return result;
}

void SimulateInfection(const size_t nubmerOfAgents, const size_t numberOfZeroPatient) {
	MockAgent mock;
	std::vector<Agent> vectorOfAgents = mock.GetRandomSampling(nubmerOfAgents);

	std::uniform_int_distribution<> zeroPatientDist(0, nubmerOfAgents - 1);
	for (size_t i = 0; i < numberOfZeroPatient; ++i) {
		vectorOfAgents[zeroPatientDist(GlobalDev)].Infection();
	}

	DataContext dataContext(NUMBER_OF_SIMULATION_DAYS);
	dataContext.numberOfInfected = numberOfZeroPatient;

	int numberSocialConnections = NUMBER_OF_SOCIAL_CONNECTIONS;
	int numberSocialConnectionsInPublicTransport = NUMBER_OF_SOCIAL_CONNECTIONSIN_PUBLIC_TRANSPORT;

	for (int currentDay = 0; currentDay < NUMBER_OF_SIMULATION_DAYS; ++currentDay) {
		/*if (currentDay > 15) {
			numberSocialConnectionsInPublicTransport = 15;
			numberSocialConnections = 10;
		}
		else if (currentDay > 30) {
			numberSocialConnectionsInPublicTransport = 12;
			numberSocialConnections = 5;
		}*/

		for (auto currentAgent = vectorOfAgents.begin(); currentAgent != vectorOfAgents.end(); ++currentAgent) {
			if (currentAgent->GetIsChecked()) {
				continue;
			}

			if ((GlobalGen() % 1000) < 2) {
				currentAgent->SetSelfIsolation();
			}

			if (currentAgent->GetIsInfected()) {
				currentAgent->IncrementCounterDaySick();

				int currentSocialConn = (GlobalGen() % (numberSocialConnections + 1));
				int startAgent = (GlobalGen() % (vectorOfAgents.size() - numberSocialConnections + 1));

				if (!currentAgent->GetIsSelfIsolated()) {
					for (int i = startAgent; i < startAgent + currentSocialConn; i++) {
						if (!vectorOfAgents[i].GetIsInfected() && !vectorOfAgents[i].GetIsChecked()) {
							if (ProbabilityOfInfection()) {
								vectorOfAgents[i].Infection();
								dataContext.numberOfInfected += 1;
							}
						}
					}
					
					int currentSocialConnPublic = (GlobalGen() % (numberSocialConnectionsInPublicTransport + 1));
					int startAgentPublic = (GlobalGen() % (vectorOfAgents.size() - numberSocialConnectionsInPublicTransport + 1));

					if (!currentAgent->GetHaveOwnTransport()) {
						for (int i = startAgentPublic; i < startAgentPublic + currentSocialConnPublic; i++) {
							if (!vectorOfAgents[i].GetIsInfected() && !vectorOfAgents[i].GetHaveOwnTransport() && !vectorOfAgents[i].GetIsChecked()) {
								if (ProbabilityOfInfectionInPublicTransport()) {
									vectorOfAgents[i].Infection();
									dataContext.numberOfInfected += 1;
								}
							}
						}
					}
				}

				if (currentAgent->GetHealthStatus() == HealthStatus::PostIncubation
					&& !currentAgent->GetIsSelfIsolated()
					&& !currentAgent->GetIsTested()) {

					if (currentDay > START_OF_ACTIVE_TESTING) {
						if ((GlobalGen() % 100) > TEST_FAILURE_PROBABILITY) {
							currentAgent->SetTest();
							dataContext.numberOfTests += 1;
							dataContext.numberOfConfirmedTests += 1;

							for (int j = startAgent; j < startAgent + 4; j++) {
								if (!vectorOfAgents[j].GetIsTested() && !vectorOfAgents[j].GetIsChecked()) {
									vectorOfAgents[j].SetTest();
									dataContext.numberOfTests += 1;

									if (vectorOfAgents[j].GetIsInfected()) {
										dataContext.numberOfConfirmedTests += 1;
									}
								}
							}
						}
					}
				}

				if (currentAgent->GetHealthStatus() == HealthStatus::Sick
					&& ProbabilityOfDying(currentAgent->GetAge())) {
					currentAgent->SetIsChecked();
					dataContext.numberOfDead += 1;
					continue;
				}

				if (currentAgent->IsRecovered()) {
					currentAgent->SetIsChecked();
					dataContext.numberOfRecovered += 1;
					continue;
				}
			}
		}

		dataContext.SaveDataOnStep(currentDay);
	}

	std::cout << "Зараженных " << std::accumulate(dataContext.vectorOfInfected.begin(), dataContext.vectorOfInfected.end(), 0) << std::endl;
	std::cout << "Умерших " << std::accumulate(dataContext.vectorOfDead.begin(), dataContext.vectorOfDead.end(), 0) << std::endl;
	std::cout << "Выздоровевших " << std::accumulate(dataContext.vectorOfRecovered.begin(), dataContext.vectorOfRecovered.end(), 0) << std::endl;
	std::cout << "Тестов сделано " << std::accumulate(dataContext.vectorOfTests.begin(), dataContext.vectorOfTests.end(), 0) << std::endl;
	std::cout << "Тестов подтверждено " << std::accumulate(dataContext.vectorOfConfirmedTests.begin(), dataContext.vectorOfConfirmedTests.end(), 0) << std::endl;

	dataContext.SaveDataInFile("./ModelingData.csv");
}

int main() {
	setlocale(LC_ALL, "RUS");
	SimulateInfection(1244254, 21);

	return 0;
}

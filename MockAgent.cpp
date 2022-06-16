#include "MockAgent.h"

#include <random>

MockAgent::MockAgent() {}

std::vector<Agent> MockAgent::GetRandomSampling(const size_t sizeOfSapmling) {
	std::vector<Agent> result;
	result.reserve(sizeOfSapmling);

	std::random_device dev;
	std::mt19937 gen(dev());

	for (size_t i = 0; i < sizeOfSapmling; ++i) {
		int randomValue = gen() % 10000;
		int age = 0;

		if (randomValue <= 1219) {
			age = gen() % 10;
		}
		else if (1219 < randomValue && randomValue <= 3367) {
			age = (gen() % 20) + 10;
		}
		else if (3367 < randomValue && randomValue <= 5046) {
			age = (gen() % 10) + 30;
		}
		else if (5046 < randomValue && randomValue <= 6450) {
			age = (gen() % 10) + 40;
		}
		else if (6450 < randomValue && randomValue <= 7764) {
			age = (gen() % 10) + 50;
		}
		else if (7764 < randomValue && randomValue <= 9021) {
			age = (gen() % 10) + 60;
		}
		else if (9021 < randomValue && randomValue <= 9613) {
			age = (gen() % 10) + 70;
		}
		else if (9613 < randomValue && randomValue < 10000) {
			age = (gen() % 16) + 80;
		}

		Gender gender = (gen() % 2) == 0 ? Gender::Male : Gender::Female;
		bool ownTransport = (gen() % 100) < 42 ? true : false;

		result.push_back(Agent(i, gender, age, ownTransport));
	}

	return result;
}

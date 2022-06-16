#pragma once

#include <vector>

#include "Agent.h"

class MockAgent {

public:
	MockAgent();
	~MockAgent() = default;

	std::vector<Agent> GetRandomSampling(const size_t sizeOfSapmling);
};

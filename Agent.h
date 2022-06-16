#pragma once

enum class Gender {
	Male,
	Female
};

enum class HealthStatus {
	Default,
	Incubation,
	PostIncubation,
	Sick,
	Recover
};

class Agent {
	unsigned int m_id;

	Gender m_gender;
	int m_age;

	HealthStatus m_healthStatus;
	bool m_isHaveOwnTransport;
	bool m_isInfected;
	int m_counterDaySick;
	bool m_isTested;
	bool m_isSelfIsolated;

	bool m_isChecked;

public:
	Agent() = delete;
	Agent(const int id, const Gender gender, const int age, const bool ownTransport);

	~Agent() = default;

	int GetId() const;

	Gender GetGender() const;
	int GetAge() const;

	HealthStatus GetHealthStatus() const;

	bool GetHaveOwnTransport() const;
	bool GetIsInfected() const;
	int GetCounterDaySick() const;
	bool GetIsTested() const;
	bool GetIsSelfIsolated() const;

	bool GetIsChecked() const;

	bool IsRecovered() const;
	void Infection();
	void IncrementCounterDaySick();
	void SetTest();
	void SetSelfIsolation();

	void SetIsChecked();

	bool operator== (const Agent& otherAgent);
	bool operator!= (const Agent& otherAgent);
};

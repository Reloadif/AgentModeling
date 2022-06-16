#include "Agent.h"

Agent::Agent(const int id, const Gender gender, const int age, const bool ownTransport) : m_id(id),
	m_gender(gender), m_age(age), m_healthStatus(HealthStatus::Default), 
	m_isHaveOwnTransport(ownTransport), m_isInfected(false),
	m_counterDaySick(-1), m_isTested(false),
	m_isSelfIsolated(false), m_isChecked(false)
{

}

int Agent::GetId() const {
	return m_id;
}

Gender Agent::GetGender() const {
	return m_gender;
}

int Agent::GetAge() const {
	return m_age;
}

HealthStatus Agent::GetHealthStatus() const {
	return m_healthStatus;
}

bool Agent::GetHaveOwnTransport() const {
	return m_isHaveOwnTransport;
}

bool Agent::GetIsInfected() const {
	return m_isInfected;
}

int Agent::GetCounterDaySick() const {
	return m_counterDaySick;
}

bool Agent::GetIsTested() const {
	return m_isTested;
}

bool Agent::GetIsSelfIsolated() const {
	return m_isSelfIsolated;
}

bool Agent::GetIsChecked() const {
	return m_isChecked;
}

bool Agent::IsRecovered() const {
	return m_healthStatus == HealthStatus::Recover;
}

void Agent::Infection() {
	m_healthStatus = HealthStatus::Incubation;
	m_isInfected = true;
	m_counterDaySick = 0;
}

void Agent::IncrementCounterDaySick() {
	m_counterDaySick += 1;

	if (3 < m_counterDaySick && m_counterDaySick <= 10) {
		m_healthStatus = HealthStatus::PostIncubation;
	}
	else if (10 < m_counterDaySick && m_counterDaySick <= 20) {
		m_healthStatus = HealthStatus::Sick;
	}
	else if (m_counterDaySick > 20) {
		m_healthStatus = HealthStatus::Recover;

		m_isInfected = false;
		m_counterDaySick = -1;

		m_isChecked = true;
	}
}

void Agent::SetTest() {
	m_isTested = true;

	if (m_isInfected) {
		m_isSelfIsolated = true;
	}
}

void Agent::SetSelfIsolation() {
	m_isSelfIsolated = true;
}

void Agent::SetIsChecked() {
	m_isChecked = true;
}

bool Agent::operator== (const Agent & otherAgent) {
	return m_id == otherAgent.m_id;
}

bool Agent::operator!= (const Agent & otherAgent) {
	return m_id != otherAgent.m_id;
}

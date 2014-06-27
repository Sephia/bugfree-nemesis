// StateManager.cpp

#include "stdafx.h"
#include "StateManager.h"
#include "State.h"
#include "WindowManager.h"

StateManager::StateManager() {
	m_currentState = nullptr;
}

StateManager::~StateManager() {

}

void StateManager::AddState(State* state) {
	if (state != nullptr) {
		state->Init();
		m_states.push_back(state);
	}
	else {
		std::cout << "State is null when trying to push it!\n";
	}
}

void StateManager::SetState(StateName name) {
	for (unsigned int i = 0; i < m_states.size(); i++) {
		if (m_states.at(i)->IsState(name)) {
			m_currentState = m_states.at(i);
		}
	}
}

bool StateManager::ChangeState() {
	StateName nextState = m_currentState->GetNextState();

	for (unsigned int i = 0; i < m_states.size(); i++) {
		if (m_states.at(i)->IsState(nextState)) {
			m_currentState->Exit();
			m_currentState = m_states.at(i);
			m_currentState->Enter();
			return true;
		}
	}
	std::cout << "Could not find the next state! : " << nextState << std::endl;
	return false;
}

int StateManager::UpdateEvents() {
	return m_currentState->UpdateEvents();
}

int StateManager::Update() {
	if (m_currentState != nullptr) {
		return m_currentState->Update();
	}
	std::cout << "No current state at Update()\n";
	return false;
}

void StateManager::Draw() {
	m_currentState->Draw();
}

void StateManager::CleanUp() {
	m_currentState = nullptr;

	for (int i = 0; i < m_states.size(); i++) {
		m_states.at(i)->CleanUp();
		delete m_states.at(i);
		m_states.at(i) = nullptr;
	}
}
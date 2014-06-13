// StateManager.cpp

#include "stdafx.h"
#include "StateManager.h"
#include "State.h"
#include "WindowManager.h"

StateManager::StateManager() {

}

StateManager::~StateManager() {

}

void StateManager::AddState(State* state) {
	if (state != nullptr) {
		m_states.push_back(state);
	}
	else {
		std::cout << "State is null when trying to add!\n";
	}
}

void StateManager::SetState(std::string name) {
	for (unsigned int i = 0; i < m_states.size(); i++) {
		if (m_states.at(i)->IsState(name)) {
			m_currentState = m_states.at(i);
		}
	}
}

int StateManager::ChangeState() {
	std::string nextState = m_currentState->GetNextState();

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
	// TODO: Write clean up code here

}
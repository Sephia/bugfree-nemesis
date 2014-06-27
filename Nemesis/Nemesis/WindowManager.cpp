// WindowManager.cpp

#include "stdafx.h"
#include "WindowManager.h"

bool WindowManager::m_instanceFlag = false;
WindowManager* WindowManager::m_single = nullptr;

WindowManager::~WindowManager() {
	m_instanceFlag = false;
}

WindowManager* WindowManager::GetInstance() {
	if (!m_instanceFlag) {
		m_single = new WindowManager();
		m_instanceFlag = true;
	}

	return m_single;
}

void WindowManager::RemoveInstance() {
	delete m_single;
	m_single = nullptr;
}

void WindowManager::Init() {
	m_window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Nemesis", sf::Style::Default);
	m_view = new sf::View(sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2), sf::Vector2f(m_window->getSize()));
	//m_view = new sf::View(sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2), sf::Vector2f(WORLDSIZE * TILESIZE, WORLDSIZE * TILESIZE));
}

bool WindowManager::PollEvents(sf::Event* event) {
	return m_window->pollEvent(*event);
}

void WindowManager::Draw(sf::Sprite* sprite) {
	m_window->draw(*sprite);
}

void WindowManager::UpdateViewPosition(Position pos) {
	m_view->setCenter(sf::Vector2f(ceilf(pos.m_x), ceilf(pos.m_y)));
	m_window->setView(*m_view);
}

void WindowManager::Display() {

	m_window->display();

	m_window->clear();
}

void WindowManager::CleanUp() {
	if (m_window != nullptr) {
		m_window->close();
		delete m_window;
		m_window = nullptr;
	}

	if (m_view != nullptr) {
		delete m_view;
		m_view = nullptr;
	}
}
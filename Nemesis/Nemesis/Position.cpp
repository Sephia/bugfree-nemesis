#include "stdafx.h"
#include "Position.h"


Position::Position(int _x, int _y) {
	m_x = _x;
	m_y = _y;
}

Position &Position::operator-(Position &_rhs) {
	m_x -= _rhs.m_x;
	m_y -= _rhs.m_y;
	return *this;
}

Position &Position::operator+(Position &_rhs) {
	m_x -= _rhs.m_x;
	m_y -= _rhs.m_y;
	return *this;
}

Position &Position::operator*(float &_rhs) {
	m_x = (int)(m_x * _rhs);
	m_y = (int)(m_y * _rhs);
	return *this;
}

Position &Position::operator*(int &_rhs) {
	m_x *= _rhs;
	m_y *= _rhs;
	return *this;
}

Position &Position::operator/(float &_rhs) {
	if (_rhs < 0.0001f && _rhs > -0.0001f) {
		_rhs = 1.0f;
	}
	m_x = (int)(m_x / _rhs);
	m_y = (int)(m_y / _rhs);
	return *this;
}

Position &Position::operator/(int &_rhs) {
	if (_rhs == 0) {
		_rhs = 1;
	}
	m_x /= _rhs;
	m_y /= _rhs;
	return *this;
}

void Position::Normalize() {
	float length = sqrt((float)(m_x * m_x + m_y * m_y));
	if (length > 0.0001f) {
		m_x = (int)(m_x / length);
		m_y = (int)(m_y / length);
	}
}
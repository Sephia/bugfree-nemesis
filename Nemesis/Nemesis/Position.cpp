#include "stdafx.h"
#include "Position.h"


Position::Position(float _x, float _y) {
	m_x = _x;
	m_y = _y;
}

Position Position::operator-(Position &_rhs) {
	Position pos(m_x - _rhs.m_x, m_y - _rhs.m_y);
	return pos;
}

Position Position::operator+(Position &_rhs) {
	Position pos(m_x + _rhs.m_x, m_y + _rhs.m_y);
	return pos;
}

Position Position::operator*(float &_rhs) {
	Position pos(m_x * _rhs, m_y * _rhs);
	return pos;
}

Position Position::operator*(int &_rhs) {
	Position pos(m_x + _rhs, m_y + _rhs);
	return pos;
}

Position Position::operator/(float &_rhs) {
	if (_rhs < 0.0001f && _rhs > -0.0001f) {
		_rhs = 1.0f;
	}

	Position pos(m_x / _rhs, m_y / _rhs);
	return pos;
}

Position Position::operator/(int &_rhs) {
	if (_rhs == 0) {
		_rhs = 1;
	}

	Position pos(m_x / _rhs, m_y / _rhs);
	return pos;
}

void Position::Normalize() {
	float length = sqrt(m_x * m_x + m_y * m_y);
	if (length > 0.0001f) {
		m_x /= length;
		m_y /= length;
	}
}
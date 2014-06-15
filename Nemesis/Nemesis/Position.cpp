#include "stdafx.h"
#include "Position.h"


Position::Position(int _x, int _y) {
	m_x = _x;
	m_y = _y;
}

Position &Position::operator-(Position &_rhs) {
	return Position(m_x - _rhs.m_x, m_y - _rhs.m_y);
}

Position &Position::operator+(Position &_rhs) {
	return Position(m_x - _rhs.m_x, m_y - _rhs.m_y);
}

Position &Position::operator*(float &_rhs) {
	return Position(m_x * _rhs, m_y * _rhs);
}

Position &Position::operator*(int &_rhs) {
	return Position(m_x * _rhs, m_y * _rhs);
}

Position &Position::operator/(float &_rhs) {
	if (_rhs > 0.0001f || _rhs < -0.0001f) {
		return Position(m_x / _rhs, m_y / _rhs);
	}
}

Position &Position::operator/(int &_rhs) {
	if (_rhs != 0) {
		return Position(m_x / _rhs, m_y / _rhs);
	}
}

void Position::Normalize() {
	float length = sqrtf(m_x * m_x + m_y * m_y);
	if (length > 0.0001f) {
		m_x /= length;
		m_y /= length;
	}
}
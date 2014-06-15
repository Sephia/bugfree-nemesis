// Position

#pragma once

class Position {
public:
	Position(int _x = 0, int _y = 0);

	Position &operator-(Position &_rhs);
	Position &operator+(Position &_rhs);
	Position &operator*(float &_rhs);
	Position &operator*(int &_rhs);
	Position &operator/(float &_rhs);
	Position &operator/(int &_rhs);

	void Normalize();

public:
	int m_x;
	int m_y;
};


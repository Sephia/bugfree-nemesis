// Position

#pragma once

class Position {
public:
	Position(float _x = 0.0f, float _y = 0.0f);

	Position operator-(Position &_rhs);
	Position operator+(Position &_rhs);
	Position operator*(float &_rhs);
	Position operator*(int &_rhs);
	Position operator/(float &_rhs);
	Position operator/(int &_rhs);

	void Normalize();

public:
	float m_x;
	float m_y;
};


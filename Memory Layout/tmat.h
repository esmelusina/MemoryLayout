#pragma once
#include "tvec.h"

class matinterface
{
public:
	const float rows;
	const float cols;
	matinterface(float r, float c) : rows(r), cols(c) {}
};

template<size_t rows, size_t cols> class tmat : matinterface
{
	tmat() : matinterface(rows, cols) {}
	float m_data[rows][cols];
	size_t nrows() { return rows; }
	size_t ncols() { return cols; }

public:
	// no compile-time safety
	operator*(const matinterface &rhs);
};
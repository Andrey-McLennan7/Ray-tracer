#pragma once

#include <cmath>

float random_float()
{
	// Returns a random real in [0,1).
	return std::rand() / (RAND_MAX + 1.0f);
}

const int size{ 100 };

// Global variables
float random_floats_x[size]{
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,

	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,

	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,

	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,

	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
};

float random_floats_y[size]{
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,

	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,

	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,

	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,

	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
	random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f, random_float() - 0.5f,
};
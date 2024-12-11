#pragma once

#include <GLM/glm.hpp>

struct Ray
{
	// Ray variables
	glm::vec3 m_origin{ glm::vec3(0.0f) };
	glm::vec3 m_direction{ glm::vec3(0.0f) };
};
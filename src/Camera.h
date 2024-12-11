#pragma once

#include <GLM/glm.hpp>

struct Ray;

class Camera
{
private:

	glm::mat4 m_projection;
	glm::mat4 m_view;

public:

	Camera(const glm::ivec2& winSize);

	Ray GetRay(const glm::vec2& pixelPos, const glm::ivec2& winSize);

};
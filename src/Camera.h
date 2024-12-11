#pragma once

#include <GLM/glm.hpp>

struct Ray;

class Camera
{
private:

	glm::mat4 m_projection;
	glm::mat4 m_view;

	glm::vec3 m_position;
	float m_fov;

public:

	Camera(const glm::ivec2& winSize, float fov = 45.0f, const glm::vec3& position = glm::vec3{ 0.0f });

	Ray GetRay(const glm::vec2& pixelPos, const glm::ivec2& winSize);

	void position(const glm::vec3& position);
	glm::vec3 position() const;

	void FOV(float fov);
	float FOV() const;
};
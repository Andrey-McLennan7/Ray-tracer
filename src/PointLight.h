#pragma once

#include "Sphere.h"
#include <GLM/glm.hpp>

class Sphere;

class PointLight
{
private:

	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_colour;

	float m_intensity;

	std::shared_ptr<Sphere> m_sphere;

public:

	PointLight(float intensity, glm::vec3 position = glm::vec3{ 0.0f }, glm::vec3 colour = glm::vec3{ 1.0f });

	void position(glm::vec3 position);
	glm::vec3 position() const;

	glm::vec3 direction() const;

	void colour(glm::vec3 colour);
	glm::vec3 colour() const;

	void sphere(std::shared_ptr<Sphere> sphere);
	std::shared_ptr<Sphere> sphere() const;

	void intensity(float intensity);
};
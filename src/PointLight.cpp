#include "PointLight.h"

PointLight::PointLight(float intensity, glm::vec3 position, glm::vec3 colour) :
	m_intensity{ intensity },
	m_position{ position },
	m_colour{ colour }
{}

void PointLight::position(glm::vec3 position)
{
	this->m_position = position;
	this->m_direction = glm::normalize(position);
}

glm::vec3 PointLight::position() const
{
	return this->m_position;
}

glm::vec3 PointLight::direction(const glm::vec3& hit_pos) const
{
	return glm::normalize(this->m_position - hit_pos);
}

void PointLight::colour(glm::vec3 colour)
{
	this->m_colour = colour;
}

glm::vec3 PointLight::colour() const
{
	return this->m_colour * this->m_intensity;
}

void PointLight::sphere(std::shared_ptr<Sphere> sphere)
{
	this->m_sphere = sphere;
}

std::shared_ptr<Sphere> PointLight::sphere() const
{
	return this->m_sphere;
}

void PointLight::intensity(float intensity)
{
	this->m_intensity = intensity;
}
#include "Diffuse.h"
#include "PointLight.h"

Diffuse::Diffuse(const glm::vec3& colour) :
	m_colour{ colour }
{}

glm::vec3 Diffuse::shade(const Ray& ray,
						 const glm::vec3& intersection,
						 const PointLight& light,
						 const glm::vec3& normal) const
{
	// The dot product between the light direction and the surface normal
	float LdotN{ glm::max(glm::dot(light.direction(), normal), 0.0f) };

	// Calculate diffuse lighting
	glm::vec3 diffuse{ glm::vec3{ LdotN * light.colour() * this->m_colour } };

    return diffuse;
}
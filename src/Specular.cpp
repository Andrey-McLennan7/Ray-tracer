#include "Specular.h"
#include "PointLight.h"

Specular::Specular(float shininess) :
	m_shininess{ shininess }
{}

glm::vec3 Specular::shade(const Ray& ray,
						  const glm::vec3& intersection,
						  const PointLight& light,
						  const glm::vec3& normal) const
{
	// The dot product between the light direction and the surface normal
	float LdotN{ glm::max(glm::dot(light.direction(), normal), 0.0f) };

	// Calculate specular lighting
	float facing{ float(LdotN > 0.0f) };

	glm::vec3 halfVec{ glm::normalize(light.direction() - ray.m_direction) };
	glm::vec3 specular{ glm::vec3{ light.colour() * facing * std::pow(glm::max(glm::dot(normal, halfVec), 0.0f), this->m_shininess) } };

	return specular;
}
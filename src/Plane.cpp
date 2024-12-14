#include "Plane.h"
#include "Object.h"
#include "PointLight.h"
#include "Material.h"
#include "Ray.h"

Plane::Plane(glm::vec3 position, glm::vec3 normal, std::shared_ptr<Material> diff) :
	Object(position, diff),
	m_normal{ normal }
{}

bool Plane::ray_intersect(const Ray& ray, glm::vec3& intersection) const
{
	// Simplify the process of getting the values
	glm::vec3 a{ ray.m_origin };
	glm::vec3 n{ ray.m_direction };
	glm::vec3 N{ this->m_normal };
	glm::vec3 P0{ this->m_position };

	if (std::abs(glm::dot(n, N)) < 1e-16)
	{
		return false;
	}

	float num{ glm::dot((P0 - a), N) };
	float denom{ glm::dot(n, N) };

	float t{ num / denom };

	if (t < 0.0f)
	{
		return false;
	}

	intersection = a + (t * n);

	return true;
}

glm::vec3 Plane::shade(const Ray& ray, const glm::vec3& intersection, const PointLight& light) const
{
	// Final output
	glm::vec3 result{ 0.0f };

	// Iterate through every materail of the object
	std::vector<std::shared_ptr<Material>>::const_iterator itr;
	for (itr = this->m_materials.begin(); itr != this->m_materials.end(); ++itr)
	{
		result += (*itr)->shade(ray, intersection, light, this->m_normal);
	}

	return result;
}

glm::vec3 Plane::normal(const glm::vec3& intersection) const
{
	return this->m_normal;
}
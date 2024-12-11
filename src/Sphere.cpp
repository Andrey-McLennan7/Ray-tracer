#include "Sphere.h"
#include "PointLight.h"
#include "Ray.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <math.h>

Sphere::Sphere(float radius, glm::vec3 position, std::shared_ptr<Material> diff) :
	Object(position, diff),
	m_radius{ radius }
{}

bool Sphere::RayIntersect(const Ray& ray, glm::vec3& intersection) const
{
	// Simplify the process of getting the values
	glm::vec3 a{ ray.m_origin };
	glm::vec3 n{ ray.m_direction };
	glm::vec3 P{ this->m_position };

	float r{ this->m_radius };

	if (glm::length(P - a) > r)
	{
		// P (m)inus A (d)ot product of ray direction
		float PmAdN{ glm::dot((P - a), n) };

		float d{ glm::length(P - a - (PmAdN * n)) };

		if (d <= r)
		{
			float x{ sqrt((r * r) - (d * d)) };

			// There is an intersection
			intersection = a + ((PmAdN - x) * n);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

glm::vec3 Sphere::shade(const Ray& ray, const glm::vec3& intersection, const PointLight& light) const
{
	// Final output
	glm::vec3 result{ 0.0f };

	// Iterate through every material applied to the object
	std::vector<std::shared_ptr<Material>>::const_iterator itr;
	for (itr = this->m_materials.begin(); itr != this->m_materials.end(); ++itr)
	{
		result += (*itr)->shade(ray, intersection, light, this->normal(intersection));
	}

	return result;
}

glm::vec3 Sphere::normal(const glm::vec3& intersection) const
{
	return glm::normalize(intersection - this->m_position);
}
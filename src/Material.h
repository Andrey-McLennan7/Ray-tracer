#pragma once

#include <GLM/glm.hpp>

struct Ray;
class PointLight;

class Material
{
public:

	virtual glm::vec3 shade(const Ray& ray,
							const glm::vec3& intersection,
							const PointLight& light,
							const glm::vec3& normal) const = 0;
};
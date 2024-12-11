#pragma once
#include "Material.h"

class Diffuse : public Material
{
private:

	glm::vec3 m_colour;

public:

	Diffuse(const glm::vec3& colour = glm::vec3{ 1.0f });

	virtual glm::vec3 shade(const Ray& ray,
							const glm::vec3& intersection,
							const PointLight& light,
							const glm::vec3& normal) const override;
};
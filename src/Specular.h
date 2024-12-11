#pragma once
#include "Material.h"

class Specular : public Material
{
private:

	float m_shininess;

public:

	Specular(float shininess = 50.0f);

	virtual glm::vec3 shade(const Ray& ray,
							const glm::vec3& intersection,
							const PointLight& light,
							const glm::vec3& normal) const override;
};
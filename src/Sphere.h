#pragma once

#include "Object.h"

class Sphere : public Object
{
private:

	float m_radius;

public:

	Sphere(float radius, glm::vec3 position = glm::vec3{ 0.0f }, std::shared_ptr<Material> diff = std::make_shared<Diffuse>());

	virtual bool ray_intersect(const Ray& ray, glm::vec3& intersection) const override;

	virtual glm::vec3 shade(const Ray& ray, const glm::vec3& intersection, const PointLight& light) const override;
	virtual glm::vec3 normal(const glm::vec3& intersection) const override;
};
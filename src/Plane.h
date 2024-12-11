#pragma once

#include "Object.h"

class Plane : public Object
{
private:

	glm::vec3 m_normal;

public:

	Plane(glm::vec3 position = glm::vec3{ 0.0f }, glm::vec3 normal = glm::vec3{ 0.0f, 1.0f, 0.0f }, std::shared_ptr<Material> diff = std::make_shared<Diffuse>());

	virtual bool RayIntersect(const Ray& ray, glm::vec3& intersection) const override;

	virtual glm::vec3 shade(const Ray& ray, const glm::vec3& intersection, const PointLight& light) const override;
	virtual glm::vec3 normal(const glm::vec3& intersection) const override;
};
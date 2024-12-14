#pragma once

#include "Ray.h"
#include "Diffuse.h"

#include <GLM/glm.hpp>
#include <memory>
#include <vector>

struct Ray;

class PointLight;

class Object
{
protected:

	glm::vec3 m_position;

	std::vector<std::shared_ptr<Material>> m_materials;

public:

	Object(glm::vec3 position = glm::vec3{ 0.0f }, std::shared_ptr<Material> diff = std::make_shared<Diffuse>());

	virtual bool ray_intersect(const Ray& ray, glm::vec3& intersection) const = 0;

	virtual glm::vec3 shade(const Ray& ray, const glm::vec3& intersection, const PointLight& light) const = 0;
	virtual glm::vec3 normal(const glm::vec3& intersection) const = 0;

	void add_material(std::shared_ptr<Material> material);
};
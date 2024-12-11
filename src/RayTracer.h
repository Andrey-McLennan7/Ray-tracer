#pragma once

#include "PointLight.h"

#include <vector>
#include <memory>

struct Ray;

class Object;

class RayTracer
{
private:

	std::vector<std::shared_ptr<Object>> m_scene_objects;
	std::vector<std::shared_ptr<PointLight>> m_lights;

	bool m_shadows;

public:

	RayTracer(bool shadows = false);

	glm::vec3 TraceRay(Ray ray);

	void add_object(std::shared_ptr<Object> object);
	void add_light(std::shared_ptr<PointLight> light);

	// Allows the user to have the preference of
	// having shadows in the scene
	void enable_shadows(bool enable);
};
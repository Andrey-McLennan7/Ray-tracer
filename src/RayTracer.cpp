#include "RayTracer.h"
#include "PointLight.h"
#include "Object.h"
#include "Plane.h"
#include "Sphere.h"
#include "Ray.h"

RayTracer::RayTracer(bool shadows) :
	m_shadows{ shadows }
{}

glm::vec3 RayTracer::TraceRay(Ray ray)
{
	// Calculate the background colour
	float a = 0.5f * (glm::normalize(ray.m_direction).y + 1.0f);
	glm::vec3 background_colour{ ((1.0f - a) * glm::vec3{ 1.0f }) + (a * glm::vec3{ 0.5f, 0.7f, 1.0f }) };

	// Calculate the scene objects (i.e., spheres and plane)
	glm::vec3 intersection{ 0.0f };
	glm::vec3 closest_intersection{ 0.0f };
	glm::vec3 pixel_colour{ 0.0f };

	std::shared_ptr<Object> object_ptr{ nullptr };

	float closest_depth{ std::numeric_limits<float>::max() };

	// Detect any ray intersections between the camera ray and any of the objects
	std::vector<std::shared_ptr<Object>>::iterator o_itr;
	for (o_itr = this->m_scene_objects.begin(); o_itr != this->m_scene_objects.end(); ++o_itr)
	{
		if ((*o_itr)->ray_intersect(ray, intersection))
		{
			// If there is an intersection, then first calculate the depth
			float depth{ glm::length(intersection - ray.m_origin) };

			// If the depth is smaller than the closest one so far,
			// then set that as the closest depth, save the closes
			// intersection, and store the object in a pointer for
			// future reference.
			//
			// This is too ensure that the closer objects in the scene
			// have greater priority than the objects (or parts of the
			// objects) behind them
			//
			if (depth < closest_depth)
			{
				closest_depth = depth;
				closest_intersection = intersection;
				object_ptr = *o_itr;
			}
		}
	}

	// Draw background colour when there is no intersection
	if (object_ptr == nullptr)
	{
		return background_colour;
	}

	// Draw shadows, if the user wants them in their scene
	if (this->m_shadows)
	{
		// Iterate through each light source in the scene 
		std::vector<std::shared_ptr<PointLight>>::iterator l_itr;
		for (l_itr = this->m_lights.begin(); l_itr != this->m_lights.end(); ++l_itr)
		{
			bool pixel_is_shadowed{ false };

			for (o_itr = this->m_scene_objects.begin(); o_itr != this->m_scene_objects.end(); ++o_itr)
			{
				if (*o_itr == object_ptr)
				{
					continue;
				}

				glm::vec3 shadow_intersection{ 0.0f };

				// Cast a shadow ray from the camera ray intersection point
				Ray shadow_ray{ closest_intersection, glm::normalize((*l_itr)->position() - closest_intersection) };

				// Detect any intersection between the shadow ray and the light source(s)
				if ((*o_itr)->ray_intersect(shadow_ray, shadow_intersection))
				{
					// If there is an intersection, then detect if any of the objects are not too close to the light sources(s)
					if ((glm::length(shadow_intersection - closest_intersection) < glm::length((*l_itr)->position() - closest_intersection)))
					{
						pixel_is_shadowed = true;
						break;
					}
				}
			}

			// If there is no intersection between the shadow ray and the light source(s)
			// then draw the pixel normally with the colour of the object
			if (!pixel_is_shadowed)
			{
				pixel_colour += object_ptr->shade(ray, closest_intersection, **l_itr);
			}
		}
	}
	else
	{
		// Draw the scene normally if the user does not want any shadows
		std::vector<std::shared_ptr<PointLight>>::iterator l_itr;
		for (l_itr = this->m_lights.begin(); l_itr != this->m_lights.end(); ++l_itr)
		{
			pixel_colour += object_ptr->shade(ray, closest_intersection, **l_itr);
		}
	}

	// Put put the final colour for the pixel
	return pixel_colour;
}

void RayTracer::add_object(std::shared_ptr<Object> object)
{
	this->m_scene_objects.push_back(object);
}

void RayTracer::add_light(std::shared_ptr<PointLight> light)
{
	this->m_lights.push_back(light);
}

void RayTracer::enable_shadows(bool enable)
{
	this->m_shadows = enable;
}
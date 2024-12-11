#include "Camera.h"
#include "Ray.h"

#include <GLM/gtc/matrix_transform.hpp>

Camera::Camera(const glm::ivec2& winSize, float fov, const glm::vec3& position) :
	m_projection{ glm::mat4(1.0f) }, m_view{ glm::mat4(1.0f) },
	m_position{ position }, m_fov{ fov }
{
	this->m_projection = glm::perspective(glm::radians(fov), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);
	this->m_view = glm::translate(this->m_view, position);
}

Ray Camera::GetRay(const glm::vec2& pixelPos, const glm::ivec2& winSize)
{
	Ray ray;

	// Convert the scene box into a Normalised Device Coordinates (NDC)
	// This is to ensure that the cube begins with -1 and ends with +1 
	float pixel_pos_x{ (float)pixelPos.x / (float)winSize.x * 2.0f - 1.0f };
	float pixel_pos_y{ (float)pixelPos.y / (float)winSize.y * 2.0f - 1.0f };

	// Generate the coordinate of the ray (origin and direction) to start
	// from -1 and end with +1
	glm::vec4 near_point{ glm::vec4{ pixel_pos_x, pixel_pos_y, -1.0f, 1.0f } };
	glm::vec4 far_point{ glm::vec4{ pixel_pos_x, pixel_pos_y, 1.0f, 1.0f } };

	// Multiply the coordinates by the inverse projection matrix
	// 
	// This distorts the cude into a correct perspective volume,
	// meaning that any object closer to the camera will be larger
	// than the once further away
	//
	near_point = glm::inverse(this->m_projection) * near_point;
	far_point = glm::inverse(this->m_projection) * far_point;

	// Convert the coordinates from left-hand rule to right-hand rule
	near_point = near_point / near_point.w;
	far_point = far_point / far_point.w;

	// Multiply the coordinates by the inverse view matrix
	// 
	// Helps convert the view of the objects from eye (local) space
	// to world space
	//
	near_point = glm::inverse(this->m_view) * near_point;
	far_point = glm::inverse(this->m_view) * far_point;

	// Set where the ray begins and what direction it's going to
	ray.m_origin = near_point;
	ray.m_direction = glm::normalize(far_point - near_point);

	return ray;
}

void Camera::position(const glm::vec3& position)
{
	this->m_position = position;
}

glm::vec3 Camera::position() const
{
	return this->m_position;
}

void Camera::FOV(float fov)
{
	this->m_fov = fov;
}

float Camera::FOV() const
{
	return this->m_fov;
}
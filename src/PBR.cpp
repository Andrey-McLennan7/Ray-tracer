#include "PBR.h"

#include "Ray.h"
#include "PointLight.h"

PBR::PBR(float roughness, float metallic, float ao, const glm::vec3& albedo) :
	m_roughness{ roughness },
	m_metallic{ metallic },
	m_ao{ ao }, m_f0{ 0.04f },
	m_albedo{ albedo }, PI{ 3.14159265359f }
{}

float PBR::DistributionGGX(const glm::vec3& N, const glm::vec3& H) const
{
	float a{ this->m_roughness * this->m_roughness };
	float a2{ a * a };
	float NdotH{ glm::max(glm::dot(N, H), 0.0f) };
	float NdotH2{ NdotH * NdotH };

	float num{ a2 };
	float denom{ (NdotH2 * (a2 - 1.0f) + 1.0f) };

	denom = this->PI * denom * denom;

	return num / denom;
}

float PBR::GeometrySmith(const glm::vec3& N, const glm::vec3& V, const glm::vec3& L) const
{
	float NdotV{ glm::max(glm::dot(N, V), 0.0f) };
	float NdotL{ glm::max(glm::dot(N, L), 0.0f) };

	float ggx1{ this->GeometrySchlickGGX(NdotL) };
	float ggx2{ this->GeometrySchlickGGX(NdotV) };

	return ggx1 * ggx2;
}

float PBR::GeometrySchlickGGX(float NdotV) const
{
	float r{ this->m_roughness - 1.0f };
	float k{ (r * r) / 8.0f };

	float num{ NdotV };
	float denom{ NdotV * (1.0f - k) + k };

	return num / denom;
}

glm::vec3 PBR::FresnelSchlick(float cos_theta, const glm::vec3& F0) const
{
	return F0 + (1.0f - F0) * pow(1.0f - cos_theta, 5.0f);
}

glm::vec3 PBR::shade(const Ray& ray,
					 const glm::vec3& intersection,
					 const PointLight& light,
					 const glm::vec3& normal) const
{
	glm::vec3 light_dir{ glm::normalize(light.position() - intersection) };
	glm::vec3 ray_dir{ -ray.m_direction };

	ray_dir = glm::normalize(ray_dir);

	glm::vec3 halfVec{ glm::normalize(light_dir + ray_dir) };
	glm::vec3 F0{ glm::mix(this->m_f0, this->m_albedo, this->m_metallic) };

	// Calculate light radians
	float distance{ glm::length(light.position() - intersection) };
	float attenuation{ 1.0f / (distance * distance) };
	glm::vec3 radians{ light.colour() * attenuation};

	// Cook-torrance BRDF
	float   NDF{ this->DistributionGGX(normal, halfVec) };
	float     G{ this->GeometrySmith(normal, ray_dir, light_dir) };
	glm::vec3 F{ this->FresnelSchlick(glm::max(glm::dot(halfVec, ray_dir), 0.0f), F0) };

	glm::vec3 kS{ F };
	glm::vec3 kD{ glm::vec3{ 1.0f } - kS };

	kD = kD * (1.0f - this->m_metallic);

	glm::vec3 num{ NDF * G * F };
	float denom{ 4.0f * glm::max(glm::dot(normal, ray_dir), 0.0f) * glm::max(glm::dot(normal, light_dir), 0.0f) + 0.0001f };

	glm::vec3 specular{ num / denom };

	// Add outgoing radiance
	float NdotL{ glm::max(glm::dot(normal, light_dir), 0.0f) };
	glm::vec3 L0{ ((kD * this->m_albedo) / (this->PI + specular)) * radians * NdotL };

	glm::vec3 ambient{ glm::vec3{ 0.03f } * this->m_albedo * this->m_ao };
	glm::vec3 colour{ ambient + L0 };

	colour = colour / (colour + glm::vec3{ 1.0f });
	colour = glm::pow(colour, glm::vec3(1.0f / 2.2f));

	return colour;
}

void PBR::roughness(float roughness)
{
	this->m_roughness = roughness;
}

float PBR::roughness() const
{
	return this->m_roughness;
}

void PBR::metallic(float metallic)
{
	this->m_metallic = metallic;
}

float PBR::metallic() const
{
	return this->m_metallic;
}

void PBR::ambient_occlusion(float ao)
{
	this->m_ao = ao;
}

float PBR::ambient_occlusion() const
{
	return this->m_ao;
}

void PBR::albedo(const glm::vec3 albedo)
{
	this->m_albedo = albedo;
}

glm::vec3 PBR::albedo() const
{
	return this->m_albedo;
}
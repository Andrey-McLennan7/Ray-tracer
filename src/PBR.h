#pragma once
#include "Material.h"

class PBR : public Material
{
private:

	const float PI;

	float m_roughness;
	float m_metallic;
	float m_ao;

	const glm::vec3 m_f0;
	glm::vec3 m_albedo;

	float DistributionGGX(const glm::vec3& N, const glm::vec3& H) const;
	float GeometrySmith(const glm::vec3& N, const glm::vec3& V, const glm::vec3& L) const;
	float GeometrySchlickGGX(float NdotV) const;

	glm::vec3 FresnelSchlick(float cos_theta, const glm::vec3& F0) const;

public:

	PBR(float roughness, float metallic, float ao, const glm::vec3& albedo = glm::vec3{ 1.0f });

	virtual glm::vec3 shade(const Ray& ray,
							const glm::vec3& intersection,
							const PointLight& light,
							const glm::vec3& normal) const override;

	void roughness(float roughness);
	float roughness() const;

	void metallic(float metallic);
	float metallic() const;

	void ambient_occlusion(float ao);
	float ambient_occlusion() const;

	void albedo(const glm::vec3 albedo);
	glm::vec3 albedo() const;
};
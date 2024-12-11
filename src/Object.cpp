#include "Object.h"

Object::Object(glm::vec3 position, std::shared_ptr<Material> diff) :
	m_position{ position }
{
	this->m_materials.push_back(diff);
}

void Object::add_material(std::shared_ptr<Material> material)
{
	this->m_materials.push_back(material);
}
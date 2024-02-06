#include "Entity.hpp"

Entity::Entity(size_t id,const std::string& tag) : m_id(id), m_tag(tag) {}


size_t Entity::getId() const
{
    return m_id;
}


const std::string& Entity::getTag() const
{
    return m_tag;
}


bool Entity::isActive() const
{
    return m_is_active;
}

void Entity::destroy()
{
    m_is_active = false;
}

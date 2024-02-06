#include "EntityManager.hpp"

EntityManager::EntityManager() {}


std::shared_ptr<Entity>EntityManager::addEntity(const std::string& tag)
{
    std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity(m_total++, tag));
    m_entites_to_add.push_back(e);
    return e;
}


const EntityVector& EntityManager::getEntites() const
{
    return m_entites;
}


const EntityVector& EntityManager::getEntites(const std::string& tag)
{
    return m_entites_map[tag];
}

void EntityManager::removeInactiveEntites(EntityVector& vec)
{
    for(auto it = vec.begin(); it != vec.end(); )
    {   if((*it)->isActive() == false)
        {
            it = vec.erase(it);
        }
        else
            it++;
    }

    for(auto& pair : m_entites_map)
    {
        auto& vect = pair.second;
        for(auto it = vect.begin(); it != vect.end(); )
        {   if((*it)->isActive() == false)
            {
                it = vect.erase(it);
            }
            else
                it++;
        }
    }
}

void EntityManager::update()
{
    this->removeInactiveEntites(m_entites);
    for(auto e : m_entites_to_add)
    {
        m_entites.push_back(e);
        m_entites_map[e->getTag()].push_back(e);
    }
    m_entites_to_add.clear();
}

#include "Entity.hpp"
#include "Commans.hpp"

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
    EntityVector m_entites;
    EntityVector m_entites_to_add;
    EntityMap m_entites_map;
    size_t m_total = 0;

    void removeInactiveEntites(EntityVector& vec);

public:
    EntityManager();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    const EntityVector& getEntites() const;
    const EntityVector& getEntites(const std::string& tag);
};

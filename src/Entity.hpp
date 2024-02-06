#pragma once
#include "Commans.hpp"
#include "components.hpp"
class Entity
{
    friend class EntityManager;

    bool m_is_active = true;
    size_t m_id = 0;
    std::string m_tag = "Entity";

    Entity(size_t id,const std::string& tag);


public:

    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CLifespan> cLifespan;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput> cInput;

    size_t getId() const;
    const std::string& getTag() const;
    bool isActive ()const;
    void destroy();


};

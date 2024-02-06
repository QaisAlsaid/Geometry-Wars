#pragma once
#include "Commans.hpp"
using namespace kr::math;
struct CCollision
{
    float radius;
    CCollision(float radius) : radius(radius) {}
};


struct CTransform
{
    Vec2 position;
    Vec2 velocity;
    float angle;
    CTransform(Vec2 position, Vec2 velocity, float angle = 0)
     : position(position)
     , velocity(velocity)
     , angle(angle)
     {}
};


struct CScore
{
    int score = 0;
    CScore(int score) : score(score) {}
};


struct CShape
{
    sf::CircleShape shape;
    CShape(float radius, size_t points, Vec3 fill_color,Vec3 outline_color, float thickness)
    {
        shape.setRadius(radius);
        shape.setPointCount(points);
        shape.setFillColor(sf::Color(fill_color.x, fill_color.y, fill_color.z));
        shape.setOutlineColor(sf::Color(outline_color.x, outline_color.y, outline_color.z));
        shape.setOutlineThickness(thickness);
    }
};


struct CLifespan
{
    int remaining = 0;
    int total = 0;
    CLifespan(int total) : remaining(total), total(total) {}
};


struct CInput
{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;
    bool special = false;
};



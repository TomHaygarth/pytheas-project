#pragma once
#include "GameComponents.h"
#include "GameObject.h"
#include "../Graphics/Sprites/ISprite.h"
#include <glm/vec2.hpp>

namespace GameComponents
{
    class Blackhole : public GameObject
    {
    public:
        Blackhole(Graphics::Sprites::ISprite * sprite, const glm::vec3& position, float const collisionRadius, float const gravitationalDensity);

        glm::vec2 CalculateGravitationalPullOnObject(GameObject const & obj, float const objMass = 1.0f) const;

    private:
        float m_collisionRadius = 0.0f;
        float m_gravitationalDensity = 0.0f;
    };
}
#include "Blackhole.h"

namespace GameComponents
{
    Blackhole::Blackhole(Graphics::Sprites::ISprite * sprite, const glm::vec3& position, float const collisionRadius, float const gravitationalDensity)
    : GameObject(sprite, position)
    , m_collisionRadius(collisionRadius)
    , m_gravitationalDensity(gravitationalDensity)
    {

    }

    glm::vec2 Blackhole::CalculateGravitationalPullOnObject(GameObject const & obj, float const objMass) const
    {
        glm::vec2 result;

        glm::vec2 direction = m_position - obj.GetPosition();
        float distance = glm::length(direction);
        glm::vec2 normal = glm::normalize(direction);

        // when distance = 1, we want gravity to be normal * 9.8 * gravitiational density
        float const gravityConst = 9.8f;

        result = (normal * gravityConst * m_gravitationalDensity) / (distance * 0.01f);

        return result;
    }
}
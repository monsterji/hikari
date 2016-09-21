#include "hikari/client/game/objects/GameObjectDefinition.hpp"

namespace hikari {

    GameObjectDefinition::GameObjectDefinition()
        : deathType{DeathType::Nothing}
        , reflectionType{GameObjectDefinition::ReflectionType::NO_REFLECTION}
        , maximumAge{0}
    {

    }

    void GameObjectDefinition::setDeathType(DeathType::Type type) {
        deathType = type;
    }

    DeathType::Type GameObjectDefinition::getDeathType() const {
        return deathType;
    }

    void GameObjectDefinition::setReflectionType(GameObjectDefinition::ReflectionType type) {
        reflectionType = type;
    }

    GameObjectDefinition::ReflectionType GameObjectDefinition::getReflectionType() const {
        return reflectionType;
    }

    void GameObjectDefinition::setMaximumAge(float maximumAge) {
        this->maximumAge = maximumAge;
    }

    float GameObjectDefinition::getMaximumAge() const {
        return maximumAge;
    }

} // hikari

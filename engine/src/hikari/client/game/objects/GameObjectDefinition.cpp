#include "hikari/client/game/objects/GameObjectDefinition.hpp"

namespace hikari {

    GameObjectDefinition::GameObjectDefinition() {

    }

    void GameObjectDefinition::setReflectionType(GameObjectDefinition::ReflectionType type) {
      reflectionType = type;
    }

    GameObjectDefinition::ReflectionType GameObjectDefinition::getReflectionType() const {
      return reflectionType;
    }

} // hikari

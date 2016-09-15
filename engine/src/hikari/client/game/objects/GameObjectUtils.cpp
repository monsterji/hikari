#include "hikari/client/game/objects/GameObjectUtils.hpp"
#include "hikari/client/game/objects/GameObject.hpp"

namespace hikari {

    void GameObjectUtils::setDirection(GameObject & object, Direction direction) {
        object.direction = direction;
    }

    const Direction GameObjectUtils::getDirection(const GameObject & object) {
        return object.direction;
    }

} // hikari

#include "hikari/client/game/objects/GameObjectUtils.hpp"
#include "hikari/client/game/objects/GameObject.hpp"
#include "hikari/client/game/objects/GameObjectDefinition.hpp"

namespace hikari {

    const bool GameObjectUtils::canAge(const GameObject & object) {
        return object.ageFlag;
    }

    void GameObjectUtils::setAgeFlag(GameObject & object, bool canAge) {
        object.ageFlag = canAge;
    }

    const float GameObjectUtils::getAge(const GameObject & object) {
        return object.age;
    }

    void GameObjectUtils::setAge(GameObject & object, float newAge) {
        object.age = newAge;
    }

    void GameObjectUtils::advanceAge(GameObject & object, float amount) {
        setAge(object, object.age + amount);
    }

    const bool GameObjectUtils::isTooOld(const GameObject & object) {
        const auto * definition = object.getDefinition();

        if(definition != nullptr) {
            return getAge(object) >= definition->getMaximumAge();
        }

        // If the object has no defintion, it has no maximum age, so it can
        // never be "too old".
        return false;
    }


    void GameObjectUtils::setDirection(GameObject & object, Direction direction) {
        object.direction = direction;
    }

    const Direction GameObjectUtils::getDirection(const GameObject & object) {
        return object.direction;
    }

} // hikari

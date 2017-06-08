#ifndef HIKARI_CLIENT_GAME_GAMEOBJECTUTILS
#define HIKARI_CLIENT_GAME_GAMEOBJECTUTILS

#include "hikari/core/game/Direction.hpp"

namespace hikari {

    class GameObject;

    class GameObjectUtils {
    public:
        static const bool canAge(const GameObject & object);
        static void setAgeFlag(GameObject & object, bool canAge);
        static const float getAge(const GameObject & object);
        static void setAge(GameObject & object, float newAge);
        static void advanceAge(GameObject & object, float amount);
        static const bool isTooOld(const GameObject & object);

        static void setDirection(GameObject & object, Direction dir);
        static const Direction getDirection(const GameObject & object);
    };

} // hikari

#endif // HIKARI_CLIENT_GAME_GAMEOBJECTUTILS

#ifndef HIKARI_CLIENT_GAME_GAMEOBJECTUTILS
#define HIKARI_CLIENT_GAME_GAMEOBJECTUTILS

#include "hikari/core/game/Direction.hpp"

namespace hikari {

    class GameObject;

    class GameObjectUtils {
    public:
        static void setDirection(GameObject & object, Direction dir);
        static const Direction getDirection(const GameObject & object);
    };

} // hikari

#endif // HIKARI_CLIENT_GAME_GAMEOBJECTUTILS

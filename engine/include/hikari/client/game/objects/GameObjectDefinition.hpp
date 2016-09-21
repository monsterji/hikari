#ifndef HIKARI_CLIENT_GAME_GAMEOBJECTDEFINITION
#define HIKARI_CLIENT_GAME_GAMEOBJECTDEFINITION

#include "hikari/client/game/objects/DeathType.hpp"

namespace hikari {

    class GameObjectDefinition {
    public:
        enum ReflectionType {
            NO_REFLECTION,
            REFLECT_X,
            REFLECT_Y,
            REFLECT_XY
        };

    private:
        // - Enums
        // - Fixed-width numbers

        DeathType::Type deathType;
        ReflectionType reflectionType;

        float maximumAge;

    public:
        GameObjectDefinition();

        void setDeathType(DeathType::Type newDeathType);
        DeathType::Type getDeathType() const;

        void setReflectionType(ReflectionType type);
        ReflectionType getReflectionType() const;

        void setMaximumAge(float maximumAge);
        float getMaximumAge() const;
    };

} // hikari

#endif // HIKARI_CLIENT_GAME_GAMEOBJECTDEFINITION

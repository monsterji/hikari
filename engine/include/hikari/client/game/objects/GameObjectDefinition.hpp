#ifndef HIKARI_CLIENT_GAME_GAMEOBJECTDEFINITION
#define HIKARI_CLIENT_GAME_GAMEOBJECTDEFINITION

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
        ReflectionType reflectionType;

    public:
        GameObjectDefinition();

        void setReflectionType(ReflectionType type);
        ReflectionType getReflectionType() const;
    };

} // hikari

#endif // HIKARI_CLIENT_GAME_GAMEOBJECTDEFINITION

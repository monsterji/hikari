#ifndef HIKARI_CLIENT_GAME_GAMEOBJECT
#define HIKARI_CLIENT_GAME_GAMEOBJECT

#include "hikari/client/game/objects/GameObjectUtils.hpp"

#include "hikari/core/game/Direction.hpp"
#include "hikari/core/game/Updatable.hpp"

#include <cstdint>
#include <iostream>

namespace hikari {

    class EventBus;
    class GameObjectDefinition;
    class GameWorld;

    class GameObject : public Updatable {
    public:
        friend class GameObjectUtils;

        /**
         * An Id struct, borrowed from the EntityX framework. It tracks
         * an ID according to its index and version. Each time an index
         * is recycled, the version is incremented. Using these two
         * numbers you can determine if you're holding an outdated Id.
         *
         * This is used instead of pointers which have to be nullified, since
         * the pointed-to object could be destroyed without notifiying the
         * pointer owner.
         */
        struct Id {
            Id();
            explicit Id(std::uint64_t id);
            Id(std::uint32_t index, std::uint32_t version);

            std::uint64_t getId() const;

            bool operator == (const Id & other) const;
            bool operator != (const Id & other) const;
            bool operator < (const Id & other) const;

            std::uint32_t getIndex() const;
            std::uint32_t getVersion() const;

        private:
            static const std::uint64_t VERSION_BIT_SHIFT = 32UL;
            static const std::uint64_t INDEX_MASK = 0xffffffffUL;

            static inline std::uint64_t toId(std::uint32_t index, std::uint32_t version);

            std::uint64_t id;

            friend class GameWorld;
        };

        //
        // Static members
        //
        static const Id generateObjectId();
        static const Id INVALID;

    private:
        static std::uint64_t nextId;

    //
    // Class members
    //
    private:
        // The order of the members should be as follows:
        // - IDs
        // - Flags
        // - Enums
        // - Fixed-width numbers
        // - Pointers
        // - Structs
        Id id;
        Id parentId;

        bool activeFlag;   // Is this object active right now?
        bool obstacleFlag; // Does this object act like an obstacle?
        bool shieldFlag;   // Does this object deflect projectiles right now?
        bool ageFlag;      // Does this object experience aging?

        Direction direction;

        float age;

        const GameObjectDefinition * definition;
        EventBus * eventBus;

    protected:
        virtual void onActivated();
        virtual void onDeactivated();

    public:
        explicit GameObject(Id id = generateObjectId());
        GameObject(const GameObject & other);
        virtual ~GameObject();

        Id getId() const;

        Id getParentId() const;
        void setParentId(Id parentId);

        const GameObjectDefinition * const getDefinition() const;
        void setDefinition(const GameObjectDefinition * const definition);

        EventBus * const getEventBus() const;
        void setEventBus(EventBus * const eventBus);

        bool isActive() const;
        void setActive(bool activeFlag);

        /**
         * Gets the "obstacle status" of this GameObject.
         *
         * @return whether this GameObject is an obstacle or not
         * @see GameObject::setObstacleFlag
         */
        bool isObstacle() const;

        /**
         * Sets whether this GameObject acts like an obstacle. When an GameObject is
         * an obstacle, it obstructs the movement of other GameObjects. It can
         * also be stood on like solid ground.
         *
         * @param obstacle flag for whether this GameObject should be an obstacle or not
         * @see GameObject::isObstacle
         */
        void setObstacleFlag(bool obstacleFlag);

        virtual void update(float dt);

        virtual void reset();
    };

    inline std::ostream &operator << (std::ostream & out, const GameObject::Id & id) {
        out << "GameObject::Id(" << id.getIndex() << "." << id.getVersion() << ")";
        return out;
    }

    inline std::ostream &operator << (std::ostream & out, const GameObject & object) {
        out << "GameObject(" << object.getId() << ")";
        return out;
    }

} // hikari

namespace std {
    template <> struct hash<hikari::GameObject::Id> {
        std::size_t operator () (const hikari::GameObject::Id & id) const {
            return static_cast<std::size_t>(id.getIndex() ^ id.getVersion());
        }
    };

    template <> struct hash<hikari::GameObject> {
        std::size_t operator () (const hikari::GameObject & object) const {
            return static_cast<std::size_t>(object.getId().getIndex() ^ object.getId().getVersion());
        }
    };
} // std

#endif // HIKARI_CLIENT_GAME_GAMEOBJECT

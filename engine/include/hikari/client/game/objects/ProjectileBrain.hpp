#ifndef HIKARI_CLIENT_GAME_OBJECTS_PROJECTILEBRAIN
#define HIKARI_CLIENT_GAME_OBJECTS_PROJECTILEBRAIN

#include "hikari/client/game/objects/Projectile.hpp"
#include "hikari/core/util/Cloneable.hpp"

namespace Sqrat {
    class Table;
}

namespace hikari {

    class CollisionInfo;
    class Movable;
    class Projectile;

    /**
     * ProjectileBrain is the base class for all Projectile behaviors. It is where the
     * logic that makes each Projectile unique is implemented.
     *
     * @see ScriptedProjectileBrain
     */
    class ProjectileBrain {
    private:
        /** A pointer back to the host Projectile object */
        Projectile * host;

    protected:
        /**
         * Gets the pointer to the host Projectile object.
         *
         * @see ProjectileBrain::attach
         */
        Projectile * const getHost();

    public:
        /**
         * Default constructor.
         */
        ProjectileBrain();

        /**
         * Copy constructor.
         */
        ProjectileBrain(const ProjectileBrain & proto);

        /**
         * Destructor.
         */
        virtual ~ProjectileBrain();

        /**
         * Creates a new instance of the brain by copy-constructing it.
         *
         * @return a clone of the instance
         */
        virtual std::unique_ptr<ProjectileBrain> clone() const;

        /**
         * Attaches the ProjectileBrain to an instance of Projectile.
         *
         * @param host a pointer to an instance of Projectile to attach to
         * @see ProjectileBrain::detach
         * @see ProjectileBrain::getHost
         */
        virtual void attach(Projectile * host);

        /**
         * Detaches the brain from its host.
         *
         * @see ProjectileBrain::attach
         * @see ProjectileBrain::getHost
         */
        virtual void detach();

        /**
         * Called when collisions take place with tiles in the world. Allows for
         * handling of collision response from within a brain.
         *
         * @param body the host's body
         * @param info the collision information
         */
        virtual void handleCollision(Movable& body, CollisionInfo& info);

        /**
         * Called when collisions take place with other objects. Useful for
         * reacting to when the Projectile touches the player or some other object.
         *
         * @param otherId [description]
         */
        virtual void handleObjectTouch(int otherId);

        /**
         * Updates the brain's logic.
         *
         * @param dt time, in seconds, to update for
         */
        virtual void update(float dt);

        // virtual void applyConfig(const Sqrat::Table & instanceConfig);
    };

} // hikari

#endif // HIKARI_CLIENT_GAME_OBJECTS_PROJECTILEBRAIN

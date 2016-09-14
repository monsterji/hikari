#ifndef HIKARI_CLIENT_GAME_OBJECTS_ENEMY
#define HIKARI_CLIENT_GAME_OBJECTS_ENEMY

#include "hikari/client/game/objects/Entity.hpp"
#include "hikari/core/util/Cloneable.hpp"
#include <memory>

namespace Sqrat {
    class Table;
}

namespace hikari {

    class EnemyBrain;

    class Enemy : public Entity, public Cloneable<Enemy> {
    private:
        static const int DEFAULT_BONUS_TABLE;

        std::shared_ptr<EnemyBrain> brain;
        float hitPoints;

        /**
         * After taking damage this counts how many ticks that elapse.
         */
        int damageTickCounter;
        int bonusTableIndex;

        bool canLiveOffscreen;

    public:
        Enemy(GameObject::Id id = GameObject::generateObjectId(), std::shared_ptr<Room> room = nullptr);
        Enemy(const Enemy& proto);
        virtual ~Enemy();

        virtual std::unique_ptr<Enemy> clone() const;

        virtual void onActivated();
        virtual void onDeactivated();

        virtual void update(float dt);
        virtual void render(sf::RenderTarget &target);

        virtual void handleCollision(Movable& body, CollisionInfo& info);

        /**
         * Handles the case when another object touches this object. Allows the
         * object to react to a simple collision.
         *
         * @param otherId the ID of the other object
         */
        virtual void handleObjectTouch(GameObject::Id otherId);

        void setBrain(const std::shared_ptr<EnemyBrain> & brain);
        const std::shared_ptr<EnemyBrain>& getBrain() const;

        void setHitPoints(float hp);
        float getHitPoints() const;
        void takeDamage(float amount);

        void setBonusTableIndex(int index);
        int getBonusTableIndex() const;

        void setLiveOffscreen(bool flag);
        bool getLiveOffscreen() const;

        void applyConfig(const Sqrat::Table & instanceConfig);
    };

} // hikari

#endif // HIKARI_CLIENT_GAME_OBJECTS_ENEMY

#include "hikari/client/game/objects/Projectile.hpp"
#include "hikari/client/game/objects/ProjectileBrain.hpp"
#include "hikari/client/game/objects/Motion.hpp"
#include "hikari/client/game/objects/motions/LinearMotion.hpp"
#include "hikari/client/game/events/EventBus.hpp"
#include "hikari/client/game/events/EntityDeathEventData.hpp"
#include "hikari/core/game/SpriteAnimator.hpp"
#include "hikari/core/math/Vector2.hpp"
#include "hikari/core/util/Log.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace hikari {

    const std::shared_ptr<Motion> Projectile::DeflectedMotion = std::make_shared<LinearMotion>(Vector2<float>(-4.0f, -4.0f));

    Projectile::Projectile(int id, std::shared_ptr<Room> room)
        : Entity(id, room)
        , brain(nullptr)
        , inert(false)
        , parentId(-1)
        , reflectionType(NO_REFLECTION)
    {
        body.setGravitated(false);
        body.setHasWorldCollision(false);
    }

    Projectile::Projectile(const Projectile& proto)
        : Entity(proto)
        , brain(nullptr)
        , inert(false)
        , parentId(proto.parentId)
        , reflectionType(proto.reflectionType)
    {
        setActive(false);

        if(proto.brain) {
            setBrain(proto.brain->clone());
        }
    }

    Projectile::~Projectile() {

    }

    std::unique_ptr<Projectile> Projectile::clone() const {
        return std::unique_ptr<Projectile>(new Projectile(*this));
    }

    void Projectile::render(sf::RenderTarget &target) {
        Entity::render(target);
    }

    void Projectile::update(float dt) {
        Entity::update(dt);

        if(brain) {
            brain->update(dt);
        } else {
            if(getDirection() == Directions::Left) {
                setVelocityX(-4.0f);
            } else {
                setVelocityX(4.0f);
            }
        }
    }

    void Projectile::handleCollision(Movable& body, CollisionInfo& info) {
        if(getReflectionType() == REFLECT_X || getReflectionType() == REFLECT_XY) {
            if(info.isCollisionX) {
                if(info.directionX == Directions::Left) {
                    setDirection(Directions::Right);
                } else if(info.directionX == Directions::Right) {
                    setDirection(Directions::Left);
                }
            }
        }

        if(getReflectionType() == REFLECT_Y || getReflectionType() == REFLECT_XY) {
            if(info.isCollisionY) {
                if(info.directionY == Directions::Up) {
                    setDirection(Directions::Down);
                } else if(info.directionY == Directions::Down) {
                    setDirection(Directions::Up);
                }
            }
        }
    }

    void Projectile::setParentId(int id) {
        parentId = id;
    }

    int Projectile::getParentId() const {
        return parentId;
    }

    void Projectile::setMotion(const std::shared_ptr<Motion> motion) {
        this->motion = motion;
    }

    const std::shared_ptr<Motion>& Projectile::getMotion() const {
        return motion;
    }

    void Projectile::setBrain(std::unique_ptr<ProjectileBrain> && brain) {
        auto & oldBrain = this->brain;

        if(oldBrain) {
            oldBrain->detach();
        }

        this->brain.reset(brain.release());

        if(this->brain) {
            this->brain->attach(this);
        }
    }

    const std::unique_ptr<ProjectileBrain> & Projectile::getBrain() const {
        return brain;
    }

    void Projectile::setReflectionType(ReflectionType type) {
        reflectionType = type;
    }

    Projectile::ReflectionType Projectile::getReflectionType() const {
        return reflectionType;
    }

    void Projectile::setInert(bool inert) {
        this->inert = inert;
    }

    bool Projectile::isInert() const {
        return inert;
    }

    void Projectile::deflect() {
        setInert(true);
        setMotion(DeflectedMotion);
        setPhasing(true);
    }

    void Projectile::onDeath() {
        HIKARI_LOG(debug2) << "Projectile::onDeath()";
        if(auto eventManagetPtr = getEventBus().lock()) {
            // TODO: May want to triggerEvent() instead; test and see.
            eventManagetPtr->queueEvent(EventDataPtr(new EntityDeathEventData(getId(), EntityDeathEventData::Projectile)));
        }
    }

} // hikari

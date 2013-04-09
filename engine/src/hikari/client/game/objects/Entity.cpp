#include "hikari/client/game/objects/Entity.hpp"
#include "hikari/core/game/map/Room.hpp"
#include "hikari/core/game/map/Tileset.hpp"
#include "hikari/core/game/Animation.hpp"
#include "hikari/core/game/AnimationSet.hpp"
#include "hikari/core/game/SpriteAnimator.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "hikari/core/util/Log.hpp"

namespace hikari {

    bool Entity::debug = false;

    void Entity::enableDebug(const bool& debug) {
        #ifdef HIKARI_DEBUG_ENTITIES
        Entity::debug = debug;
        #endif // HIKARI_DEBUG_ENTITIES
    }

    Entity::Entity(const int& id, std::shared_ptr<Room> room)
        : GameObject(id)
        , room(room)
        , spriteTexture()
        , sprite()
        , animationSet()
        , currentAnimation()
        , animationPlayer(new SpriteAnimator(sprite))
        , direction(Directions::None)
        , currentAnimationName("")
    {
        reset();

        body.setCollisionCallback(
            std::bind(&Entity::handleCollision, this, std::placeholders::_1, std::placeholders::_2));

        #ifdef HIKARI_DEBUG_ENTITIES
        boxOutline.setFillColor(sf::Color(128, 64, 0, 128));
        boxOutline.setOutlineColor(sf::Color(255, 255, 255, 128));
        boxOutline.setOutlineThickness(1.0f);

        boxPosition.setFillColor(sf::Color(255, 0, 0, 196));
        boxPosition.setOutlineColor(sf::Color(255, 255, 255, 196));
        boxPosition.setOutlineThickness(1.0f);
        #endif // HIKARI_DEBUG_ENTITIES
    }

    Entity::Entity(const Entity& proto)
        : GameObject(GameObject::generateObjectId())
        , room(proto.room)
        , spriteTexture(proto.spriteTexture)
        , sprite()
        , animationSet(proto.animationSet)
        , currentAnimation(proto.currentAnimation)
        , animationPlayer(new SpriteAnimator(sprite))
        , direction(proto.direction)
        , currentAnimationName(proto.currentAnimationName)
    {
        HIKARI_LOG(debug2) << "Entity copy constructor!" << std::endl;

        body = proto.body;

        body.setCollisionCallback(
            std::bind(&Entity::handleCollision, this, std::placeholders::_1, std::placeholders::_2));

        setSpriteTexture(spriteTexture);

        #ifdef HIKARI_DEBUG_ENTITIES
        boxOutline = proto.boxOutline;
        boxPosition = proto.boxPosition;
        #endif // HIKARI_DEBUG_ENTITIES
    }

    Entity::~Entity() {

    }

    std::shared_ptr<sf::Texture> Entity::getSpriteTexture() {
        return spriteTexture;
    }

    sf::Sprite& Entity::getSprite() {
        return sprite;
    }

    std::shared_ptr<AnimationSet> Entity::getAnimationSet() const {
        return animationSet;
    }

    std::shared_ptr<Animation> Entity::getCurrentAnimation() const {
        return currentAnimation;
    }

    void Entity::changeAnimation(const std::string& animationName) {
        if(!currentAnimation || currentAnimationName != animationName) {
            if(auto set = getAnimationSet()) {
                if(set->has(animationName)) {
                    setCurrentAnimation(set->get(animationName));
                    currentAnimationName = animationName;
                }
            }
        }
    }

    std::shared_ptr<Animator> Entity::getAnimationPlayer() const {
        return animationPlayer;
    }

    void Entity::setSpriteTexture(const std::shared_ptr<sf::Texture> & newTexture) {
        spriteTexture = newTexture;

        if(spriteTexture) {
            sprite.setTexture(*(getSpriteTexture().get()));
        }
    }

    void Entity::setSprite(const sf::Sprite& newSprite) {
        sprite = newSprite;
    }

    void Entity::setAnimationSet(std::shared_ptr<AnimationSet> newAnimationSet) {
        animationSet = newAnimationSet;
    }

    void Entity::setCurrentAnimation(std::shared_ptr<Animation> newAnimation) {
        currentAnimation = newAnimation;
        animationPlayer->setAnimation(getCurrentAnimation());
    }

    void Entity::setAnimationPlayer(std::shared_ptr<Animator> newAnimationPlayer) {
        animationPlayer = newAnimationPlayer;
        setCurrentAnimation(getCurrentAnimation());
    }

    const Vector2<float>& Entity::getPosition() const {
        return getBoundingBox().getPosition();
    }

    void Entity::setPosition(const Vector2<float>& newPosition) {
        body.setPosition(newPosition);
    }

    void Entity::setPosition(const float x, const float y) {
        body.setPosition(x, y);
    }

    const BoundingBoxF& Entity::getBoundingBox() const {
        return body.getBoundingBox();
    }

    void Entity::setBoundingBox(const BoundingBoxF& box) {
        body.setBoundingBox(box);
    }

    void Entity::setDirection(const Direction& dir) {
        this->direction = dir;

        // Flip sprite and sprite offset if facing left
        const sf::Vector2f& spriteScale = getSprite().getScale();

        if(getDirection() == Directions::Left) {
            getSprite().setScale(-std::abs(spriteScale.x), spriteScale.y);
        } else {
            getSprite().setScale(std::abs(spriteScale.x), spriteScale.y);
        }
    }

    void Entity::setRoom(const std::shared_ptr<Room>& newRoom) {
        room = newRoom;
    }

    const std::shared_ptr<Room>& Entity::getRoom() const {
        return room;
    }

    void Entity::setWorld(const std::weak_ptr<GameWorld>& worldRef) {
        world = worldRef;
    }

    const std::weak_ptr<GameWorld>& Entity::getWorld() const {
        return world;
    }

    const Direction Entity::getDirection() const {
        return this->direction;
    }

    void Entity::setVelocityX(const float &vx) {
        body.setVelocity(vx, getVelocityY());
    }

    const float Entity::getVelocityX() const {
        return body.getVelocity().getX();
    }

    void Entity::setVelocityY(const float &vy) {
        body.setVelocity(getVelocityX(), vy);
    }

    const float Entity::getVelocityY() const {
        return body.getVelocity().getY();
    }

    void Entity::setGravitated(const bool& affected) {
        body.setGravitated(affected);
    }

    const bool Entity::isGravitated() const {
        return body.isGravitated();
    }

    void Entity::setObstacle(const bool& isObstacle) {
        this->obstacleFlag = isObstacle;
    }

    const bool Entity::isObstacle() const {
        return obstacleFlag;
    }

    void Entity::setPhasing(const bool& phasing) {
        body.setHasWorldCollision(phasing);
    }

    const bool Entity::isPhasing() const {
        return body.doesCollideWithWorld();
    }

    void Entity::onBirth() {

    }

    void Entity::onDeath() {
        reset();
    }

    void Entity::onWake() {

    }

    void Entity::onSleep() {
        reset();
    }

    void Entity::handleCollision(Movable& body, CollisionInfo& info) {

    }

    void Entity::update(const float& dt) {
        body.update(dt);

        animationPlayer->update(dt);

        #ifdef HIKARI_DEBUG_ENTITIES
        if(debug) {
            const BoundingBoxF& bb = getBoundingBox();

            boxOutline.setPosition(std::floor(bb.getLeft() ), std::floor(bb.getTop()));
            boxOutline.setSize(sf::Vector2f(std::floor(bb.getWidth() ), std::floor(bb.getHeight())));

            boxPosition.setPosition(std::floor(getPosition().getX()), std::floor(getPosition().getY()));
            boxPosition.setSize(sf::Vector2f(1.0f, 1.0f));
        }
        #endif // HIKARI_DEBUG_ENTITIES
    }

    void Entity::render(sf::RenderTarget &target) {
        #ifdef HIKARI_DEBUG_ENTITIES
        // Draw bounding box behind sprite
        if(debug) {
            target.draw(boxOutline);
        }
        #endif // HIKARI_DEBUG_ENTITIES

        renderEntity(target);

        #ifdef HIKARI_DEBUG_ENTITIES        
        // Draw position in front of sprite
        if(debug) {
            target.draw(boxPosition);
        }
        #endif // HIKARI_DEBUG_ENTITIES
    }

    void Entity::renderEntity(sf::RenderTarget &target) {
        auto sprite = getSprite();
        auto position = getPosition();

        sprite.setPosition(
            std::floor(position.getX()), 
            std::floor(position.getY())
        );

        target.draw(sprite);
    }

    void Entity::reset() {
        animationPlayer->rewind();
    }

    namespace EntityHelpers {

        float getX(const Entity* entity) {
            return entity->getPosition().getX();
        }

        float getY(const Entity* entity) {
            return entity->getPosition().getY();
        }

        void setX(Entity * entity, const float & x) {
            entity->setPosition(x, entity->getPosition().getY());
        }

        void setY(Entity * entity, const float & y) {
            entity->setPosition(entity->getPosition().getX(), y);
        }

        bool checkIfTileAtPositionHasAttribute(Entity * entity, const int & x, const int & y, const int & attribute) {
            if(const auto & room = entity->getRoom()) {
                return TileAttribute::hasAttribute(room->getAttributeAt(x / 16, y / 16), static_cast<TileAttribute::TileAttribute>(attribute));
            }

            return false;
        }

    }

} // hikari
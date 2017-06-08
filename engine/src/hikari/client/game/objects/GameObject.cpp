#include "hikari/client/game/objects/GameObject.hpp"
#include "hikari/client/game/objects/GameObjectDefinition.hpp"
#include "hikari/client/game/objects/GameObjectUtils.hpp"
#include "hikari/core/util/Log.hpp"

namespace hikari {

    using Utils = GameObjectUtils;

    GameObject::Id::Id()
        : id{0}
    {

    }

    GameObject::Id::Id(std::uint64_t id)
        : id{id}
    {

    }

    GameObject::Id::Id(std::uint32_t index, std::uint32_t version)
        : id{toId(index, version)}
    {

    }

    std::uint64_t GameObject::Id::getId() const {
        return id;
    }

    bool GameObject::Id::operator == (const Id & other) const {
        return id == other.id;
    }

    bool GameObject::Id::operator != (const Id & other) const {
        return !(*this == other);
    }

    bool GameObject::Id::operator < (const Id & other) const {
        return id < other.id;
    }

    std::uint32_t GameObject::Id::getIndex() const {
        return id & INDEX_MASK;
    }

    std::uint32_t GameObject::Id::getVersion() const {
        return id >> VERSION_BIT_SHIFT;
    }

    std::uint64_t GameObject::Id::toId(std::uint32_t index, std::uint32_t version) {
        return static_cast<std::uint64_t>(index) |
            (static_cast<std::uint64_t>(version) << VERSION_BIT_SHIFT);
    }

    /* static */
    std::uint64_t GameObject::nextId = 1000;

    /* static */
    const GameObject::Id GameObject::generateObjectId() {
        return GameObject::Id(static_cast<std::int64_t>(nextId++));
    }

    /* static */
    const GameObject::Id GameObject::INVALID;

    GameObject::GameObject(Id id)
        : id(id)
        , parentId{INVALID}
        , activeFlag(false)
        , obstacleFlag(false)
        , shieldFlag(false)
        , ageFlag(false)
        , direction{Directions::None}
        , age{0.0f}
        , definition{nullptr}
        , eventBus{nullptr}
    {

    }

    GameObject::GameObject(const GameObject & other)
        : id{INVALID} // TODO: Need the manager to assign an ID so it can be recycled.
        , parentId{other.parentId}
        , activeFlag{other.activeFlag}
        , obstacleFlag{other.obstacleFlag}
        , shieldFlag{other.shieldFlag}
        , ageFlag{other.ageFlag}
        , direction{other.direction}
        , definition{other.definition}
        , age{0.0f}
        , eventBus{other.eventBus}
    {

    }

    GameObject::~GameObject() {

    }

    GameObject::Id GameObject::getId() const {
        return id;
    }

    GameObject::Id GameObject::getParentId() const {
        return parentId;
    }

    void GameObject::setParentId(GameObject::Id parentId) {
        this->parentId = parentId;
    }

    const GameObjectDefinition * const GameObject::getDefinition() const {
        return definition;
    }

    void GameObject::setDefinition(const GameObjectDefinition * const definition) {
        this->definition = definition;
    }

    EventBus * const GameObject::getEventBus() const {
        return eventBus;
    }

    void GameObject::setEventBus(EventBus * const eventBus) {
        this->eventBus = eventBus;
    }

    bool GameObject::isActive() const {
        return activeFlag;
    }

    void GameObject::setActive(bool activeFlag) {
        if(this->activeFlag != activeFlag) {
            this->activeFlag = activeFlag;

            if(this->activeFlag) {
                onActivated();
            } else {
                onDeactivated();
            }
        }
    }

    bool GameObject::isObstacle() const {
        return obstacleFlag;
    }

    void GameObject::setObstacleFlag(bool isObstacle) {
        this->obstacleFlag = isObstacle;
    }

    void GameObject::onActivated() {

    }

    void GameObject::onDeactivated() {

    }

    void GameObject::update(float dt) {
        if(isActive()) {
            if(Utils::canAge(*this)) {
                Utils::advanceAge(*this, dt);

                if(Utils::isTooOld(*this)) {
                    // onDeath();
                    setActive(false);
                }
            }
        }
    }

    void GameObject::reset() {

    }

} // hikari

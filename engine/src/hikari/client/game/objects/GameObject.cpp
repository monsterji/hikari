#include "hikari/client/game/objects/GameObject.hpp"
#include "hikari/client/game/objects/GameObjectDefinition.hpp"
#include "hikari/core/util/Log.hpp"

namespace hikari {

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
    int GameObject::nextId = 1000;

    /* static */
    const int  GameObject::generateObjectId() {
        return nextId++;
    }

    /* static */
    const GameObject::Id GameObject::INVALID;

    GameObject::GameObject(int id)
        : id(id)
        , active(false)
        , parentId{INVALID}
        , definition{nullptr}
    {

    }

    GameObject::~GameObject() {

    }

    int GameObject::getId() const {
        return id;
    }

    GameObject::Id GameObject::getParentId() const {
        return parentId;
    }

    void GameObject::setParentId(GameObject::Id parentId) {
        this->parentId = parentId;
    }

    const GameObjectDefinition * GameObject::getDefinition() const {
        return definition;
    }

    void GameObject::setDefinition(const GameObjectDefinition * definition) {
        this->definition = definition;
    }

    bool GameObject::isActive() const {
        return active;
    }

    void GameObject::setActive(bool active) {
        if(this->active != active) {
            this->active = active;

            if(this->active) {
                onActivated();
            } else {
                onDeactivated();
            }
        }
    }

    void GameObject::onActivated() {

    }

    void GameObject::onDeactivated() {

    }

    void GameObject::update(float dt) {

    }

    void GameObject::reset() {

    }

} // hikari

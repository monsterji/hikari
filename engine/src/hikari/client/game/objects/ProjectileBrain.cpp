#include "hikari/client/game/objects/ProjectileBrain.hpp"
#include "hikari/core/util/Log.hpp"

namespace hikari {

    ProjectileBrain::ProjectileBrain()
        :host(nullptr)
    {

    }

    ProjectileBrain::ProjectileBrain(const ProjectileBrain & proto)
        : host(nullptr)
    {

    }

    ProjectileBrain::~ProjectileBrain() {
        detach();
    }

    Projectile * const ProjectileBrain::getHost() {
        return host;
    }

    void ProjectileBrain::attach(Projectile * host) {
        this->host = host;
    }

    void ProjectileBrain::detach() {
        host = nullptr;
    }

    void ProjectileBrain::update(float dt) {
        // Does nothing
    }

    void ProjectileBrain::handleCollision(Movable& body, CollisionInfo& info) {
        // Does nothing
    }

    void ProjectileBrain::handleObjectTouch(int otherId) {
        // Does nothing
    }

    // void ProjectileBrain::applyConfig(const Sqrat::Table & instanceConfig) {
    //     // Does nothing
    // }

} // hikari
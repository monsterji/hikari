#include "hikari/client/game/objects/ProjectileBrain.hpp"
#include "hikari/client/game/objects/Motion.hpp"

#include "hikari/core/math/Vector2.hpp"
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

    std::unique_ptr<ProjectileBrain> ProjectileBrain::clone() const {
        return std::unique_ptr<ProjectileBrain>(new ProjectileBrain(*this));
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
        if(host) {
            if(auto motion = host->getMotion()) {
                Vector2<float> newVelocity = motion->calculate(
                    dt,
                    Vector2<float>(host->getVelocityX(), host->getVelocityY())
                );

                host->setVelocityY(newVelocity.getY());

                // Flip horizontal velocity depending on direction
                if(host->getDirection() == Directions::Left) {
                    host->setVelocityX(-newVelocity.getX());
                } else {
                    host->setVelocityX(newVelocity.getX());
                }
            } else {
                if(host->getDirection() == Directions::Left) {
                    host->setVelocityX(-4.0f);
                } else {
                    host->setVelocityX(4.0f);
                }
            }
        }
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
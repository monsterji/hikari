#ifndef HIKARI_CLIENT_GAME_OBJECT_PARTICLEFACTORY
#define HIKARI_CLIENT_GAME_OBJECT_PARTICLEFACTORY

#include <memory>
#include <string>
#include <unordered_map>

#include "hikari/core/util/Service.hpp"

namespace hikari {

    class GameObjectDefinition;
    class AnimationSetCache;
    class ImageCache;
    class Particle;

    class ParticleFactory : public Service {
    private:
        //
        // Fields
        //
        std::weak_ptr<AnimationSetCache> animationSetCache;
        std::weak_ptr<ImageCache> imageCache;
        std::unordered_map<std::string, std::shared_ptr<Particle>> prototypeRegistry;
        std::unordered_map<std::string, std::unique_ptr<GameObjectDefinition>> definitionRegistry;

    public:
        //
        // Constructor
        //
        ParticleFactory(const std::weak_ptr<AnimationSetCache>& animationSetCache,
            const std::weak_ptr<ImageCache>& imageCache);
        virtual ~ParticleFactory();

        //
        // Methods
        //
        std::unique_ptr<Particle> create(const std::string& enemyType);

        void registerPrototype(const std::string & prototypeName, const std::shared_ptr<Particle> & instancee);
        void registerDefinition(const std::string & name, std::unique_ptr<GameObjectDefinition> && definition);
    };

} // hikari

#endif // HIKARI_CLIENT_GAME_OBJECT_PARTICLEFACTORY

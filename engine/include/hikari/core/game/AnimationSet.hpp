#ifndef HIKARI_CORE_GAME_ANIMATIONSET
#define HIKARI_CORE_GAME_ANIMATIONSET

#include "hikari/core/Platform.hpp"
#include "hikari/core/game/Animation.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace sf {
    class Texture;
}

namespace hikari {

    typedef std::unique_ptr<Animation> AnimationPtr;

    /**
        A set of Animation objects. Associates a name with an animation object.
    */
    class HIKARI_API AnimationSet {
    private:
        std::string name;
        std::string imageFileName;
        const sf::Texture * texture;
        std::unordered_map<std::string, AnimationPtr> animationMap;
        std::unordered_map<std::string, std::string> aliases;

    public:
        AnimationSet(const std::string& name, const std::string& imageFileName, const sf::Texture * texture);

        const std::string& getName() const;
        const std::string& getImageFileName() const;
        const sf::Texture * getTexture() const;

        bool add(const std::string& name, AnimationPtr && animation);
        bool addAlias(const std::string& name, const std::string& alias);
        bool has(const std::string& name) const;
        bool remove(const std::string& name);
        bool removeAlias(const std::string& alias);
        const Animation * get(const std::string & name) const;
    };

} // hikari

#endif // HIKARI_CORE_GAME_ANIMATIONSET

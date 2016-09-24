#include "hikari/core/game/AnimationSet.hpp"

namespace hikari {

    AnimationSet::AnimationSet(const std::string& name, const std::string& imageFileName, const sf::Texture * texture)
        : name(name)
        , imageFileName(imageFileName)
        , texture(texture)
        , animationMap()
        , aliases()
    {

    }

    const std::string& AnimationSet::getName() const {
        return name;
    }

    const std::string& AnimationSet::getImageFileName() const {
        return imageFileName;
    }

    const sf::Texture * AnimationSet::getTexture() const {
        return texture;
    }

    bool AnimationSet::add(const std::string& name, AnimationPtr && animation) {
        if(has(name)) {
            return false;
        }

        animationMap.insert(
            std::make_pair(name, std::move(animation))
        );

        return true;
    }

    bool AnimationSet::addAlias(const std::string& name, const std::string& alias) {
        return aliases.insert(
            std::make_pair(alias, name)
        ).second;
    }

    bool AnimationSet::has(const std::string& name) const {
        return aliases.find(name) != aliases.end() || animationMap.find(name) != animationMap.end();
    }

    bool AnimationSet::remove(const std::string& name) {
        animationMap.erase(name);

        return true;
    }

    bool AnimationSet::removeAlias(const std::string& alias) {
        aliases.erase(alias);

        return true;
    }

    const Animation * AnimationSet::get(const std::string & name) const {
        if(has(name)) {
            const auto & alias = aliases.find(name);

            if(alias != aliases.end()) {
                return animationMap.find(alias->second)->second.get();
            }

            return animationMap.find(name)->second.get();
        }

        return nullptr;
    }

} // hikari

#ifndef HIKARI_CORE_GAME_MAP_TILESETLOADER
#define HIKARI_CORE_GAME_MAP_TILESETLOADER

#include "hikari/core/Platform.hpp"
#include <memory>
#include <json/value.h>
#include <string>

#if (_WIN32 && _MSC_VER)
    #pragma warning(push)
    #pragma warning(disable:4251)
#endif

namespace hikari {

    class AnimationLoader;
    class ImageCache;
    class Tileset;

    class HIKARI_API TilesetLoader {
    private:
        static const char* PROPERTY_NAME_SURFACE;
        static const char* PROPERTY_NAME_SIZE;
        static const char* PROPERTY_NAME_TILES;
        static const char* PROPERTY_NAME_X;
        static const char* PROPERTY_NAME_Y;
        static const char* PROPERTY_NAME_ANIMATION;
        static const char* PROPERTY_NAME_VERSION;

        std::shared_ptr<AnimationLoader> animationLoader;
        std::shared_ptr<ImageCache> imageCache;

        bool isValidTilesetJson(const Json::Value &json) const;
        bool isValidTileJson(const Json::Value &json) const;
        bool isTileAnimated(const Json::Value &json) const;

        std::unique_ptr<Tileset> constructTileset(const Json::Value &json) const;

    public:
        TilesetLoader(const std::shared_ptr<ImageCache> &imageCache,
                const std::shared_ptr<AnimationLoader> &animationLoader);
        std::unique_ptr<Tileset> loadFromJson(const Json::Value &json);
    };

} // hikari

#if (_WIN32 && _MSC_VER)
    #pragma warning(pop)
#endif

#endif // HIKARI_CORE_GAME_MAP_TILESETLOADER

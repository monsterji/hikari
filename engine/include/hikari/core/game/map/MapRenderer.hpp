#ifndef HIKARI_CORE_GAME_MAP_MAPRENDERER
#define HIKARI_CORE_GAME_MAP_MAPRENDERER

#include "hikari/core/Platform.hpp"
#include "hikari/core/geom/Rectangle2D.hpp"
#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#if (_WIN32 && _MSC_VER)
    #pragma warning(push)
    #pragma warning(disable:4251)
#endif

namespace sf {
    class RenderTarget;
    class View;
}

namespace hikari {

    class Room;
    class Tileset;

    typedef std::shared_ptr<Room> RoomPtr;

    class HIKARI_API MapRenderer {
    private:
        static bool isDebugLadderRenderingEnabled;
        static bool isDebugForceRenderingEnabled;
        static bool isDebugDoorRenderingEnabled;
        static const int TILE_OVERDRAW;
        RoomPtr room;
        const Tileset * tileData;
        sf::Sprite tileSprite;
        sf::RectangleShape backgroundShape;
        sf::RectangleShape debugLadderShape;
        sf::RectangleShape debugForceShape;
        Rectangle2D<int> visibleScreenArea;
        Rectangle2D<int> visibleTileArea;

        inline void buildBackgroundRectangle();
        inline void cullTiles();
        inline void applyTileToSprite(const int &tileIndex, const int &x, const int &y);
        inline void applyTileAttributes(const int &attributes);

    public:
        MapRenderer(const RoomPtr &room, const Tileset * tileData);

        void setRoom(const RoomPtr &room);
        RoomPtr getRoom() const;

        void setTileData(const Tileset * tileData);
        const Tileset * getTileData() const;

        void setCullRegion(const Rectangle2D<int> &cullRegion);

        void render(sf::RenderTarget &target);
        void renderBackground(sf::RenderTarget &target);
        void renderForeground(sf::RenderTarget &target);
    };

} // hikari

#if (_WIN32 && _MSC_VER)
    #pragma warning(pop)
#endif

#endif // HIKARI_CORE_GAME_MAP_MAPRENDERER

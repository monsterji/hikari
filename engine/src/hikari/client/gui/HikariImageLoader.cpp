#include "hikari/client/gui/HikariImageLoader.hpp"
#include "guichan/sfml/sfmlimage.hpp"

namespace hikari {
namespace gui {

    HikariImageLoader::HikariImageLoader(const std::weak_ptr<ImageCache> & imageCache)
        : imageCache(imageCache)
    {

    }

    HikariImageLoader::~HikariImageLoader() {

    }

    gcn::Image* HikariImageLoader::load(const std::string& filename, bool convertToDisplayFormat) {
        auto loadedImage = loadTextureFromCache(filename);
        gcn::Image * image = nullptr;

        if(loadedImage) {
            image = new gcn::SFMLImage(const_cast<ImageCache::ResourceType *>(loadedImage), false);

            if (convertToDisplayFormat) {
                image->convertToDisplayFormat();
            }
        }

        return image;
    }

    const ImageCache::ResourceType * HikariImageLoader::loadTextureFromCache(const std::string& filename) {
        const ImageCache::ResourceType * loadedImage = nullptr;

        if(auto cache = imageCache.lock()) {
            loadedImage = cache->get(filename);
        }

        return loadedImage;
    }

} // hikari::gui
} // hikari

#ifndef HIKARI_CLIENT_OBJECTREMOVEDEVENTDATA
#define HIKARI_CLIENT_OBJECTREMOVEDEVENTDATA

#include "hikari/client/game/events/BaseEventData.hpp"
#include "hikari/client/game/objects/GameObject.hpp"

namespace hikari {

    /**
     * An event to be fired when a GameObject is removed from the GameWorld.
     */
    class ObjectRemovedEventData : public BaseEventData {
    public:
        static const EventType Type;

    private:
        GameObject::Id objectId;

    public:
        explicit ObjectRemovedEventData(GameObject::Id objectId);
        virtual ~ObjectRemovedEventData();

        /**
         * Gets the ID of the object that was removed.
         * @return the ID of the removed object
         */
        GameObject::Id getObjectId() const;

        virtual const EventType & getEventType() const;

        virtual EventDataPtr copy() const;
        virtual const char * getName() const;
    };

} // hikari

#endif // HIKARI_CLIENT_OBJECTREMOVEDEVENTDATA

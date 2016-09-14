#ifndef HIKARI_CLIENT_ENTITYDAMAGEEVENTDATA
#define HIKARI_CLIENT_ENTITYDAMAGEEVENTDATA

#include "hikari/client/game/events/BaseEventData.hpp"
#include "hikari/client/game/objects/GameObject.hpp"

namespace hikari {

    class EntityDamageEventData : public BaseEventData {
    public:
        static const EventType Type;

    private:
        GameObject::Id entityId;
        float amount;

    public:
        EntityDamageEventData(GameObject::Id entityId, float amount);
        virtual ~EntityDamageEventData();

        GameObject::Id getEntityId() const;
        float getAmount() const;

        virtual const EventType & getEventType() const;

        virtual EventDataPtr copy() const;
        virtual const char * getName() const;
    };

} // hikari

#endif // HIKARI_CLIENT_ENTITYDAMAGEEVENTDATA

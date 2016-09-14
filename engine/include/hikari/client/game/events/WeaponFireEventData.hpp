#ifndef HIKARI_CLIENT_WEAPONFIREEVENTDATA
#define HIKARI_CLIENT_WEAPONFIREEVENTDATA

#include "hikari/client/game/events/BaseEventData.hpp"
#include "hikari/client/game/objects/GameObject.hpp"
#include "hikari/client/game/objects/Faction.hpp"
#include "hikari/core/game/Direction.hpp"
#include "hikari/core/math/Vector2.hpp"

namespace hikari {

    class Entity;

    class WeaponFireEventData : public BaseEventData {
    public:
        static const EventType Type;

    private:
        int weaponId;  // id of the weapon to be fired
        GameObject::Id shooterId; // id of the entity that shot this weapon
        Faction faction;
        Direction direction; //weaponId, ownerId, faction, position, direction
        Vector2<float> position; // position where this weapon was fired
    public:
        WeaponFireEventData(int weaponId, GameObject::Id shooterId, Faction faction, Direction direction, const Vector2<float>& position);
        virtual ~WeaponFireEventData();

        int getWeaponId() const;
        GameObject::Id getShooterId() const;
        Faction getFaction() const;
        Direction getDirection() const;
        const Vector2<float>& getPosition() const;

        virtual const EventType & getEventType() const;

        virtual EventDataPtr copy() const;
        virtual const char * getName() const;
    };

} // hikari

#endif // HIKARI_CLIENT_WEAPONFIREEVENTDATA

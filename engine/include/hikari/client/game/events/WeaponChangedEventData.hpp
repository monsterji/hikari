#ifndef HIKARI_CLIENT_WEAPONCHANGEDEVENTDATA
#define HIKARI_CLIENT_WEAPONCHANGEDEVENTDATA

#include "hikari/client/game/events/BaseEventData.hpp"
#include "hikari/client/game/objects/Faction.hpp"
#include "hikari/core/game/Direction.hpp"
#include "hikari/core/math/Vector2.hpp"

namespace hikari {

    class Entity;

    class WeaponChangedEventData : public BaseEventData {
    public:
        static const EventType Type;

    private:
        int weaponId;  // id of the weapon to be fired
        int shooterId; // id of the entity that shot this weapon
        Faction faction;
    public:
        WeaponChangedEventData(int weaponId, int shooterId, Faction faction);
        virtual ~WeaponChangedEventData();

        int getWeaponId() const;
        int getShooterId() const;
        Faction getFaction() const;

        virtual const EventType & getEventType() const;

        virtual EventDataPtr copy() const;
        virtual const char * getName() const;
    };

} // hikari

#endif // HIKARI_CLIENT_WEAPONCHANGEDEVENTDATA
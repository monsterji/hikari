#include "hikari/client/game/events/WeaponChangedEventData.hpp"
#include "hikari/core/util/HashedString.hpp"

namespace hikari {

    const EventType WeaponChangedEventData::Type = HashedString("WeaponChangedEventData").getHash();

    WeaponChangedEventData::WeaponChangedEventData(int weaponId, int shooterId, Faction faction)
        : BaseEventData(0.0f)
        , weaponId(weaponId)
        , shooterId(shooterId)
        , faction(faction)
    {

    }

    int WeaponChangedEventData::getWeaponId() const {
        return weaponId;
    }

    int WeaponChangedEventData::getShooterId() const {
        return shooterId;
    }

    Faction WeaponChangedEventData::getFaction() const {
        return faction;
    }

    WeaponChangedEventData::~WeaponChangedEventData() {
        // Do nothing!
    }

    const EventType & WeaponChangedEventData::getEventType() const {
        return WeaponChangedEventData::Type;
    }

    EventDataPtr WeaponChangedEventData::copy() const {
        return EventDataPtr(
            new WeaponChangedEventData(
                getWeaponId(),
                getShooterId(),
                getFaction()
            )
        );
    }

    const char * WeaponChangedEventData::getName() const {
        return "WeaponChangedEventData";
    }

} // hikari
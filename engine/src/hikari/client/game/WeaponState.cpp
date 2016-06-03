#include "hikari/client/game/WeaponState.hpp"
#include "hikari/client/game/Weapon.hpp"
#include "hikari/client/game/objects/Entity.hpp"

#include "hikari/core/util/Log.hpp"

namespace hikari {

    WeaponState::WeaponState(Weapon & weapon)
        : weapon(weapon)
    {
        HIKARI_LOG(debug4) << "WeaponState::WeaponState(" << weapon.getName() << ")";
    }

    WeaponState::~WeaponState() {
        HIKARI_LOG(debug4) << "~WeaponState::WeaponState(" << weapon.getName() << ")";
    }

    void WeaponState::attach(Entity * host) {

    }

    void WeaponState::detach() {

    }

    void WeaponState::fire() {

    }

} // hikari

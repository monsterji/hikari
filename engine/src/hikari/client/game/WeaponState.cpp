#include "hikari/client/game/WeaponState.hpp"

#include "hikari/core/util/Log.hpp"

#include <string>

namespace hikari {

    WeaponState::WeaponState(const std::string & id) : id(id) {
        HIKARI_LOG(debug4) << "WeaponState::WeaponState(" << id << ")";
    }

    WeaponState::~WeaponState() {
        HIKARI_LOG(debug4) << "~WeaponState::WeaponState(" << id << ")";
    }

} // hikari

#ifndef HIKARI_CLIENT_GAME_WEAPONSTATE
#define HIKARI_CLIENT_GAME_WEAPONSTATE

#include <string>

namespace hikari {

  class WeaponState {
  private:
    std::string id;

  public:
    WeaponState(const std::string & id);
    ~WeaponState();
  };

} // hikari

#endif // HIKARI_CLIENT_GAME_WEAPONSTATE

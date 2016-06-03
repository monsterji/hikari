#ifndef HIKARI_CLIENT_GAME_WEAPONSTATE
#define HIKARI_CLIENT_GAME_WEAPONSTATE

namespace hikari {

  class Weapon;

  class WeaponState {
  private:
      Weapon & weapon;

  public:
      WeaponState(Weapon & weapon);
      ~WeaponState();
  };

} // hikari

#endif // HIKARI_CLIENT_GAME_WEAPONSTATE

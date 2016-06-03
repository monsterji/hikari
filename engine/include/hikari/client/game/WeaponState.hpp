#ifndef HIKARI_CLIENT_GAME_WEAPONSTATE
#define HIKARI_CLIENT_GAME_WEAPONSTATE

namespace hikari {

  class Entity;
  class Weapon;

  class WeaponState {
  protected:
      Weapon & weapon;

  public:
      WeaponState(Weapon & weapon);
      virtual ~WeaponState();

      virtual void attach(Entity * host);
      virtual void detach();
      virtual void fire();
  };

} // hikari

#endif // HIKARI_CLIENT_GAME_WEAPONSTATE

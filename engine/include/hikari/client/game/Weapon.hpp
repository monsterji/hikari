#ifndef HIKARI_CLIENT_GAME_WEAPON
#define HIKARI_CLIENT_GAME_WEAPON

#include <memory>
#include <string>
#include <vector>

namespace hikari {

  class GameWorld;
  class WeaponAction;
  class WeaponFireEventData;
  class WeaponState;
  class Shot;
  class SquirrelService;

  /**
   * A Weapon describes the properties of a "usable" weapon. Weapons are
   * stateless -- they can only be used to fire a weapon. Objects which
   * use weapons must track their effects themself.
   */
  class Weapon {
  private:
    const static int DEFAULT_PALETTE_ID;

    float usageCost;            /// How much ammunition one "usage" of this weapon is required for it to fire
    unsigned int limit;         /// How many times the weapon can be fired before it requires cooldown
    int damageId;
    int paletteId;              /// Which palette should Rockman have if he's using this weapon?
    std::string name;           /// The unique name of this weapon.
    std::string label;          /// The unique label of this weapon.
    std::string projectileType; /// The identifier of a particular projectile.
    std::string usageSound;     /// The name of the sample to play when the weapon is used.
    std::vector<std::shared_ptr<WeaponAction>> actions;

  protected:
    void setName(const std::string & name);
    void setProjectileType(const std::string & type);

  public:
    static const float DEFAULT_USAGE_COST;
    static const char * DEFAULT_PROJECTILE_TYPE;
    static const char * DEFAULT_USAGE_SOUND;

    Weapon(const std::string & name, unsigned int limit, int damageId, int paletteId = DEFAULT_PALETTE_ID, float usageCost = DEFAULT_USAGE_COST);

    virtual ~Weapon();

    float getUsageCost() const;
    unsigned int getLimit() const;
    int getDamageId() const;
    int getPaletteId() const;
    const std::string & getName() const;
    const std::string & getLabel() const;
    const std::string & getProjectileType() const;
    const std::string & getUsageSound() const;

    void setLabel(const std::string & label);
    void setSound(const std::string & sound);
    void setActions(const std::vector<std::shared_ptr<WeaponAction>> & actions);
    virtual Shot fire(GameWorld & world, WeaponFireEventData & eventData) const;

    std::unique_ptr<WeaponState> createState(SquirrelService & squirrel);
  };

} // hikari

#endif // HIKARI_CLIENT_GAME_WEAPON

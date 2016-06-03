#ifndef HIKARI_CLIENT_GAME_SCRIPTEDWEAPONSTATE
#define HIKARI_CLIENT_GAME_SCRIPTEDWEAPONSTATE

#include "hikari/client/game/WeaponState.hpp"
#include <squirrel.h>
#include <sqrat.h>

namespace hikari {

    class Entity;
    class SquirrelService;

    /**
     * Script-powered WeaponState. Allows an weapon to be controlled by a script.
     */
    class ScriptedWeaponState : public WeaponState {
    private:
        static const char * FUNCTION_NAME_ATTACH;
        static const char * FUNCTION_NAME_DETACH;
        static const char * FUNCTION_NAME_FIRE;
        static const char * BASE_CLASS_NAME;

        /** A handle to the Squirrel VM */
        HSQUIRRELVM vm;

        /** The name of the class in the scripting enviornment to bind to */
        std::string scriptClassName;

        /** A handle to the instance object we create in the VM */
        Sqrat::Object instance;

        /** A table used to pass class-level configuration to the behavior */
        Sqrat::Table classConfig;

        Sqrat::Function proxyAttach;
        Sqrat::Function proxyDetach;
        Sqrat::Function proxyFire;

        /**
         * Creates an instance of the behavior in the VM and binds it to this
         * object.
         *
         * @return true if binding was successful, false if anything went wrong
         */
        bool bindScriptClassInstance();
    public:
        /**
         * Constructor. Expects the SquirrelService and the class name to create
         * an instance of. Optionally accepts a table containing values for any
         * instance-level configuration.
         */
        ScriptedWeaponState(Weapon & weapon, SquirrelService& service, const std::string& scriptClassName, const Sqrat::Table& classConfig = Sqrat::Table());

        /**
         * Copy constructor. Causes a new instance of the scripted class to be
         * instantiated, and bind to that instance.
         */
        ScriptedWeaponState(const ScriptedWeaponState & proto);

        /**
         * Destructor.
         */
        virtual ~ScriptedWeaponState();

        virtual void attach(Entity * host);
        virtual void detach();
        virtual void fire();
    };

} // hikari

#endif // HIKARI_CLIENT_GAME_SCRIPTEDWEAPONSTATE
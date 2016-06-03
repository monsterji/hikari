#include "hikari/client/game/ScriptedWeaponState.hpp"
#include "hikari/client/game/objects/Entity.hpp"
#include "hikari/client/scripting/SquirrelService.hpp"

#include "hikari/core/util/Log.hpp"

#include <algorithm>

namespace hikari {

    const char * ScriptedWeaponState::FUNCTION_NAME_ATTACH = "attachHost";
    const char * ScriptedWeaponState::FUNCTION_NAME_DETACH = "detachHost";
    const char * ScriptedWeaponState::FUNCTION_NAME_FIRE = "fire";
    const char * ScriptedWeaponState::BASE_CLASS_NAME = "WeaponStateBase";

    ScriptedWeaponState::ScriptedWeaponState(Weapon & weapon, SquirrelService& squirrel, const std::string& scriptClassName, const Sqrat::Table& classConfig)
        : WeaponState(weapon)
        , vm(squirrel.getVmInstance())
        , scriptClassName(scriptClassName)
        , instance()
        , classConfig(classConfig)
    {
        if(this->classConfig.IsNull()) {
            this->classConfig = Sqrat::Table(vm);
        }

        if(!bindScriptClassInstance()) {
            // throw?
            HIKARI_LOG(error) << "ScriptedWeaponState failed to bind.";
        }
    }

    ScriptedWeaponState::ScriptedWeaponState(const ScriptedWeaponState & proto)
        : WeaponState(proto.weapon)
        , vm(proto.vm)
        , scriptClassName(proto.scriptClassName)
        , instance()
        , classConfig(proto.classConfig)
    {
        if(classConfig.IsNull()) {
            classConfig = Sqrat::Table(vm);
        }

        if(!bindScriptClassInstance()) {
            // throw?
            HIKARI_LOG(error) << "ScriptedWeaponState failed to bind.";
        }
    }

    ScriptedWeaponState::~ScriptedWeaponState() {
        HIKARI_LOG(debug2) << "~ScriptedWeaponState()";
    }

    bool ScriptedWeaponState::bindScriptClassInstance() {
        bool isValid = true;

        if(scriptClassName.empty()) {
            isValid = false;
        } else {
            try {
                Sqrat::Object classObject = Sqrat::RootTable(vm).GetSlot(scriptClassName.c_str());

                if(!classObject.IsNull()) {
                    Sqrat::Object& configRef = classConfig;

                    // Create an instance of the class, and run its constructor
                    Sqrat::PushVar(vm, classObject);
                    sq_createinstance(vm, -1);
                    instance = Sqrat::Var<Sqrat::Object>(vm, -1).value;

                    if(Sqrat::Error::Instance().Occurred(vm)) {
                        HIKARI_LOG(error) << "Error creating instance for '" << scriptClassName << "'. " << Sqrat::Error::Instance().Message(vm);
                    }

                    Sqrat::Function(instance, "constructor").Execute(configRef);
                    sq_pop(vm, 2);

                    if(Sqrat::Error::Instance().Occurred(vm)) {
                        HIKARI_LOG(error) << "Error executing constructor for '" << scriptClassName << "'. " << Sqrat::Error::Instance().Message(vm);
                    }

                    if(!instance.IsNull()) {
                        proxyAttach = Sqrat::Function(instance, FUNCTION_NAME_ATTACH);
                        proxyDetach = Sqrat::Function(instance, FUNCTION_NAME_DETACH);
                        proxyFire = Sqrat::Function(instance, FUNCTION_NAME_FIRE);
                    } else {
                        HIKARI_LOG(error) << "Constructor for '" << scriptClassName << "' did not return the correct object type.";
                    }
                } else {
                    HIKARI_LOG(debug2) << "Could not find a constructor for '" << scriptClassName << "'.";
                }
            } catch(...) {
                HIKARI_LOG(error) << "Could not create an instance of '" << scriptClassName << "'.";
            }
        }

        return isValid;
    }

    void ScriptedWeaponState::attach(Entity * host) {
        WeaponState::attach(host);

        if(!proxyAttach.IsNull()) {
            proxyAttach.Execute(host);

            if(Sqrat::Error::Instance().Occurred(vm)) {
                HIKARI_LOG(debug2) << "Error attaching to host object: " << Sqrat::Error::Instance().Message(vm);
            }
        }
    }

    void ScriptedWeaponState::detach() {
        if(!proxyDetach.IsNull()) {
            proxyDetach.Execute();

            if(Sqrat::Error::Instance().Occurred(vm)) {
                HIKARI_LOG(debug2) << "Error detaching from host object: " << Sqrat::Error::Instance().Message(vm);
            }
        }
    }

    void ScriptedWeaponState::fire() {
        if(!proxyFire.IsNull()) {
            proxyFire.Execute();
        }
    }

} // hikari

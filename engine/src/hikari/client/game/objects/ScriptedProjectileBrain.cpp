#include "hikari/client/game/objects/ScriptedProjectileBrain.hpp"
#include "hikari/client/scripting/SquirrelService.hpp"

#include "hikari/core/util/Log.hpp"

#include <algorithm>

namespace hikari {

    const char * ScriptedProjectileBrain::FUNCTION_NAME_ATTACH = "attachHost";
    const char * ScriptedProjectileBrain::FUNCTION_NAME_DETACH = "detachHost";
    const char * ScriptedProjectileBrain::FUNCTION_NAME_APPLYCONFIG = "applyConfig";
    const char * ScriptedProjectileBrain::FUNCTION_NAME_HANDLECOLLISION = "handleWorldCollision";
    const char * ScriptedProjectileBrain::FUNCTION_NAME_HANDLEOBJECTTOUCH = "handleObjectTouch";
    const char * ScriptedProjectileBrain::FUNCTION_NAME_UPDATE = "update";
    const char * ScriptedProjectileBrain::BASE_CLASS_NAME = "ProjectileBehavior";

    ScriptedProjectileBrain::ScriptedProjectileBrain(SquirrelService& squirrel, const std::string& scriptClassName, const Sqrat::Table& classConfig)
        : vm(squirrel.getVmInstance())
        , scriptClassName(scriptClassName)
        , instance()
        , classConfig(classConfig)
    {
        if(this->classConfig.IsNull()) {
            this->classConfig = Sqrat::Table(vm);
        }

        if(!bindScriptClassInstance()) {
            // throw?
            HIKARI_LOG(error) << "ScriptedProjectileBrain failed to bind.";
        }
    }

    ScriptedProjectileBrain::ScriptedProjectileBrain(const ScriptedProjectileBrain & proto)
        : vm(proto.vm)
        , scriptClassName(proto.scriptClassName)
        , instance()
        , classConfig(proto.classConfig)
    {
        if(classConfig.IsNull()) {
            classConfig = Sqrat::Table(vm);
        }

        if(!bindScriptClassInstance()) {
            // throw?
            HIKARI_LOG(error) << "ScriptedProjectileBrain failed to bind.";
        }
    }

    ScriptedProjectileBrain::~ScriptedProjectileBrain() {

    }

    bool ScriptedProjectileBrain::bindScriptClassInstance() {
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
                        proxyUpdate = Sqrat::Function(instance, FUNCTION_NAME_UPDATE);
                        proxyApplyConfig = Sqrat::Function(instance, FUNCTION_NAME_APPLYCONFIG);
                        proxyHandleWorldCollision = Sqrat::Function(instance, FUNCTION_NAME_HANDLECOLLISION);
                        proxyHandleObjectTouch = Sqrat::Function(instance, FUNCTION_NAME_HANDLEOBJECTTOUCH);
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

    std::unique_ptr<ProjectileBrain> ScriptedProjectileBrain::clone() const {
        return std::unique_ptr<ProjectileBrain>(new ScriptedProjectileBrain(*this));
    }

    void ScriptedProjectileBrain::attach(Projectile * host) {
        ProjectileBrain::attach(host);

        Sqrat::Table instanceConfig(vm);

        if(!proxyAttach.IsNull()) {
            proxyAttach.Execute(host, instanceConfig);

            if(Sqrat::Error::Instance().Occurred(vm)) {
                HIKARI_LOG(debug2) << "Error attaching to host object: " << Sqrat::Error::Instance().Message(vm);
            }
        }
    }

    void ScriptedProjectileBrain::detach() {
        if(!proxyDetach.IsNull()) {
            proxyDetach.Execute();

            if(Sqrat::Error::Instance().Occurred(vm)) {
                HIKARI_LOG(debug2) << "Error detaching from host object: " << Sqrat::Error::Instance().Message(vm);
            }
        }
    }

    void ScriptedProjectileBrain::handleCollision(Movable& body, CollisionInfo& info) {
        if(info.isCollisionX) {
            proxyHandleWorldCollision.Execute(info.directionX);
        } else if(info.isCollisionY) {
            proxyHandleWorldCollision.Execute(info.directionY);
        }
    }

    void ScriptedProjectileBrain::handleObjectTouch(int otherId) {
        if(!proxyHandleObjectTouch.IsNull()) {
            proxyHandleObjectTouch.Execute(otherId);
        }
    }

    void ScriptedProjectileBrain::update(float dt) {
        if(!proxyUpdate.IsNull()) {
            proxyUpdate.Execute(dt);
        }
        ProjectileBrain::update(dt);
    }

    void ScriptedProjectileBrain::applyConfig(const Sqrat::Table & classConfig) {
        if(!proxyApplyConfig.IsNull()) {
            proxyApplyConfig.Execute(classConfig);
        }
    }

} // hikari

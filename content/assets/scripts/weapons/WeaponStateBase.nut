/**
 * Base class for all weapon states.
 */
class WeaponStateBase {
    host = null;

    constructor(config = {}) {
        host = null;
        ::log("WeaponStateBase constructor called.");
    }

    function attachHost(newHost) {
        host = newHost;
    }

    function detachHost() {
        host = null;
    }

    function fire() {
        ::log("WeaponStateBase::fire() id=" + host.getId());
    }
}

::log("WeaponStateBase.nut executed!");
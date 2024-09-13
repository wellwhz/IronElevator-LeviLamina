#include "IronElevator.h"

#include <memory>

#include "ll/api/mod/RegisterHelper.h"

namespace iron_elevator {

static std::unique_ptr<IronElevator> instance;

IronElevator& IronElevator::getInstance() { return *instance; }

bool IronElevator::load() {
    getSelf().getLogger().debug("Loading...");
    // Code for loading the mod goes here.
    return true;
}

bool IronElevator::enable() {
    getSelf().getLogger().debug("Enabling...");
    // Code for enabling the mod goes here.
    return true;
}

bool IronElevator::disable() {
    getSelf().getLogger().debug("Disabling...");
    // Code for disabling the mod goes here.
    return true;
}

} // namespace iron_elevator

LL_REGISTER_MOD(iron_elevator::IronElevator, iron_elevator::instance);

#pragma once

#include "ll/api/event/ListenerBase.h"
#include "ll/api/mod/NativeMod.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/Config.h"

#include <Config.h>
#include <mc/world/level/block/Block.h>

namespace iron_elevator {

Config config;

class IronElevator {

public:
    static IronElevator& getInstance();

    explicit IronElevator(ll::mod::NativeMod& self) : mSelf(self) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    /// @return True if the mod is loaded successfully.
    [[nodiscard]] bool load() const;

    /// @return True if the mod is enabled successfully.
    bool enable();

    /// @return True if the mod is disabled successfully.
    bool disable();

private:
    ll::mod::NativeMod& mSelf;

    ll::event::ListenerPtr mPlayerJumpEventListener;
    ll::event::ListenerPtr mPlayerSneakEventListener;
};

} // namespace iron_elevator

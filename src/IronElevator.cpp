#include "IronElevator.h"

#include <memory>

#include "ll/api/event/player/PlayerJumpEvent.h"
#include "ll/api/event/player/PlayerSneakEvent.h"
#include "ll/api/mod/RegisterHelper.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"
#include "mc/world/level/block/Block.h"
#include "mc/world/level/dimension/Dimension.h"

namespace iron_elevator {

static std::unique_ptr<IronElevator> instance;

IronElevator& IronElevator::getInstance() { return *instance; }

bool IronElevator::load() const {
    // 读取配置文件
    const auto& configFilePath = getSelf().getConfigDir() / "config.json";
    if (!ll::config::loadConfig(config, configFilePath)) {
        getSelf().getLogger().warn("Cannot load configurations from {}", configFilePath);
        getSelf().getLogger().info("Saving default configurations");

        if (!ll::config::saveConfig(config, configFilePath)) {
            getSelf().getLogger().error("Cannot save default configurations to {}", configFilePath);
        }
    }

    return true;
}

bool IronElevator::enable() {
    auto& eventBus = ll::event::EventBus::getInstance();

    // 注册跳跃事件
    mPlayerJumpEventListener = eventBus.emplaceListener<ll::event::player::PlayerJumpEvent>([this](auto& event) {
        auto&    player      = event.self();
        auto&    blockSource = player.getDimension().getBlockSourceFromMainChunkSource();
        BlockPos blockPos    = player.getFeetBlockPos().add({0, -1});
        auto&    block       = blockSource.getBlock(blockPos);

        if (block.getTypeName() == config.ElevatorBlock) {
            for (int i = config.minElevatorDistance; i <= config.maxElevatorDistance; i++) {
                if (blockSource.getBlock(blockPos.add({0, i})).getTypeName() == config.ElevatorBlock) {
                    if (!config.checkTeleportPointSafety
                        || !(
                            blockSource.getBlock(blockPos.add({0, i + 1})).isSolid()
                            || blockSource.getBlock(blockPos.add({0, i + 2})).isSolid()
                        )) {
                        player.teleport(player.getFeetPos().add(Vec3(0, i, 0)), player.getDimension().getDimensionId());
                        return;
                    }
                }
            }
        }
    });

    // 注册潜行事件
    mPlayerSneakEventListener = eventBus.emplaceListener<ll::event::player::PlayerSneakingEvent>([this](auto& event) {
        auto&    player      = event.self();
        auto&    blockSource = player.getDimension().getBlockSourceFromMainChunkSource();
        BlockPos blockPos    = player.getFeetBlockPos().add({0, -1});
        auto&    block       = blockSource.getBlock(blockPos);

        if (block.getTypeName() == config.ElevatorBlock) {
            for (int i = config.minElevatorDistance; i <= config.maxElevatorDistance; i++) {
                if (blockSource.getBlock(blockPos.add({0, -i})).getTypeName() == config.ElevatorBlock) {
                    if (!config.checkTeleportPointSafety
                        || !(
                            blockSource.getBlock(blockPos.add({0, i + 1})).isSolid()
                            || blockSource.getBlock(blockPos.add({0, i + 2})).isSolid()
                        )) {
                        player.teleport(
                            player.getFeetPos().add(Vec3(0, -i, 0)),
                            player.getDimension().getDimensionId()
                        );
                        return;
                    }
                }
            }
        }
    });

    return true;
}

bool IronElevator::disable() {
    auto& eventBus = ll::event::EventBus::getInstance();
    eventBus.removeListener(mPlayerJumpEventListener);

    return true;
}

} // namespace iron_elevator

LL_REGISTER_MOD(iron_elevator::IronElevator, iron_elevator::instance);

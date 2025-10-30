#include "modules.hpp"
#include <imgui.h>

void modules::multihand::run(::cache& cache)
{
    if (!cache.player) return;

    if (cache.player.isUsingItem() && cache.options.attackKey.get().isPressed()) {
        float attackCooldown = cache.player.getAttackCooldownProgress(0.0f);
        if (attackCooldown >= 1.0f) {
            auto target = cache.instance.crosshairTarget.get();
            if (target.is_instance_of<maps::EntityHitResult>()) {
                maps::EntityHitResult entityHitResult{ target };
                auto targetEntity = entityHitResult.entity.get();
                maps::PlayerEntity playerEntity = static_cast<maps::PlayerEntity>(cache.player);

                cache.instance.interactionManager.get().attackEntity(playerEntity, targetEntity);
                cache.player.swingHand(maps::Hand{}.MAIN_HAND.get());
            }
            else if (target.is_instance_of<maps::BlockHitResult>()) {
                maps::BlockHitResult blockHitResult{ target };
                auto blockPos = blockHitResult.getBlockPos();
                auto direction = blockHitResult.getSide();
                cache.instance.interactionManager.get().attackBlock(blockPos, direction);
                cache.player.swingHand(maps::Hand{}.MAIN_HAND.get());
            }
            else {
                cache.player.swingHand(maps::Hand{}.MAIN_HAND.get());
            }
        }
    }
}


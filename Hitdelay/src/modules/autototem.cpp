#include "modules.hpp"
#include <imgui.h>

bool rage = true;

void modules::autototem::run(::cache& cache)
{
    auto offHandStack = cache.player.getOffHandStack();

    if (!offHandStack.isEmpty()) {
        return;
    }

    auto playerInventory = cache.player.getInventory();
    if (playerInventory.object_instance == nullptr) {
        return;
    }

    auto inventory = static_cast<maps::Inventory>(playerInventory);
    int inventorySize = inventory.size();

    if (inventorySize == 0) {
        return;
    }

    auto totemItem = maps::Items{}.TOTEM_OF_UNDYING.get();
    int totemSlot = -1;

    for (int i = 0; i < inventorySize; ++i) {
        auto stack = inventory.getStack(i);
        auto itemInstance = stack.item.get();

        if (itemInstance.is_same_object(totemItem)) {
            totemSlot = i;
            break;
        }
    }

    if (totemSlot == -1) {
        return;
    }

    auto networkHandler = cache.instance.getNetworkHandler();

    if (rage) {
        if (totemSlot < 9) {

        }
    }

    else {
        if (totemSlot < 9) {
            auto updateSlotPacket = maps::UpdateSelectedSlotC2SPacket::new_object(
                &maps::UpdateSelectedSlotC2SPacket::constructor,
                static_cast<jint>(totemSlot)
            );

            networkHandler.sendPacket(static_cast<maps::Packet>(updateSlotPacket));

            auto swapOffhandPacket = maps::PlayerActionC2SPacket::new_object(
                &maps::PlayerActionC2SPacket::constructor,
                maps::PlayerActionC2SPacket$Action{}.SWAP_ITEM_WITH_OFFHAND.get(),
                maps::BlockPos{}.ORIGIN.get(),
                maps::Direction{}.DOWN.get()
            );

            networkHandler.sendPacket(static_cast<maps::Packet>(swapOffhandPacket));

            auto pickPacket = maps::PickFromInventoryC2SPacket::new_object(
                &maps::PickFromInventoryC2SPacket::constructor,
                static_cast<jint>(playerInventory.selectedSlot.get())
            );

            networkHandler.sendPacket(static_cast<maps::Packet>(pickPacket));
        }
        else {
            auto swapOffhandPacket = maps::PlayerActionC2SPacket::new_object(
                &maps::PlayerActionC2SPacket::constructor,
                maps::PlayerActionC2SPacket$Action{}.SWAP_ITEM_WITH_OFFHAND.get(),
                maps::BlockPos{}.ORIGIN.get(),
                maps::Direction{}.DOWN.get()
            );

            networkHandler.sendPacket(static_cast<maps::Packet>(swapOffhandPacket));

            auto pickPacket = maps::PickFromInventoryC2SPacket::new_object(
                &maps::PickFromInventoryC2SPacket::constructor,
                static_cast<jint>(totemSlot)
            );

            networkHandler.sendPacket(static_cast<maps::Packet>(pickPacket));
            networkHandler.sendPacket(static_cast<maps::Packet>(swapOffhandPacket));
        }
    }
}

void modules::autototem::on_disable(::cache& cache)
{
}

/*void modules::autototem::render_options()
{
    ImGui::SliderInt("Delay", &delay, 10, 200);
}
*/

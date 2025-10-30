#include "modules.hpp"
#include <imgui.h>
#include <fstream>
#include <iostream>
#include <thread>  // for std::this_thread
#include <chrono>  // for std::chrono>

void modules::autopot::run(::cache& cache) {
    std::ofstream logFile("C:\\Users\\Diabelek\\Videos\\log.txt", std::ios::app); // Open log file in append mode
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file!" << std::endl;
        return;
    }

    logFile << "Starting autopot module..." << std::endl;

    if (!cache.player) {
        logFile << "No player found in cache." << std::endl;
        logFile.close();
        return;
    }

    auto playerInventory = cache.player.getInventory();
    if (playerInventory.object_instance == nullptr) {
        logFile << "Player inventory is null." << std::endl;
        logFile.close();
        return;
    }

    auto inventory = static_cast<maps::Inventory>(playerInventory);
    logFile << "Player inventory size: " << inventory.size() << std::endl;

    if (inventory.size() == 0) {
        logFile << "Inventory is empty." << std::endl;
        logFile.close();
        return;
    }

    auto splashPotion = maps::Items{}.SPLASH_POTION.get();
    logFile << "Splash Potion object address: " << static_cast<void*>(splashPotion.object_instance) << std::endl;

    auto HealingPotion = maps::Potions{}.HEALING.get();
    logFile << "Healing Potion object address: " << static_cast<void*>(HealingPotion.object_instance) << std::endl;

    auto InstantHealingPotion = maps::Potions{}.STRONG_HEALING.get();
    logFile << "Instant Healing Potion object address: " << static_cast<void*>(InstantHealingPotion.object_instance) << std::endl;

    // Iterate through the hotbar slots
    for (int i = 0; i < 9; i++) {
        auto itemStack = inventory.getStack(i);
        auto itemInstance = itemStack.item.get();

        logFile << "Checking item in slot " << i << std::endl;
        logFile << "Item address in slot " << i << ": " << static_cast<void*>(itemInstance.object_instance) << std::endl;

        // Check if the item is a splash potion
        if (itemInstance.is_same_object(splashPotion)) {
            logFile << "Found splash potion in slot " << i << std::endl;

            maps::PotionUtil potionUtil;

            // Extract NbtCompound from the itemStack and use it to get the potion
            auto nbtCompound = itemStack.getNbt();  // Assuming getNbt() gets NBT data for the item
            if (nbtCompound.object_instance != nullptr) {
                auto potion = potionUtil.getPotion(nbtCompound);  // Pass NbtCompound to getPotion()

                logFile << "Potion object address: " << static_cast<void*>(potion.object_instance) << std::endl;

                // Check if the potion is a Healing Potion (IH) or a Strong Healing Potion (IH2)
                if (potion.is_same_object(HealingPotion)) {
                    logFile << "Found Healing Potion (IH) in slot " << i << std::endl;
                    system("start cmd /k echo you have Healing Potion (IH) in your slotbar");
                }
                else if (potion.is_same_object(InstantHealingPotion)) {
                    logFile << "Found Strong Healing Potion (IH2) in slot " << i << std::endl;
                    system("start cmd /k echo you have Strong Healing Potion (IH2) in your slotbar");
                }
                else {
                    logFile << "Potion in slot " << i << " is not a healing potion (IH or IH2), skipping system command." << std::endl;
                }
            }
            else {
                logFile << "ItemStack in slot " << i << " has no NBT data." << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            logFile.close();
            return;
        }
        else {
            logFile << "Item in slot " << i << " is not a splash potion." << std::endl;
        }
    }

    logFile << "No healing potions found in the hotbar." << std::endl;
    logFile.close();
}

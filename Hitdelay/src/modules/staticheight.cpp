#include "modules.hpp"
#include <imgui/imgui.h>
#include <iostream>
#include "../manager/FriendManager.hpp"

void modules::staticheight::run(::cache& cache)
{
	if (!cache.player) return;

	for (const maps::AbstractClientPlayerEntity& playerEntity : jni::array<maps::AbstractClientPlayerEntity>(cache.players.toArray()).to_vector())
	{
		if (playerEntity.is_same_object(cache.player)) continue;
		std::string name = playerEntity.getEntityName().to_string();
		if (FriendManager::is_exist(name)) return;

		maps::Box boundingBox = playerEntity.boundingBox.get();

		if (playerEntity.isFallFlying || playerEntity.isSwimming || playerEntity.isSleeping) {
			double minX = boundingBox.minX.get();
			double maxX = boundingBox.maxX.get();

			double minY = boundingBox.minY.get();
			double maxY = boundingBox.maxY.get();

			double minZ = boundingBox.minZ.get();
			double maxZ = boundingBox.maxZ.get();

			double width = maxX - minX;
			double height = maxY - minY;

			if (std::abs(0.6 - width) < 0.001 && std::abs(1.8 - height) < 0.001) continue;

			double center_x = minX + width / 2.0;
			boundingBox.minX = center_x - 0.3;
			boundingBox.maxX = center_x + 0.3;

			double center_y = minY + height / 2.0;
			boundingBox.minY = center_y - 0.9;
			boundingBox.maxY = center_y + 0.9;

			double center_z = minZ + width / 2.0;
			boundingBox.minZ = center_z - 0.3;
			boundingBox.maxZ = center_z + 0.3;
		}
	}
}
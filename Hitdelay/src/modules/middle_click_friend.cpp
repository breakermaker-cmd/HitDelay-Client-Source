#include "../manager/FriendManager.hpp"
#include "modules.hpp"

void modules::middle_click_friend::run(::cache& cache)
{
	maps::HitResult result = cache.instance.crosshairTarget.get();
	maps::HitResult$Type type = result.getType();
	maps::HitResult$Type ENTITY = maps::HitResult$Type{}.ENTITY.get();

	if (!type || !type.is_same_object(ENTITY))
		return;
	maps::Entity entity = maps::EntityHitResult(result).entity.get();

	std::string name = entity.getEntityName().to_string();
	

	if ((GetAsyncKeyState(VK_MBUTTON) & 0x8000)) {
		if (FriendManager::is_exist(name)) {
			FriendManager::remove_friend(name);
			Sleep(500);
		}
		else {
			FriendManager::add_friend(name);
			Sleep(500);
		}
	}


}

#include "modules.hpp"

void modules::sprint_reset::run(::cache& cache)
{
	static bool punch_reset = false;
	maps::HitResult result = cache.instance.crosshairTarget.get();
	maps::HitResult$Type type = result.getType();
	maps::HitResult$Type ENTITY = maps::HitResult$Type{}.ENTITY.get();

	if (!type || !type.is_same_object(ENTITY))
		return;
	maps::Entity entity = maps::EntityHitResult(result).entity.get();
	if (GetAsyncKeyState(VK_LBUTTON)) {

		if (cache.player.isSprinting() == JNI_TRUE)
			cache.player.setSprinting(JNI_FALSE);
		cache.player.setSprinting(JNI_TRUE);
		//Sleep(100);
	}
}

#include "modules.hpp"
#include <imgui.h>

void modules::jump_reset::run(::cache& cache)
{
	static bool ht_dt = false;
	int hurtTime = cache.player.hurtTime.get();

	float tickDelta = cache.instance.renderTickCounter.get().tickDelta.get();
	if (tickDelta > 1.0f) return;

	maths::vector3d current_player_position = cache.player.get_position();
	maths::vector3d prev_player_position = cache.player.get_prev_position();
	maths::vector3d player_position = prev_player_position + (current_player_position - prev_player_position) * tickDelta;

	maths::angles current_player_angles = cache.player.get_angles();
	maths::angles prev_player_angles = cache.player.get_prev_angles();
	maths::angles player_angles = prev_player_angles + (current_player_angles - prev_player_angles) * tickDelta;

	maps::AbstractClientPlayerEntity selected_target{ nullptr };
	maths::angles selected_target_angles_delta{};
	maths::vector3d selected_target_position{};
	for (maps::AbstractClientPlayerEntity& playerEntity : jni::array<maps::AbstractClientPlayerEntity>(cache.players.toArray()).to_vector())
	{
		if (!playerEntity || playerEntity.is_same_object(cache.player)) continue;

		maths::vector3d current_target_position = playerEntity.get_position();
		maths::vector3d prev_target_position = playerEntity.get_prev_position();
		maths::vector3d target_position = prev_target_position + (current_target_position - prev_target_position) * tickDelta;

		maths::vector3d player_target = (target_position - player_position);
		double distance = player_target.length();
		if (distance > 5.f || distance < 0.f) continue;

		if (GetAsyncKeyState('W')) {
			if (hurtTime == 10)
				ht_dt = true;

			if (cache.player.onGround.get() == JNI_TRUE && ht_dt) {
				ht_dt = false;
				cache.player.jump();
				Sleep(this->sleep_ms);
			}
		}
	}
}

void modules::jump_reset::render_options()
{
	ImGui::SliderInt("Sleep MS", &sleep_ms, 5, 250);
}

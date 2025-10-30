#include "modules.hpp"
#include <imgui.h>

void modules::nojumpdelay::run(::cache& cache)
{
    if (!cache.player) return;

    int jumpingCooldown = cache.player.jumpingCooldown.get();

    if (jumpingCooldown > delay) {
        cache.player.jumpingCooldown.set(delay);
    }
}

void modules::nojumpdelay::render_options()
{
    ImGui::SliderInt("Delay", &delay, 0, 250);
}
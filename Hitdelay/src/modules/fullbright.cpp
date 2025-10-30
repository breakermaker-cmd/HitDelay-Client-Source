#include "modules.hpp"
#include <imgui.h>

void modules::fullbright::run(::cache& cache)
{
    if (nightvision) {
        auto NightVision = maps::StatusEffects{}.NIGHT_VISION.get();
        auto NightVisionEffect = maps::StatusEffectInstance::new_object(&maps::StatusEffectInstance::constructor, NightVision, static_cast<jint>(9999999), static_cast<jint>(0));
        cache.player.addStatusEffect(NightVisionEffect);
    }
    else if (gamma) {
        cache.options.gammaSetting = 10000.0f;
        //todo
    }
}

void modules::fullbright::on_disable(::cache& cache)
{
    if (nightvision) {
        auto NightVision = maps::StatusEffects{}.NIGHT_VISION.get();
        bool removed = cache.player.removeStatusEffect(NightVision);
    }
    else if (gamma) {
        cache.options.gammaSetting = 1.0f;
        // todo
    }
}


void modules::fullbright::render_options()
{
    ImGui::Checkbox("Gamma", &gamma);
    ImGui::Checkbox("Night Vision", &nightvision);
}
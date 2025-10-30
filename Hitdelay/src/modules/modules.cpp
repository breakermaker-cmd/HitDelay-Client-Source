#include "modules.hpp"
#include "../gui/gui.hpp"
#include <imgui/imgui.h>
#include "../utils/utils.hpp"
#include <map>

static std::map<std::string, std::vector<modules::module*>> _modules{};

void modules::init()
{
	jni::frame frame{};
	_modules =
	{
		{"Combat", {new hitbox(), new aimassist(), new autoclick(), new triggerbot(), new autopot() }},
		{"Movement", {new jump_reset(), new sprint_reset(), new auto_sprint(), new nojumpdelay()}},
		{"Player", {new middle_click_friend() }},
		{"Visuals", {new glow_esp(), new esp(), new fullbright()}},
		{"Misc", { new autototem(), new staticheight(), new multihand() }}
	};
}

void modules::shutdown(::cache& cache)
{
	jni::frame frame{};
	for (auto m : _modules)
	{

		for (modules::module* module : m.second)
		{
			if (module->enabled && cache.is_valid()) module->on_disable(cache);
			delete module;
		}
	}
}

const std::map<std::string, std::vector<modules::module*>>& modules::get_modules()
{
	return _modules;
}

const std::vector<modules::module*>& modules::get_all_modules()
{
	std::vector<modules::module*> res;
	for (auto m : _modules)
	{

		for (modules::module* module : m.second)
		{
			res.push_back(module);
		}
	}

	return res;
}

const std::vector<modules::module*>& modules::get_modules(std::string type)
{
	std::vector<modules::module*> res;
	for (auto m : _modules)
	{
		if (m.first == type) {
			for (modules::module* module : m.second)
			{
				res.push_back(module);
			}
		}
	}

	return res;
}


modules::module::module(const char* name) : 
	name(name)
{
}

void modules::module::run(::cache& cache)
{
}

void modules::module::on_enable(::cache& cache)
{
}

void modules::module::on_disable(::cache& cache)
{
}

void modules::module::render_options()
{
}

int modules::module::get_keybind()
{
	return keybind;
}

const char* modules::module::get_name()
{
	return name;
}

void modules::module::key_bind_selector()
{
	utils::null_string display = (scanning ? "scanning..." : keycode_to_string(keybind));
	if (ImGui::Button((utils::null_string("keybind: ") + display + "##" + name).data))
	{
		scanning = true;
		gui::reset_last_pressed_key();
	}

	if (scanning)
	{
		int last_pressed = gui::get_last_pressed_key();
		if (!last_pressed) return;

		if (last_pressed == VK_ESCAPE)
			last_pressed = 0;

		keybind = last_pressed;
		scanning = false;
	}
}

utils::null_string modules::module::keycode_to_string(int keycode)
{
	if (!keycode)
		return "none";

	switch (keycode)
	{
	case VK_MENU:
	case VK_LMENU:
		return "LALT";
	case VK_RMENU:
		return "RALT";
	case VK_SPACE:
		return "SPACE";
	case VK_LBUTTON:
		return "LBUTTON";
	case VK_RBUTTON:
		return "RBUTTON";
	case VK_MBUTTON:
		return "MBUTTON";
	case VK_TAB:
		return "TAB";
	}

	char character = MapVirtualKeyA(keybind, MAPVK_VK_TO_CHAR);
	if (!character)
		return "?";
		
	utils::null_string str{"a"};
	str.data[0] = character;
	return str;
}

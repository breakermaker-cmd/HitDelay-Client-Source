#pragma once
#include "../cache/cache.hpp"
#include <vector>
#include <random>
#include <map>
#include "../utils/utils.hpp"
#include "../maths/math.hpp"

namespace modules
{
	void init();
	void shutdown(::cache& cache);

	class module
	{
	public:
		module(const char* name = "no name");
		virtual ~module() = default;

		virtual void run(::cache& cache); // called periodically, if module is enabled
		virtual void render_options(); // extra imgui widgets
		virtual void on_enable(::cache& cache);
		virtual void on_disable(::cache& cache); // called on uninject if cache is valid (if in game)

		int get_keybind();
		const char* get_name();
		void key_bind_selector();

		bool display_options = false;
		bool enabled = false;
		bool prev_enabled = false; // used to detect and send on_enable / on_disable events

	protected:
		int keybind = 0;
		std::random_device rd{};
		std::mt19937_64 gen{ rd() };

	private:
		utils::null_string keycode_to_string(int keycode);

		bool scanning = false;
		const char* name = "no name";
	};

	const std::map<std::string, std::vector<modules::module*>>& get_modules();
	const std::vector<modules::module*>& get_all_modules();
	const std::vector<modules::module*>& get_modules(std::string type);

	class hitbox : public module
	{
	public:
		hitbox() : module("Hitbox") {}

		void run(::cache& cache) override;
		void render_options() override;
		void on_disable(::cache& cache) override;

	private:
		float expand_width = 0.1f;
		float expand_height = 0.1f;
		bool sword_only = false;
		bool prev_enabled2 = false;
	};

	class staticheight : public module
	{
	public:
		staticheight() : module("Static Height") {}

		void run(::cache& cache) override;

	private:
	};

	class multihand : public module
	{
	public:
		multihand() : module("MultiHand") {}

		void run(::cache& cache) override;

	private:
	};

	class autopot : public module
	{
	public:
		autopot() : module("Auto Pot") {}

		void run(::cache& cache) override;

	private:
	};

	class autoclick : public module
	{
	public:
		autoclick() : module("Autoclick") {}

		void run(::cache& cache) override;
		void render_options() override;
		void on_disable(::cache& cache) override;

	private:
		float min_cps = 7.0;
		float max_cps = 14.0;
		bool down = false;
	};

	class triggerbot : public module
	{
	public:
		triggerbot() : module("Triggerbot") {};

		void run(::cache& cache) override;
		void render_options() override;
		void on_disable(::cache& cache) override;

	private:
		bool sword_only = true;
		bool wait_critical = true;
		int prev_attack_tick = -1;
	};

	class aimassist : public module
	{
	public:
		aimassist() : module("Aimassist") {}

		void run(::cache& cache) override;
		void on_disable(::cache& cache) override;
		void render_options() override;

	private:
		float min_distance = 0.0f;
		float max_distance = 6.0f;
		float max_angle = 80.0f;
		float width = 1.0f;
		float min_width_randomness = 0.0f;
		float max_width_randomness = 0.0f;
		float min_force_yaw = 0.4f;
		float max_force_yaw = 1.0f;
		float min_force_pitch = 0.4f;
		float max_force_pitch = 1.0f;

		struct intersection
		{
			maths::vector3d point;
			bool intersects;
		};
		intersection find_intersection(maths::vector3d ray_start, maths::vector3d ray_dir, maths::vector3d box_min, maths::vector3d box_max);

		bool lock_target = true; // continue aiming the same target even if a closer target exist
		bool require_left_click = true;
		bool sword_only = true;
		maps::AbstractClientPlayerEntity locked_target{ nullptr, true };
	};

	class reach : public module
	{
	public:
	private:
	};

	class glow_esp : public module
	{
	public:
		glow_esp() : module("glow esp") {}

		void run(::cache& cache) override;
		void on_disable(::cache& cache) override;
	private:
	};

	class fullbright : public module
	{
	public:
		fullbright() : module("fullbright") {}

		void run(::cache& cache) override;
		void on_disable(::cache& cache) override;
		void render_options() override;
	private:
		bool gamma = false;
		bool nightvision = true;
	};

	class autototem : public module
	{
	public:
		autototem() : module("autototem") {}

		void run(::cache& cache) override;
		void on_disable(::cache& cache) override;
	private:
	};

	class middle_click_friend : public module
	{
	public:
		middle_click_friend() : module("middle click friend") {}

		void run(::cache& cache) override;
	private:
	};

	class jump_reset : public module
	{
	public:
		jump_reset() : module("jump reset") {}

		void run(::cache& cache) override;
		void render_options() override;
	private:
		int sleep_ms = 50;
	};

	class sprint_reset : public module
	{
	public:
		sprint_reset() : module("sprint reset") {}

		void run(::cache& cache) override;
	private:
		int ticks = 0;
	};

	class auto_sprint : public module
	{
	public:
		auto_sprint() : module("auto sprint") {}

		void run(::cache& cache) override;
	private:
	};

	class nojumpdelay : public module
	{
	public:
		nojumpdelay() : module("no jump delay") {}
		void render_options() override;

		void run(::cache& cache) override;
	private:
		int delay = 0;
	};

	class esp : public module
	{
	public:
		esp() : module("Esp 3D") {}

		struct Box
		{
			Box(vec3f mind, vec3f maxd) {
				this->min = mind;
				this->max = maxd;
			}

			vec3f min, max;
		};

		struct visual_entity
		{
			visual_entity(Box b_box, vec3f pos, std::string name, float health, int armor, bool isSneaking)
				: bb(b_box), pos(pos), name(name), health(health), armor(armor), sneaking(isSneaking) {}

			Box bb;
			vec3f pos;
			std::string name;
			float health;
			int armor;
			bool sneaking = false;
		};

		vec3d render_pos;
		vec3d player_pos;
		vec3d player_prev_pos;

		bool show_border = false; // enable border outlines for all boxes
		bool text_shadow = false; // use a text outline
		bool show_txt_bg = false; // background for text
		float text_size = 13.f;

		bool show_distance = true;
		bool show_name = true;
		bool show_health = true;
		bool show_sneaking = true;

		float line_col[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		float fill_col[4] = { 1.0f, 1.0f, 1.0f, 0.1f };

		float text_col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float text_bg_col[4] = { 0.1f, 0.1f, 0.1f, 0.45f };

		std::vector<visual_entity> boxes;

		void run(::cache& cache) override;
		void on_enable(::cache& cache) override;
		void on_disable(::cache& cache) override;
		void render_options() override;
	private:
	};
	inline bool fill_3d = false;
}
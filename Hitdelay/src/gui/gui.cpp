#include "gui.hpp"
#include <Windows.h>
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_win32.h"
#include "../modules/modules.hpp"
#include "../hook/hook.hpp"

namespace
{
	typedef BOOL(WINAPI* wglSwapBuffers_t)(HDC);

	wglSwapBuffers_t wglSwapBuffers = nullptr;
	WNDPROC original_WndProc = nullptr;

	HWND window = nullptr;
	ImGuiContext* imGuiContext = nullptr;
	HGLRC original_context = nullptr;
	HGLRC new_context = nullptr;

	volatile bool request_shutdown = false;
	hook<wglSwapBuffers_t>* opengl_hook = nullptr;

	int last_pressed_key = 0;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK detour_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool opened = false;
	if (msg == WM_KEYDOWN && wParam == VK_INSERT)
	{
		gui::draw = !gui::draw;
		opened = gui::draw;
	}

	if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN || msg == WM_MBUTTONDOWN)
		last_pressed_key = (int)wParam;

	if (gui::draw)
	{
		if (opened)
		{
			ClipCursor(NULL);
			opened = false;
		}

		LRESULT result = ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		if (result)
			return result;

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN || msg == WM_MBUTTONDOWN)
	{
		int key = (int)wParam;
		for (modules::module* module : modules::get_all_modules())
			if (module->get_keybind() && key && module->get_keybind() == key)
				module->enabled = !module->enabled;
	}

	return CallWindowProcA(original_WndProc, hWnd, msg, wParam, lParam);
}

static void uninit(HWND current_window, HDC device)
{
	SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)original_WndProc);
	original_context = wglGetCurrentContext();
	wglMakeCurrent(device, new_context); // switch to the context we created, where imgui was initiated
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext(imGuiContext);
	wglMakeCurrent(device, original_context);
	wglDeleteContext(new_context);
}

static BOOL WINAPI detour_wglSwapBuffers(hook<wglSwapBuffers_t>* hk, void* return_address, HDC device)
{
	static bool run_once = true;
	static ImFont* arial = nullptr;
	HWND current_window = WindowFromDC(device);

	if (request_shutdown)
	{
		uninit(current_window, device);
		BOOL bl = hk->get_original()(device);
		hk->request_free();
		request_shutdown = false;
		return bl;
	}

	// if already init, and window changed, cleanup and reinit
	if (!run_once && window != current_window)
	{
		uninit(current_window, device);
		run_once = true;
	}

	if (run_once)
	{
		window = current_window;
		original_context = wglGetCurrentContext();
		new_context = wglCreateContext(device);
		wglMakeCurrent(device, new_context);

		original_WndProc = (WNDPROC)SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)detour_WndProc);

		imGuiContext = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;


		io.Fonts->AddFontDefault();
		ImGui::StyleColorsDark();

		ImGui_ImplOpenGL3_Init();
		ImGui_ImplWin32_Init(window);

		arial = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 16.0f);

		run_once = false;
	}

	wglMakeCurrent(device, new_context);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (arial != nullptr)
		ImGui::PushFont(arial);
	if (gui::draw)
	{
		ImGui::SetNextWindowBgAlpha(1.f);
		ImGui::Begin("hitdelay test 4", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		{
			if (ImGui::BeginTabBar("#TABBAR")) {

				for (auto m : modules::get_modules()) {
					if (ImGui::BeginTabItem(m.first.c_str())) {
						for (modules::module* module : m.second)
						{
							ImGui::Checkbox(module->get_name(), &module->enabled);
							if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
								module->display_options = !module->display_options;
							if (module->display_options)
							{
								ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetFrameHeight());
								ImGui::BeginGroup();
								module->key_bind_selector();
								module->render_options();
								ImGui::EndGroup();
							}
						}
						ImGui::EndTabItem();
					}
				}
				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}
	if (arial != nullptr)
		ImGui::PopFont();
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	wglMakeCurrent(device, original_context);
	return hk->get_original()(device);
}

bool gui::init()
{
	HMODULE opengl = GetModuleHandleA("opengl32.dll");
	if (!opengl) return false;
	wglSwapBuffers = (wglSwapBuffers_t)GetProcAddress(opengl, "wglSwapBuffers");

	if (!wglSwapBuffers)
		return false;

	opengl_hook = hook<wglSwapBuffers_t>::create(wglSwapBuffers, detour_wglSwapBuffers);
	if (!opengl_hook->is_valid())
		return false;

	return true;
}

void gui::shutdown()
{
	request_shutdown = true;
	while (request_shutdown || !opengl_hook->freeed());
	opengl_hook->destroy();
}

int gui::get_last_pressed_key()
{
	return last_pressed_key;
}

void gui::reset_last_pressed_key()
{
	last_pressed_key = 0;
}

HWND gui::get_window()
{
	return window;
}

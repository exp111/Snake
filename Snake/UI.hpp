#pragma once

#define NOMINMAX
#include <Windows.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/dx9/imgui_impl_dx9.h"
#include "imgui/imgui_extra.h"

#include <string>
#include <chrono>

#include "Color.hpp"
#include "singleton.hpp"

#include "menu.hpp"
#include "Utils.hpp"

struct IDirect3DDevice9;

class UI
	: public Singleton<UI>
{
public:
	void Initialize();


	void RenderMainMenuBar();
	void Render();

	void Show();
	void Hide();
	void Toggle();

	bool IsVisible() { return _visible; }
	ImGuiStyle GetStyle() { return _style; }

	Color color_ui_main;
	Color color_ui_secondary;
	Color color_ui_body;
	Color color_ui_font;

	bool			  _showMenuBar;
	
private:
	void CreateStyle();

	ImGuiStyle        _style;
	bool              _visible;
	bool			  _showTestWindow;
	bool			  _unload;
};
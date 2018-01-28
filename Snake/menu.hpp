#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/dx9/imgui_impl_dx9.h"
#include "imgui/imgui_extra.h"

#include "singleton.hpp"

#include "UI.hpp"
#include "Utils.hpp"

class Menu
	: public Singleton<Menu>
{
public:
	void Initialize();

	void Render();

	void Show();
	void Hide();
	void Toggle();

	bool IsVisible() { return _visible; }

	bool              _visible;

private:
	void CreateStyle();
	ImGuiStyle _style;

	Color color_ui_main;
	Color color_ui_secondary;
	Color color_ui_body;
	Color color_ui_font;
};
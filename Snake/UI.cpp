#include "ui.hpp"

void UI::Initialize()
{
	_visible = true;
	_showMenuBar = true;
	_showTestWindow = false;
	_unload = false;

	color_ui_main = Color(255, 128, 0, 212);
	color_ui_secondary = Color(102, 0, 0, 255);
	color_ui_body = Color(26, 26, 26, 255);
	color_ui_font = Color(230, 230, 230, 255);

	Menu::Get().Initialize();

	CreateStyle();
}



void UI::RenderMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8 * 2.0f, 4 * 2.0f));

		ImGui::Selectable("Main Window", &Menu::Get()._visible, 0, ImVec2(ImGui::CalcTextSize("Main Window", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Test Window", &_showTestWindow, 0, ImVec2(ImGui::CalcTextSize("Main Window", NULL, true).x, 0.0f));
		//ImGui::SameLine();

		//Upper Right Corner
		//push it
		ImGui::SameLine(ImGui::GetWindowWidth() - 300 - ImGui::GetStyle().WindowPadding.x);
		ImGui::Selectable("Unload", &_unload, 0, ImVec2(ImGui::CalcTextSize("Unload", NULL, true).x, 0.0f));
		ImGui::SameLine();
		ImGui::TextColored(color_ui_main, Utils::GetFullTimeDayString());

		ImGui::PopStyleVar();
		ImGui::EndMainMenuBar();
	}
}

void UI::Render()
{
	CreateStyle();
	ImGui_ImplDX9_NewFrame();

	ImGui::GetStyle() = _style;
	ImGui::GetIO().MouseDrawCursor = _visible;

	//Render Windows
	if (_visible) {
		if (_showMenuBar)
			RenderMainMenuBar();

		if (_showTestWindow)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
			ImGui::ShowTestWindow(&_showTestWindow);
		}
		Menu::Get().Render();
	}

	//Windows End

	ImGui::Render();
}

void UI::Show()
{
	_visible = true;
}

void UI::Hide()
{
	_visible = false;
}

void UI::Toggle()
{
	_visible = !_visible;
}

void UI::CreateStyle()
{
	_style.Alpha = 1.f;               // Global alpha applies to everything in ImGui
	_style.WindowPadding = ImVec2(10, 10);                      // Padding within a window
	_style.WindowMinSize = ImVec2(100, 100);                    // Minimum window size
	_style.WindowRounding = 0.0f;                                // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	_style.WindowTitleAlign = ImVec2(0.5f, 0.5f);                  // Alignment for title bar text
	_style.ChildWindowRounding = 0.0f;                                // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
	_style.FramePadding = ImVec2(5, 5);                        // Padding within a framed rectangle (used by most widgets)
	_style.FrameRounding = 0.0f;                                // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
	_style.ItemSpacing = ImVec2(0, 5);                        // Horizontal and vertical spacing between widgets/lines
	_style.ItemInnerSpacing = ImVec2(4, 4);                        // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
	_style.TouchExtraPadding = ImVec2(0, 0);                        // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
	_style.IndentSpacing = 21.0f;                               // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	_style.ColumnsMinSpacing = 6.0f;                                // Minimum horizontal spacing between two columns
	_style.ScrollbarSize = 16.0f;                               // Width of the vertical scrollbar, Height of the horizontal scrollbar
	_style.ScrollbarRounding = 9.0f;                                // Radius of grab corners rounding for scrollbar
	_style.GrabMinSize = 10.0f;                               // Minimum width/height of a grab box for slider/scrollbar
	_style.GrabRounding = 0.0f;                                // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	_style.ButtonTextAlign = ImVec2(0.5f, 0.5f);                  // Alignment of button text when button is larger than text.
	_style.DisplayWindowPadding = ImVec2(22, 22);                      // Window positions are clamped to be IsVisible within the display area by at least this amount. Only covers regular windows.
	_style.DisplaySafeAreaPadding = ImVec2(4, 4);                        // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
	_style.AntiAliasedLines = true;                                // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
	_style.AntiAliasedShapes = true;                                // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
	_style.CurveTessellationTol = 1.25f;                               // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.

	_style.Colors[ImGuiCol_Text] = ImVec4(color_ui_font);
	_style.Colors[ImGuiCol_TextDisabled] = ImVec4(Color(color_ui_font.r(), color_ui_font.g(), color_ui_font.b(), 77));
	_style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(color_ui_font);
	_style.Colors[ImGuiCol_WindowBg] = ImVec4(color_ui_body);
	_style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(Color(color_ui_body.r(), color_ui_body.g(), color_ui_body.b(), 128));
	_style.Colors[ImGuiCol_PopupBg] = ImVec4(color_ui_body);
	_style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
	_style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	_style.Colors[ImGuiCol_FrameBg] = ImVec4(color_ui_body);
	_style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(Color(color_ui_font.r(), color_ui_font.g(), color_ui_font.b(), 77));
	_style.Colors[ImGuiCol_FrameBgActive] = ImVec4(color_ui_secondary);
	_style.Colors[ImGuiCol_TitleBg] = ImVec4(color_ui_body);
	_style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(color_ui_body);
	_style.Colors[ImGuiCol_TitleBgActive] = ImVec4(color_ui_body);
	_style.Colors[ImGuiCol_MenuBarBg] = ImVec4(color_ui_body);
	_style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(color_ui_body);
	_style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(Color(color_ui_font.r(), color_ui_font.g(), color_ui_font.b(), 77));
	_style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(Color(color_ui_font.r(), color_ui_font.g(), color_ui_font.b(), 128));
	_style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(Color(color_ui_font.r(), color_ui_font.g(), color_ui_font.b(), 204));
	_style.Colors[ImGuiCol_ComboBg] = ImVec4(color_ui_body);
	_style.Colors[ImGuiCol_CheckMark] = ImVec4(color_ui_main);
	_style.Colors[ImGuiCol_SliderGrab] = ImVec4(Color(color_ui_font.r(), color_ui_font.g(), color_ui_font.b(), 77));
	_style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(Color(color_ui_font.r(), color_ui_font.g(), color_ui_font.b(), 153));
	_style.Colors[ImGuiCol_Button] = ImVec4(color_ui_body);
	_style.Colors[ImGuiCol_ButtonHovered] = ImVec4(color_ui_secondary);
	_style.Colors[ImGuiCol_ButtonActive] = ImVec4(color_ui_main);
	_style.Colors[ImGuiCol_Header] = ImVec4(Color(color_ui_main.r(), color_ui_main.g(), color_ui_main.b(), (color_ui_main.a() - 25)));
	_style.Colors[ImGuiCol_HeaderHovered] = ImVec4(Color(color_ui_main.r(), color_ui_main.g(), color_ui_main.b(), (color_ui_main.a() - 75)));
	_style.Colors[ImGuiCol_HeaderActive] = ImVec4(color_ui_main);
	_style.Colors[ImGuiCol_Column] = ImVec4(color_ui_font);
	_style.Colors[ImGuiCol_ColumnHovered] = ImVec4(Color(color_ui_main.r(), color_ui_main.g(), color_ui_main.b(), (color_ui_main.a() - 75)));
	_style.Colors[ImGuiCol_ColumnActive] = ImVec4(color_ui_main);
	_style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	_style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	_style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	_style.Colors[ImGuiCol_CloseButton] = ImVec4(Color(color_ui_main.r(), color_ui_main.g(), color_ui_main.b(), (color_ui_main.a() - 75)));
	_style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(Color(color_ui_main.r(), color_ui_main.g(), color_ui_main.b(), (color_ui_main.a() - 25)));
	_style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(color_ui_main);
	_style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	_style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	_style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	_style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	_style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}
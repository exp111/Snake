#pragma once

#include "imgui.h"
#include "imgui_internal.h"

using namespace ImGui;

namespace ImGuiExtra
{
	inline bool Checkbox(const char* label, bool* v)
	{
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;
		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = ImGuiStyle::ImGuiStyle();
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = CalcTextSize(label, NULL, true);
		const ImVec2 pading = ImVec2(2, 2);
		const ImRect check_bb(window->DC.CursorPos, ImVec2(window->DC.CursorPos.x + label_size.y + style.FramePadding.x * 6, window->DC.CursorPos.y+ label_size.y + style.FramePadding.y / 2));
		ItemSize(check_bb, style.FramePadding.y);
		ImRect total_bb = check_bb;
		if (label_size.x > 0)
			SameLine(0, style.ItemInnerSpacing.x);
		const ImRect text_bb(ImVec2(window->DC.CursorPos.x, window->DC.CursorPos.y + style.FramePadding.y), ImVec2(window->DC.CursorPos.x+ label_size.x, window->DC.CursorPos.y+style.FramePadding.y+ label_size.y));
		if (label_size.x > 0)
		{
			ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
			total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
		}
		if (!ImGui::ItemAdd(total_bb, &id))
			return false;
		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
		if (pressed)
			*v = !(*v);
		const float check_sz = ImMin(check_bb.GetWidth(), check_bb.GetHeight());
		const float check_sz2 = check_sz / 2;
		const float pad = ImMax(1.0f, (float)(int)(check_sz / 4.f));
		//window->DrawList->AddRectFilled(check_bb.Min+ImVec2(pad,pad), check_bb.Max-ImVec2(pad,pad), GetColorU32(ImGuiCol_CheckMark), style.FrameRounding);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 6, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 5, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 4, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 3, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 2, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 1, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 1, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 2, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 3, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 4, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 5, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_Button]), 9);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 6, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), 9);
		if (*v)//?? ?????? ???????
		{
			//window->DrawList->AddRectFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2, check_bb.Min.y), check_bb.Max, GetColorU32(ImVec4(0.34f, 1.0f, 0.54f, 1.0f)), 0);
			//window->DrawList->AddRectFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2, check_bb.Min.y), check_bb.Max, GetColorU32(ImVec4(0.34f, 1.0f, 0.54f, 1.0f)), 0);


			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 6, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 5, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 4, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 3, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 2, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 1, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 1, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 2, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 3, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 4, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 5, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 6, check_bb.Min.y + 9), 7, GetColorU32(style.Colors[ImGuiCol_ButtonActive]), 9);
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 6, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), 9);
		}
		else
		{
			window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 6, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), 12);
		}
		if (label_size.x > 0.0f)
			RenderText(text_bb.GetTL(), label);
		return pressed;
	}
}
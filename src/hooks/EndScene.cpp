#include <pch.h>
#include <base.h>
#include "../menu.h"

HRESULT __stdcall Base::Hooks::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	Data::pDxDevice9 = pDevice;
	if (!Data::InitImGui)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImGui_ImplWin32_Init(Data::hWindow);
		ImGui_ImplDX9_Init(pDevice);
		ImGui::SetNextWindowSize(ImVec2(400, 300));
		Data::InitImGui = true;
	}

	if (!Data::InitImGui) return Data::oEndScene(pDevice); // is this reachable?

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	auto& menu = Menu::Get();
	if (Data::ShowMenu)
	{
		menu.Show();
	}

	menu.ExecuteOptions();
	
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	if(Data::ToDetach)
		Base::Detach();
	return Data::oEndScene(pDevice);
}
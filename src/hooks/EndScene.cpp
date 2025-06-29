#include <pch.h>
#include <base.h>
#include "../player.hpp"

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

	// TODO fix ugly code
	static float walkingSpeed = Default::walkingSpeed;

	if (Data::ShowMenu)
	{
		ImGui::Begin("Turtle WoW internal by Einhar");
		ImGui::Text("Detected WoW version: %s", Addr::version);
		ImGui::Checkbox("Slow fall", &Menu::isFallingSpeed);
		ImGui::Checkbox("Walk speed", &Menu::isWalkingSpeed);

		if(Menu::isWalkingSpeed)
		{
			ImGui::SliderFloat("Walk speed", &walkingSpeed, 0.f, 200.f);
		}

		ImGui::End();
	}

	walkingSpeed = Player::GetWalkingSpeed();
	Player::SetFailingSpeed(Menu::isFallingSpeed ? 3.f : Default::fallingSpeed);
	Player::SetWalkingSpeed(Menu::isWalkingSpeed ? walkingSpeed : Default::walkingSpeed);

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	if(Data::ToDetach)
		Base::Detach();
	return Data::oEndScene(pDevice);
}
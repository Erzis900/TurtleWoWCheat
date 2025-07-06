#include "pch.h"
#include "menu.h"
#include "utils.h"
#include "entityManager.h"

Menu& Menu::Get()
{
    static bool firstAccess{true};
    static Menu instance;
    
    if(firstAccess)
    {
        instance.initializePatchCheats();
        firstAccess = false;
    }
    return instance;
}

void Menu::Show()
{
    ImGui::Begin("Turtle WoW internal by Einhar");
    ImGui::Text("Detected WoW version: %s", Base::Addr::version);
    ImGui::Checkbox("Slow Fall", &isFallingSpeed);
    ImGui::Checkbox("Wall Climb", &isWallClimb);
    ImGui::Checkbox("Walk Speed", &isWalkingSpeed);

    if (isWalkingSpeed)
    {
        ImGui::SliderFloat("Walk Speed", &walkingSpeed, 0.f, 300.f);
    }

    for(auto& [name, cheatStruct]: patchCheats)
    {
        ImGui::Checkbox(name.c_str(), &cheatStruct.checkboxState);
    }

    ImGui::End();
}

void Menu::ExecuteOptions()
{
    [[maybe_unused]] auto& player = Player::Get();
    auto& entityManager = EntityManager::Get();

    entityManager.Update();

    if(isWalkingSpeed)
    {
        std::cout << "Setting walking speed to: " << walkingSpeed << std::endl;
        player.setWalkingSpeed(walkingSpeed);
    }
    player.setFallingSpeed(isFallingSpeed ? 3.f : Base::Default::fallingSpeed);
    player.setWallClimb(isWallClimb ? 0.f : Base::Default::wallClimb);

    if(isFallingSpeed)
    {
        std::cout << "Setting falling speed to: " << 3.f << std::endl;
    }

    for(auto& [_, cheatStruct]: patchCheats)
    {
        if(!cheatStruct.checkboxState && cheatStruct.patchState)
        {
            Utils::Patch(cheatStruct.address, cheatStruct.originalBytes);
            cheatStruct.patchState = false;
        }
        if(cheatStruct.checkboxState && !cheatStruct.patchState)
        {
            Utils::Patch(cheatStruct.address, cheatStruct.patchBytes);
            cheatStruct.patchState = true;
        }
    }
}


void Menu::initializePatchCheats()
{
    constexpr auto numberOfPatchCheats = 5;
    assert(patchCheats.empty());

    auto emplace = [&patchCheats=this->patchCheats](const std::string& cheatName,
            DWORD address, std::vector<BYTE> originalBytes, std::vector<BYTE> patchBytes = std::vector<BYTE>{})
    {
        const DWORD nopcode = 0x90;
        auto instance = PatchCheat{
            false, // checkbox state
            false, // patch state (was already done in memory?)
            originalBytes.size(),
            originalBytes, 
            patchBytes, // patch bytes or NOP if none
            address};
        if(instance.patchBytes.empty())
        {
            instance.patchBytes = std::vector<BYTE>(instance.patchSize, nopcode);
        }
        patchCheats.insert({cheatName, instance});
    };
    emplace("Infinite Jump", Base::Addr::infiniteJump, {0x75, 0x27});
    emplace("No Fall Damage", Base::Addr::noFallDamage, {0x8B, 0x4F, 0x78});
    emplace("Air Swim", Base::Addr::airSwim, {0x20, 0x00}, {0x00, 0x20});
    emplace("Super Fly", Base::Addr::superFly, {0x74, 0x25});
    emplace("Unlock Zoom", Base::Addr::unlockZoom, {0xF6, 0xC4, 0x41});
}
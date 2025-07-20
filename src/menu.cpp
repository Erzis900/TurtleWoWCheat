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
        instance.locationsMap = instance.locationProvider.GetLocationsMap();
        instance.initializeValueCheats();
        instance.initializePatchCheats();
        firstAccess = false;
    }
    return instance;
}

void Menu::Show()
{
    auto handleValueCheat = [](auto& cheatLabel, ValueCheat& cheatStruct)
    {
        ImGui::Checkbox(cheatLabel.c_str(), &cheatStruct.checkboxState);
        if(cheatStruct.checkboxState && cheatStruct.showSlider)
        {
            ImGui::SliderFloat(cheatLabel.c_str(), &cheatStruct.valueController, cheatStruct.minValue, cheatStruct.maxValue);
        }
    };
    ImGui::Begin("Turtle WoW internal by Einhar");
    ImGui::BeginTabBar("Tabs");

    if (ImGui::BeginTabItem("General"))
    {
        ImGui::Text("Detected WoW version: %s", Addr::version);

        for (auto& [name, cheatStruct] : patchCheats)
        {
            ImGui::Checkbox(name.c_str(), &cheatStruct.checkboxState);
        }
        for (auto& [name, cheatStruct] : valueCheats)
        {
            handleValueCheat(name, cheatStruct);
        }
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Teleport"))
    {
        for(const auto& [land, categoriesAndLocations]: locationsMap)
        {
            for(const auto& [category, locations]: categoriesAndLocations)
            {
                ImGui::Text("%s - %s", string(land).c_str(), string(category).c_str());
                for(const auto& location: locations)
                {
                    if (ImGui::Button(location.name.c_str()))
                    {
                        Player::Get().teleport(location.x, location.y, location.z);
                    }
                }
            }
        }
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("ESP"))
    {
        ImGui::Checkbox("ESP", &isESP);
        ImGui::Checkbox("Distance limit", &EntityManager::Get().GetIsDistanceLimit());
        
        if(EntityManager::Get().GetIsDistanceLimit()) 
        {
            ImGui::SliderFloat("Distance limit", &EntityManager::Get().GetMaxDistance(), 0.f, 500.f);
        }

        ImGui::ColorEdit3("Color", EntityManager::Get().getColor());

        ImGui::EndTabItem();
    }
    
    ImGui::EndTabBar();
    ImGui::End();
}

void Menu::ExecuteOptions()
{
    for(auto& [_, cheatStruct]: valueCheats)
    {
        if(!cheatStruct.checkboxState && cheatStruct.isActivated)
        {
            cheatStruct.handler(cheatStruct.defaultValueWhenOff);
            cheatStruct.isActivated = false;
        }
        else if(cheatStruct.checkboxState)
        {
            cheatStruct.handler(cheatStruct.valueController);
            cheatStruct.isActivated = true;
        }
    }

    for(auto& [_, cheatStruct]: patchCheats)
    {
        if(!cheatStruct.checkboxState && cheatStruct.isActivated)
        {
            Utils::Patch(cheatStruct.address, cheatStruct.originalBytes);
            cheatStruct.isActivated = false;
        }
        else if(cheatStruct.checkboxState && !cheatStruct.isActivated)
        {
            Utils::Patch(cheatStruct.address, cheatStruct.patchBytes);
            cheatStruct.isActivated = true;
        }
    }
}

void Menu::initializeValueCheats()
{
    assert(valueCheats.empty());

    auto emplace = 
        [&valueCheats=this->valueCheats]
        (const std::string& cheatName, bool showSlider, std::function<void(float)> handler,
            float valueWhenOn, float valueWhenOff, 
            float minValue = 0.f, float maxValue = 100.f)
    {
        auto instance = ValueCheat{
            false, // checkbox state
            false, // is executed in code?
            showSlider,
            handler,
            valueWhenOn,
            valueWhenOff,
            minValue,
            maxValue};
        valueCheats.insert({cheatName, instance});
    };
    emplace("Falling Speed", false, 
            [](float value) { Player::Get().setFallingSpeed(value); }, 
            3.f, Default::fallingSpeed);
    emplace("Walking Speed", true,
            [](float value) { Player::Get().setWalkingSpeed(value); },
            Default::walkingSpeed, Default::walkingSpeed, 0.f, 300.f);
    emplace("Jump Gravity", true,
            [](float value) { Player::Get().setJumpGravity(value); },
            Default::jumpGravity, Default::jumpGravity, -100.f, 0.f);
    emplace("Wall Climb", false,
            [](float value) { Player::Get().setWallClimb(value); },
            0.f, Default::wallClimb);
}


void Menu::initializePatchCheats()
{
    assert(patchCheats.empty());

    auto emplace = [&patchCheats=this->patchCheats](const std::string& cheatName,
            uintptr_t address, std::vector<BYTE> originalBytes, std::vector<BYTE> patchBytes = std::vector<BYTE>{})
    {
        const BYTE nopcode = 0x90;
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
    emplace("Infinite Jump", Addr::infiniteJump, {0x75, 0x27});
    emplace("No Fall Damage", Addr::noFallDamage, {0x8B, 0x4F, 0x78});
    emplace("Air Swim", Addr::airSwim, {0x20, 0x00}, {0x00, 0x20});
    emplace("Super Fly", Addr::superFly, {0x74, 0x25});
    emplace("Unlock Zoom", Addr::unlockZoom, {0xF6, 0xC4, 0x41});
    emplace("Anti Root", Addr::antiRoot, { 0x8A, 0x47 }, { 0xEB, 0xF9 });
}
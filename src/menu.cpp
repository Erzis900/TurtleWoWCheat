#include "pch.h"
#include "menu.h"
#include "utils.h"

namespace Menu
{
    bool isFallingSpeed = false;
    bool isWalkingSpeed = false;
    bool isWallClimb = false;
    bool isInfiniteJump = false;
    bool isNoFallDamage = false;

    void Display()
    {
        ImGui::Begin("Turtle WoW internal by Einhar");
        ImGui::Text("Detected WoW version: %s", Base::Addr::version);
        ImGui::Checkbox("Slow fall", &isFallingSpeed);
        ImGui::Checkbox("Walk speed", &isWalkingSpeed);

        if (isWalkingSpeed)
        {
            // TODO fix walking speed
            // slider changes it once on slider value change and the game overwrites it
            // we need to write to the address each frame to overwrite the speed value
            ImGui::SliderFloat("Walk speed", Player::walkingSpeed, 0.f, 200.f);
        }

        ImGui::Checkbox("Infinite jump", &isInfiniteJump);
        if (isInfiniteJump && !Utils::IsNOP(Base::Addr::base + 0x3C625F, 2))
        {
            Utils::NOP(Base::Addr::base + 0x3C625F, 2);
        }

        ImGui::Checkbox("No Fall Damage", &isNoFallDamage);
        if (isNoFallDamage && !Utils::IsNOP(Base::Addr::base + 0x3C63DA, 3))
        {
            Utils::NOP(Base::Addr::base + 0x3C63DA, 3);
        }

        ImGui::End();
    }

    void ExecuteOptions()
    {
        Player::SetFallingSpeed(isFallingSpeed ? 3.f : Base::Default::fallingSpeed);
        if (!isWalkingSpeed) Player::SetWalkingSpeed(Base::Default::walkingSpeed);
    }
}
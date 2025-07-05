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
    float walkingSpeed = Base::Default::walkingSpeed;

    void Show()
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
            ImGui::SliderFloat("Walk speed", &Menu::walkingSpeed, 0.f, 300.f);
        }

        ImGui::Checkbox("Infinite jump", &isInfiniteJump);
        ImGui::Checkbox("No Fall Damage", &isNoFallDamage);

        ImGui::End();
    }

    void ExecuteOptions()
    {
        [[maybe_unused]] auto& player = Player::Get();
        if(isWalkingSpeed)
        {
            std::cout << "Setting walking speed to: " << walkingSpeed << std::endl;
            player.setWalkingSpeed(walkingSpeed);
        }

        if(isFallingSpeed)
        {
            std::cout << "Setting falling speed to: " << 3.f << std::endl;
        }

        player.setFallingSpeed(isFallingSpeed ? 3.f : Base::Default::fallingSpeed);

        if (isInfiniteJump)
        {
            Utils::NOP(Base::Addr::infiniteJump, 2);
        }
        else
        {
            Utils::Patch(Base::Addr::infiniteJump, { 0x75, 0x27 });
        }

        if (isNoFallDamage)
        {
            Utils::NOP(Base::Addr::noFallDamage, 3);
        }
        else
        {
            Utils::Patch(Base::Addr::noFallDamage, { 0x8B, 0x4F, 0x78 });
        }
    }
}
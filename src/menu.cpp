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
    bool isAirSwim = false;
    bool isSuperFly = false;
    float walkingSpeed = Base::Default::walkingSpeed;

    void Show()
    {
        ImGui::Begin("Turtle WoW internal by Einhar");
        ImGui::Text("Detected WoW version: %s", Base::Addr::version);
        ImGui::Checkbox("Slow Fall", &isFallingSpeed);
        ImGui::Checkbox("Walk Speed", &isWalkingSpeed);

        if (isWalkingSpeed)
        {
            ImGui::SliderFloat("Walk Speed", &Menu::walkingSpeed, 0.f, 300.f);
        }

        ImGui::Checkbox("Infinite Jump", &isInfiniteJump);
        ImGui::Checkbox("No Fall Damage", &isNoFallDamage);
        ImGui::Checkbox("Wall Climb", &isWallClimb);
        ImGui::Checkbox("Air Swim", &isAirSwim);
        ImGui::Checkbox("Super Fly", &isSuperFly);

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

        player.setWallClimb(isWallClimb ? 0.f : Base::Default::wallClimb);

        if (isAirSwim)
        {
            Utils::Patch(Base::Addr::airSwim, { 0x00, 0x20 });
        }
        else
        {
            Utils::Patch(Base::Addr::airSwim, { 0x20, 0x00 });
        }

        if (isSuperFly)
        {
            Utils::NOP(Base::Addr::superFly, 2);
        }
        else
        {
            Utils::Patch(Base::Addr::superFly, { 0x74, 0x25 });
        }
    }
}
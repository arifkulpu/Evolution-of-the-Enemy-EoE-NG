#include "Menu.h"
#include "Settings.h"
#include "SKSEMenuFramework.h"

namespace Menu
{
    void __stdcall RenderGeneral()
    {
        auto settings = Settings::GetSingleton();
        bool changed = false;

        if (ImGuiMCP::Checkbox("Enable Mod", &settings->bEnableMod)) changed = true;
        ImGuiMCP::Separator();

        if (ImGuiMCP::SliderFloat("Health Gain / Level", &settings->fHealthGainPerLevel, 0.0f, 50.0f)) changed = true;
        if (ImGuiMCP::SliderFloat("Magicka Gain / Level", &settings->fMagickaGainPerLevel, 0.0f, 50.0f)) changed = true;
        if (ImGuiMCP::SliderFloat("Stamina Gain / Level", &settings->fStaminaGainPerLevel, 0.0f, 50.0f)) changed = true;
        ImGuiMCP::Separator();

        if (ImGuiMCP::SliderFloat("Boss Multiplier", &settings->fBossMultiplier, 1.0f, 5.0f)) changed = true;
        if (ImGuiMCP::SliderFloat("Damage Resist / Level", &settings->fDamageResistPerLevel, 0.0f, 10.0f)) changed = true;
        if (ImGuiMCP::SliderFloat("Magic Resist / Level", &settings->fMagicResistPerLevel, 0.0f, 10.0f)) changed = true;
        if (ImGuiMCP::SliderFloat("Attack Damage Mult / Level", &settings->fAttackDamageMultPerLevel, 0.0f, 0.5f)) changed = true;
        if (ImGuiMCP::SliderFloat("Spell Power Mod / Level", &settings->fSpellPowerModPerLevel, 0.0f, 0.5f)) changed = true;
        ImGuiMCP::Separator();

        if (ImGuiMCP::SliderFloat("Random Min", &settings->fRandomMin, 0.1f, 1.0f)) changed = true;
        if (ImGuiMCP::SliderFloat("Random Max", &settings->fRandomMax, 1.0f, 3.0f)) changed = true;
        if (ImGuiMCP::SliderFloat("Tier Mult / 10 Levels", &settings->fTierMultiplierPer10Levels, 0.0f, 1.0f)) changed = true;

        if (changed) {
            settings->Save();
        }
    }

    void __stdcall RenderToggles()
    {
        auto settings = Settings::GetSingleton();
        bool changed = false;

        if (ImGuiMCP::Checkbox("Bandits & Humanoids", &settings->bEnableBanditsAndHumanoids)) changed = true;
        if (ImGuiMCP::Checkbox("Animals", &settings->bEnableAnimals)) changed = true;
        if (ImGuiMCP::Checkbox("Monsters", &settings->bEnableMonsters)) changed = true;
        if (ImGuiMCP::Checkbox("Undead", &settings->bEnableUndead)) changed = true;
        if (ImGuiMCP::Checkbox("Automatons", &settings->bEnableAutomatons)) changed = true;
        if (ImGuiMCP::Checkbox("Dragons", &settings->bEnableDragons)) changed = true;
        if (ImGuiMCP::Checkbox("Bosses", &settings->bEnableBosses)) changed = true;

        if (changed) {
            settings->Save();
        }
    }

    void __stdcall RenderNerf()
    {
        auto settings = Settings::GetSingleton();
        bool changed = false;

        if (ImGuiMCP::Checkbox("Enable High Level Nerf", &settings->bEnableHighLevelNerf)) changed = true;
        if (ImGuiMCP::SliderFloat("Damage Nerf / Level", &settings->fNerfDamagePerLevel, 0.0f, 0.1f)) changed = true;
        if (ImGuiMCP::SliderFloat("Armor Nerf / Level", &settings->fNerfArmorPerLevel, 0.0f, 10.0f)) changed = true;
        if (ImGuiMCP::SliderFloat("Max Nerf Limit", &settings->fMaxNerfLimit, 0.0f, 0.9f)) changed = true;

        if (changed) {
            settings->Save();
        }
    }

    void __stdcall RenderVariance()
    {
        auto settings = Settings::GetSingleton();
        bool changed = false;

        if (ImGuiMCP::Checkbox("Enable Level Variance", &settings->bEnableLevelVariance)) changed = true;
        ImGuiMCP::TextWrapped("Each enemy gets a random, permanent level offset applied to the level it is scaled to (normally the player's level). Changes affect enemies processed from now on.");
        ImGuiMCP::Separator();

        if (ImGuiMCP::SliderInt("Variance Min", &settings->iVarianceMin, -30, 0)) changed = true;
        if (ImGuiMCP::SliderInt("Variance Max", &settings->iVarianceMax, 0, 30)) changed = true;
        ImGuiMCP::Separator();

        if (ImGuiMCP::Checkbox("Clamp To Encounter Zone", &settings->bClampToEncounterZone)) changed = true;
        ImGuiMCP::TextWrapped("Note: zone max levels cap the scaling, which works against EoE's 'ignore level caps' behavior. Leave off unless you want that.");
        ImGuiMCP::Separator();

        if (ImGuiMCP::Checkbox("Player Level Floor", &settings->bUsePlayerLevelFloor)) changed = true;
        if (ImGuiMCP::SliderInt("Floor Offset (player level - X)", &settings->iPlayerFloorOffset, 0, 30)) changed = true;
        ImGuiMCP::Separator();

        if (ImGuiMCP::Checkbox("Low Level Player Protection", &settings->bLowLevelProtection)) changed = true;
        if (ImGuiMCP::SliderInt("Player Level Threshold", &settings->iLowLevelThreshold, 1, 20)) changed = true;
        if (ImGuiMCP::SliderInt("Enemy Level Cap", &settings->iLowLevelEnemyCap, 1, 30)) changed = true;

        if (changed) {
            settings->Save();
        }
    }

    void Register()
    {
        if (!SKSEMenuFramework::IsInstalled()) {
            SKSE::log::info("SKSE Menu Framework is not installed, skipping menu registration.");
            return;
        }

        SKSEMenuFramework::SetSection("Evolution of the Enemy");
        SKSEMenuFramework::AddSectionItem("General & Scaling", RenderGeneral);
        SKSEMenuFramework::AddSectionItem("Enemy Toggles", RenderToggles);
        SKSEMenuFramework::AddSectionItem("High Level Nerf", RenderNerf);
        SKSEMenuFramework::AddSectionItem("Level Variance", RenderVariance);

        SKSE::log::info("Registered SKSE Menu Framework items for Evolution of the Enemy.");
    }
}

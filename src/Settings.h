#pragma once

#include <string>

class Settings
{
public:
    static Settings* GetSingleton()
    {
        static Settings singleton;
        return &singleton;
    }

    void Load();

    bool bEnableMod{true};
    float fHealthGainPerLevel{10.0f};
    float fMagickaGainPerLevel{10.0f};
    float fStaminaGainPerLevel{10.0f};
    float fBossMultiplier{2.0f};
    
    float fDamageResistPerLevel{1.0f};
    float fMagicResistPerLevel{1.0f};
    
    // In Skyrim, AttackDamageMult is usually a percentage scalar. E.g. +0.02 is +2% damage.
    // We will assume 0.05f means +5% damage per level.
    float fAttackDamageMultPerLevel{0.05f};
    float fSpellPowerModPerLevel{0.05f};

private:
    Settings() = default;
    ~Settings() = default;
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    void ParseLine(const std::string& line);
};

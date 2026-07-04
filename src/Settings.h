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
    float fBossMultiplier{1.5f};
    
    float fDamageResistPerLevel{1.0f};
    float fMagicResistPerLevel{1.0f};
    
    // In Skyrim, AttackDamageMult is usually a percentage scalar. E.g. +0.02 is +2% damage.
    // We will assume 0.05f means +5% damage per level.
    float fAttackDamageMultPerLevel{0.05f};
    float fSpellPowerModPerLevel{0.05f};
    
    // Randomness settings (variance applied to stat gains)
    float fRandomMin{0.8f};
    float fRandomMax{1.2f};
    
    // Tier/Bracket multiplier: bonus per 10 player levels
    float fTierMultiplierPer10Levels{0.10f};

private:
    Settings() = default;
    ~Settings() = default;
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    void ParseLine(const std::string& line);
};

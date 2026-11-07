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
    void Save();

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

    // Toggles for specific enemy types
    bool bEnableBanditsAndHumanoids{true};
    bool bEnableAnimals{true};
    bool bEnableMonsters{true};
    bool bEnableUndead{true};
    bool bEnableAutomatons{true};
    bool bEnableDragons{true};
    bool bEnableBosses{true};

    // Nerf settings for high level enemies
    bool bEnableHighLevelNerf{true};
    float fNerfDamagePerLevel{0.03f};
    float fNerfArmorPerLevel{2.0f};
    float fMaxNerfLimit{0.50f};

    // Level Variance (optional): each enemy gets a persistent random offset applied
    // to the TARGET level it is scaled to (default: player level).
    bool bEnableLevelVariance{false};
    int iVarianceMin{-5};
    int iVarianceMax{5};
    bool bClampToEncounterZone{false};   // clamp target level to the encounter zone min/max (max only if zone has one)
    bool bUsePlayerLevelFloor{false};    // target level >= playerLevel - iPlayerFloorOffset (only when player level > offset)
    int iPlayerFloorOffset{10};
    bool bLowLevelProtection{true};      // player level < iLowLevelThreshold: strong enemies skip variance, others capped
    int iLowLevelThreshold{5};
    int iLowLevelEnemyCap{10};

private:
    Settings() = default;
    ~Settings() = default;
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    void ParseLine(const std::string& line);
};

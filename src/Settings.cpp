#include "Settings.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void Settings::Load()
{
    // The INI file will be at Data/SKSE/Plugins/EvolutionOfTheEnemyNG.ini
    std::ifstream file("Data/SKSE/Plugins/EvolutionOfTheEnemyNG.ini");
    if (!file.is_open()) {
        SKSE::log::info("No INI file found. Creating default INI at Data/SKSE/Plugins/EvolutionOfTheEnemyNG.ini.");
        Save();
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        ParseLine(line);
    }
    
    SKSE::log::info("Settings loaded successfully!");
}

void Settings::Save()
{
    std::ofstream file("Data/SKSE/Plugins/EvolutionOfTheEnemyNG.ini");
    if (!file.is_open()) {
        SKSE::log::error("Failed to create default INI file!");
        return;
    }

    file << "[General]\n";
    file << "bEnableMod = " << (bEnableMod ? "1" : "0") << "\n\n";

    file << "[Stats]\n";
    file << "fHealthGainPerLevel = " << fHealthGainPerLevel << "\n";
    file << "fMagickaGainPerLevel = " << fMagickaGainPerLevel << "\n";
    file << "fStaminaGainPerLevel = " << fStaminaGainPerLevel << "\n\n";

    file << "[Boss]\n";
    file << "fBossMultiplier = " << fBossMultiplier << "\n\n";

    file << "[Resistance]\n";
    file << "fDamageResistPerLevel = " << fDamageResistPerLevel << "\n";
    file << "fMagicResistPerLevel = " << fMagicResistPerLevel << "\n\n";

    file << "[Damage]\n";
    file << "fAttackDamageMultPerLevel = " << fAttackDamageMultPerLevel << "\n";
    file << "fSpellPowerModPerLevel = " << fSpellPowerModPerLevel << "\n\n";

    file << "[Randomness]\n";
    file << "fRandomMin = " << fRandomMin << "\n";
    file << "fRandomMax = " << fRandomMax << "\n\n";

    file << "[Tier]\n";
    file << "fTierMultiplierPer10Levels = " << fTierMultiplierPer10Levels << "\n\n";

    file << "[Toggles]\n";
    file << "bEnableBanditsAndHumanoids = " << (bEnableBanditsAndHumanoids ? "1" : "0") << "\n";
    file << "bEnableAnimals = " << (bEnableAnimals ? "1" : "0") << "\n";
    file << "bEnableMonsters = " << (bEnableMonsters ? "1" : "0") << "\n";
    file << "bEnableUndead = " << (bEnableUndead ? "1" : "0") << "\n";
    file << "bEnableAutomatons = " << (bEnableAutomatons ? "1" : "0") << "\n";
    file << "bEnableDragons = " << (bEnableDragons ? "1" : "0") << "\n";
    file << "bEnableBosses = " << (bEnableBosses ? "1" : "0") << "\n\n";

    file << "[Nerf]\n";
    file << "bEnableHighLevelNerf = " << (bEnableHighLevelNerf ? "1" : "0") << "\n";
    file << "fNerfDamagePerLevel = " << fNerfDamagePerLevel << "\n";
    file << "fNerfArmorPerLevel = " << fNerfArmorPerLevel << "\n";
    file << "fMaxNerfLimit = " << fMaxNerfLimit << "\n";

    file.close();
    SKSE::log::info("Default INI file created successfully!");
}

void Settings::ParseLine(const std::string& line)
{
    auto commentPos = line.find(';');
    std::string content = line.substr(0, commentPos);

    // Trim whitespace
    content.erase(content.begin(), std::find_if(content.begin(), content.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    content.erase(std::find_if(content.rbegin(), content.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), content.end());

    if (content.empty() || content[0] == '[') return;

    auto eqPos = content.find('=');
    if (eqPos == std::string::npos) return;

    std::string key = content.substr(0, eqPos);
    std::string valStr = content.substr(eqPos + 1);

    // Trim again
    key.erase(std::find_if(key.rbegin(), key.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), key.end());
    valStr.erase(valStr.begin(), std::find_if(valStr.begin(), valStr.end(), [](unsigned char ch) { return !std::isspace(ch); }));

    try {
        if (key == "bEnableMod") bEnableMod = (std::stoi(valStr) != 0);
        else if (key == "fHealthGainPerLevel") fHealthGainPerLevel = std::stof(valStr);
        else if (key == "fMagickaGainPerLevel") fMagickaGainPerLevel = std::stof(valStr);
        else if (key == "fStaminaGainPerLevel") fStaminaGainPerLevel = std::stof(valStr);
        else if (key == "fBossMultiplier") fBossMultiplier = std::stof(valStr);
        else if (key == "fDamageResistPerLevel") fDamageResistPerLevel = std::stof(valStr);
        else if (key == "fMagicResistPerLevel") fMagicResistPerLevel = std::stof(valStr);
        else if (key == "fAttackDamageMultPerLevel") fAttackDamageMultPerLevel = std::stof(valStr);
        else if (key == "fSpellPowerModPerLevel") fSpellPowerModPerLevel = std::stof(valStr);
        else if (key == "fRandomMin") fRandomMin = std::stof(valStr);
        else if (key == "fRandomMax") fRandomMax = std::stof(valStr);
        else if (key == "fTierMultiplierPer10Levels") fTierMultiplierPer10Levels = std::stof(valStr);
        else if (key == "bEnableBanditsAndHumanoids") bEnableBanditsAndHumanoids = (std::stoi(valStr) != 0);
        else if (key == "bEnableAnimals") bEnableAnimals = (std::stoi(valStr) != 0);
        else if (key == "bEnableMonsters") bEnableMonsters = (std::stoi(valStr) != 0);
        else if (key == "bEnableUndead") bEnableUndead = (std::stoi(valStr) != 0);
        else if (key == "bEnableAutomatons") bEnableAutomatons = (std::stoi(valStr) != 0);
        else if (key == "bEnableDragons") bEnableDragons = (std::stoi(valStr) != 0);
        else if (key == "bEnableBosses") bEnableBosses = (std::stoi(valStr) != 0);
        else if (key == "bEnableHighLevelNerf") bEnableHighLevelNerf = (std::stoi(valStr) != 0);
        else if (key == "fNerfDamagePerLevel") fNerfDamagePerLevel = std::stof(valStr);
        else if (key == "fNerfArmorPerLevel") fNerfArmorPerLevel = std::stof(valStr);
        else if (key == "fMaxNerfLimit") fMaxNerfLimit = std::stof(valStr);
    } catch (...) {
        SKSE::log::warn("Failed to parse setting: {} = {}", key, valStr);
    }
}

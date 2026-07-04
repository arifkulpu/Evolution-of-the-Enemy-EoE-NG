#include "Settings.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void Settings::Load()
{
    // The INI file will be at Data/SKSE/Plugins/EvolutionOfTheEnemyNG.ini
    std::ifstream file("Data/SKSE/Plugins/EvolutionOfTheEnemyNG.ini");
    if (!file.is_open()) {
        SKSE::log::info("No INI file found. Using default settings.");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        ParseLine(line);
    }
    
    SKSE::log::info("Settings loaded successfully!");
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
    } catch (...) {
        SKSE::log::warn("Failed to parse setting: {} = {}", key, valStr);
    }
}

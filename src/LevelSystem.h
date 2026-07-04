#pragma once

class Settings;

namespace LevelSystem
{
    void InstallHooks();
    void UpdateNPCLevels();
    void ProcessSingleActor(RE::Actor* actorPtr, uint16_t playerLevel);
    void ProcessActorList(RE::BSTArray<RE::ActorHandle>& handles, uint16_t playerLevel);
    bool IsBoss(RE::Actor* actor);
}

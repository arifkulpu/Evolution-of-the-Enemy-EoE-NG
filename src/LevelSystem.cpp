#include "LevelSystem.h"
#include "Settings.h"
#include <random>

namespace LevelSystem
{
    class LevelUpEventHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
    {
    public:
        static LevelUpEventHandler* GetSingleton()
        {
            static LevelUpEventHandler singleton;
            return &singleton;
        }

        RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override
        {
            if (!a_event || !a_eventSource)
                return RE::BSEventNotifyControl::kContinue;

            // When the stats menu closes, player might have leveled up
            if (a_event->menuName == RE::StatsMenu::MENU_NAME && !a_event->opening) {
                UpdateNPCLevels();
            }

            return RE::BSEventNotifyControl::kContinue;
        }
    };

    class CellAttachEventHandler : public RE::BSTEventSink<RE::TESCellAttachDetachEvent>
    {
    public:
        static CellAttachEventHandler* GetSingleton()
        {
            static CellAttachEventHandler singleton;
            return &singleton;
        }

        RE::BSEventNotifyControl ProcessEvent(const RE::TESCellAttachDetachEvent* a_event, RE::BSTEventSource<RE::TESCellAttachDetachEvent>*) override
        {
            if (a_event && a_event->attached) {
                UpdateNPCLevels();
            }
            return RE::BSEventNotifyControl::kContinue;
        }
    };

    class CombatEventHandler : public RE::BSTEventSink<RE::TESCombatEvent>
    {
    public:
        static CombatEventHandler* GetSingleton()
        {
            static CombatEventHandler singleton;
            return &singleton;
        }

        RE::BSEventNotifyControl ProcessEvent(const RE::TESCombatEvent* a_event, RE::BSTEventSource<RE::TESCombatEvent>*) override
        {
            if (a_event && a_event->newState != RE::ACTOR_COMBAT_STATE::kNone) {
                UpdateNPCLevels();
            }
            return RE::BSEventNotifyControl::kContinue;
        }
    };

    void InstallHooks()
    {
        if (auto ui = RE::UI::GetSingleton()) {
            ui->AddEventSink(LevelUpEventHandler::GetSingleton());
            SKSE::log::info("Registered MenuOpenCloseEvent Sink");
        }

        if (auto scripts = RE::ScriptEventSourceHolder::GetSingleton()) {
            scripts->AddEventSink(CellAttachEventHandler::GetSingleton());
            scripts->AddEventSink(CombatEventHandler::GetSingleton());
            SKSE::log::info("Registered TESCellAttachDetachEvent and TESCombatEvent Sinks");
        }
    }

    bool IsBoss(RE::Actor* actor)
    {
        if (!actor) return false;
        
        if (actor->HasKeywordString("LocRefTypeBoss")) return true;
        
        auto actorBase = actor->GetActorBase();
        if (actorBase) {
            auto race = actorBase->GetRace();
            if (race && race->HasKeywordString("ActorTypeDragon")) return true;
        }
        
        return false;
    }

    void UpdateNPCLevels()
    {
        auto settings = Settings::GetSingleton();
        if (!settings->bEnableMod) return;

        auto player = RE::PlayerCharacter::GetSingleton();
        if (!player) return;

        uint16_t playerLevel = player->GetLevel();

        auto processManager = RE::ProcessLists::GetSingleton();
        if (!processManager) return;

        for (auto& handle : processManager->highActorHandles) {
            auto actorPtr = handle.get();
            if (actorPtr && actorPtr->Is3DLoaded() && !actorPtr->IsDead() && !actorPtr->IsPlayerRef()) {
                auto actorBase = actorPtr->GetActorBase();
                if (!actorBase || actorBase->IsInvulnerable() || actorBase->IsEssential()) continue;

                uint16_t npcLevel = actorPtr->GetLevel();

                float extraLevels = actorPtr->AsActorValueOwner()->GetActorValue(RE::ActorValue::kVariable10);
                uint16_t effectiveLevel = npcLevel + static_cast<uint16_t>(extraLevels);

                if (effectiveLevel < playerLevel) {
                    uint16_t levelDiff = playerLevel - effectiveLevel;
                    
                    bool isMage = false;
                    bool isArcher = false;
                    bool isMelee = false;

                    auto rightHand = actorPtr->GetEquippedObject(false);
                    auto leftHand = actorPtr->GetEquippedObject(true);

                    if (rightHand) {
                        if (rightHand->IsWeapon()) {
                            auto weapon = rightHand->As<RE::TESObjectWEAP>();
                            if (weapon->IsBow() || weapon->IsCrossbow()) isArcher = true;
                            else if (weapon->IsMelee()) isMelee = true;
                        } else if (rightHand->IsMagicItem()) {
                            isMage = true;
                        }
                    }

                    if (leftHand) {
                        if (leftHand->IsWeapon()) {
                            auto weapon = leftHand->As<RE::TESObjectWEAP>();
                            if (weapon->IsBow() || weapon->IsCrossbow()) isArcher = true;
                            else if (weapon->IsMelee()) isMelee = true;
                        } else if (leftHand->IsMagicItem()) {
                            isMage = true;
                        }
                    }

                    if (!isMage && !isArcher && !isMelee) isMelee = true;

                    float healthGain = settings->fHealthGainPerLevel;
                    float magickaGain = settings->fMagickaGainPerLevel;
                    float staminaGain = settings->fStaminaGainPerLevel;
                    float attackDamageGain = settings->fAttackDamageMultPerLevel;
                    float spellPowerGain = settings->fSpellPowerModPerLevel;

                    if (isMage) {
                        healthGain *= 0.1f;       // Büyücü canı çok az artmalı
                        staminaGain *= 0.2f;      
                        magickaGain *= 2.5f;      // Asıl manaları artmalı
                        spellPowerGain *= 1.75f;  // Hasarı %75 fazla
                    } else if (isArcher) {
                        healthGain *= 0.8f;       // Okçuların orta canı
                        staminaGain *= 2.0f;      // Dayanıklılık artmalı
                        magickaGain *= 0.1f;      
                        attackDamageGain *= 1.50f;// Hasarı %50 artsın
                    } else if (isMelee) {
                        healthGain *= 2.0f;       // Tank karakterlerin canı yüksek olacak
                        staminaGain *= 1.2f;      
                        magickaGain *= 0.1f;      
                        attackDamageGain *= 0.10f;// Hasar artışı %10 olacak
                    }

                    float multiplier = 1.0f;
                    if (IsBoss(actorPtr.get())) {
                        multiplier = settings->fBossMultiplier;
                    }

                    // Tier/Bracket: her 10 seviyede bonus çarpan
                    float tierMultiplier = 1.0f + (static_cast<float>(playerLevel / 10) * settings->fTierMultiplierPer10Levels);

                    // Rastgele çarpan: her NPC'ye farklı güç
                    static std::mt19937 rng(std::random_device{}());
                    std::uniform_real_distribution<float> dist(settings->fRandomMin, settings->fRandomMax);
                    float randomMultiplier = dist(rng);

                    float combinedMult = multiplier * tierMultiplier * randomMultiplier;

                    float finalHealthGain = levelDiff * healthGain * combinedMult;
                    float finalMagickaGain = levelDiff * magickaGain * combinedMult;
                    float finalStaminaGain = levelDiff * staminaGain * combinedMult;
                    
                    float resistGain = levelDiff * combinedMult;
                    float damageResistGain = resistGain * settings->fDamageResistPerLevel;
                    float magicResistGain = resistGain * settings->fMagicResistPerLevel;
                    
                    float finalAttackDamageGain = resistGain * attackDamageGain;
                    float finalSpellPowerGain = resistGain * spellPowerGain;

                    auto avOwner = actorPtr->AsActorValueOwner();
                    
                    // Mod Stats
                    avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kPermanent, RE::ActorValue::kHealth, finalHealthGain);
                    avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kPermanent, RE::ActorValue::kMagicka, finalMagickaGain);
                    avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kPermanent, RE::ActorValue::kStamina, finalStaminaGain);

                    avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kHealth, finalHealthGain);
                    avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kMagicka, finalMagickaGain);
                    avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kStamina, finalStaminaGain);
                    
                    // Mod Resistances (Armor and Magic Resist)
                    avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kPermanent, RE::ActorValue::kDamageResist, damageResistGain);
                    avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kPermanent, RE::ActorValue::kResistMagic, magicResistGain);
                    
                    // Mod Damage Multipliers
                    avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kPermanent, RE::ActorValue::kAttackDamageMult, finalAttackDamageGain);
                    avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kPermanent, RE::ActorValue::kDestructionPowerModifier, finalSpellPowerGain);
                    
                    // Track applied level difference
                    avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kPermanent, RE::ActorValue::kVariable10, static_cast<float>(levelDiff));
                }
            }
        }
    }
}

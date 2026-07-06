#include "LevelSystem.h"
#include "Settings.h"
#include <random>

namespace LevelSystem
{
    // Rastgele sayı üreteci (thread-safe statik)
    static std::mt19937& GetRNG() {
        static std::mt19937 rng(std::random_device{}());
        return rng;
    }

    // Tek bir NPC'yi günceller
    void ProcessSingleActor(RE::Actor* actorPtr, uint16_t playerLevel)
    {
        if (!actorPtr || actorPtr->IsDead() || actorPtr->IsPlayerRef()) return;

        // Takipçileri (followers) atla
        if (actorPtr->IsPlayerTeammate()) return;

        auto settings = Settings::GetSingleton();
        auto actorBase = actorPtr->GetActorBase();
        if (!actorBase || actorBase->IsInvulnerable() || actorBase->IsEssential()) return;

        // Sadece düşman NPC'leri güçlendir: Aggression kontrolü
        // 0 = Barışçıl (tüccar, siviller), 1 = Saldırgan (gardiyanlar), 2+ = Çok saldırgan (haydutlar, canavarlar)
        float aggression = actorPtr->AsActorValueOwner()->GetActorValue(RE::ActorValue::kAggression);
        if (aggression < 1.0f) return;

        bool isBoss = IsBoss(actorPtr);
        if (isBoss && !settings->bEnableBosses) return;

        if (!isBoss) {
            auto race = actorBase->GetRace();
            bool isDragon = race && race->HasKeywordString("ActorTypeDragon");
            if (isDragon && !settings->bEnableDragons) return;
            
            bool isAnimal = actorPtr->HasKeywordString("ActorTypeAnimal");
            if (isAnimal && !settings->bEnableAnimals) return;
            
            bool isMonster = actorPtr->HasKeywordString("ActorTypeMonster") || actorPtr->HasKeywordString("ActorTypeTroll");
            if (isMonster && !settings->bEnableMonsters) return;
            
            bool isUndead = actorPtr->HasKeywordString("ActorTypeUndead") || actorPtr->HasKeywordString("Vampire");
            if (isUndead && !settings->bEnableUndead) return;
            
            bool isDwarven = actorPtr->HasKeywordString("ActorTypeDwarven");
            if (isDwarven && !settings->bEnableAutomatons) return;
            
            bool isNPC = actorPtr->HasKeywordString("ActorTypeNPC");
            if (isNPC && !settings->bEnableBanditsAndHumanoids) return;
        }

        uint16_t npcLevel = actorPtr->GetLevel();

        float extraLevels = actorPtr->AsActorValueOwner()->GetActorValue(RE::ActorValue::kVariable10);
        uint16_t effectiveLevel = npcLevel + static_cast<uint16_t>(extraLevels);

        if (effectiveLevel >= playerLevel) return;

        uint16_t levelDiff = playerLevel - effectiveLevel;
        enum class NPCRole {
            ShieldTank,
            DualWield,
            Assassin,
            AxeMace,
            Melee1H,
            Melee2H,
            Spearman,
            Rifleman,
            Archer,
            Spellsword,
            MageDestruction,
            MageHealer,
            MageConjurer
        };

        NPCRole role = NPCRole::Melee1H;
        auto rightHand = actorPtr->GetEquippedObject(false);
        auto leftHand = actorPtr->GetEquippedObject(true);

        bool hasShield = false;
        bool hasMagicL = false, hasMagicR = false;
        bool hasMeleeL = false, hasMeleeR = false;
        bool hasDagger = false;
        bool hasAxeMace = false;
        bool is2H = false;
        bool isBow = false;
        bool isCrossbow = false;
        
        RE::SpellItem* spellL = nullptr;
        RE::SpellItem* spellR = nullptr;

        if (leftHand) {
            if (leftHand->IsArmor()) hasShield = true;
            else if (leftHand->IsWeapon()) {
                hasMeleeL = true;
                auto w = leftHand->As<RE::TESObjectWEAP>();
                if (w->IsOneHandedDagger()) hasDagger = true;
                if (w->IsOneHandedAxe() || w->IsOneHandedMace()) hasAxeMace = true;
            }
            else if (leftHand->IsMagicItem()) {
                hasMagicL = true;
                spellL = leftHand->As<RE::SpellItem>();
            }
        }

        if (rightHand) {
            if (rightHand->IsWeapon()) {
                auto w = rightHand->As<RE::TESObjectWEAP>();
                if (w->IsBow()) isBow = true;
                if (w->IsCrossbow()) isCrossbow = true;
                if (w->IsTwoHandedAxe() || w->IsTwoHandedSword()) is2H = true;
                if (w->IsOneHandedDagger()) hasDagger = true;
                if (w->IsOneHandedAxe() || w->IsOneHandedMace()) hasAxeMace = true;
                if (w->IsMelee()) hasMeleeR = true;
                
                if (w->HasKeywordString("WeapTypeSpear") || w->HasKeywordString("WeapTypeHalberd") || w->HasKeywordString("WeapTypePike")) {
                    role = NPCRole::Spearman;
                } else if (w->HasKeywordString("WeapTypeRifle") || w->HasKeywordString("WeapTypeMusket")) {
                    role = NPCRole::Rifleman;
                }
            }
            else if (rightHand->IsMagicItem()) {
                hasMagicR = true;
                spellR = rightHand->As<RE::SpellItem>();
            }
        }

        if (role != NPCRole::Spearman && role != NPCRole::Rifleman) {
            if (hasShield) {
                role = NPCRole::ShieldTank;
            } else if (isCrossbow) {
                role = NPCRole::Rifleman;
            } else if (isBow) {
                role = NPCRole::Archer;
            } else if (is2H) {
                role = NPCRole::Melee2H;
            } else if ((hasMagicL && hasMeleeR) || (hasMagicR && hasMeleeL)) {
                role = NPCRole::Spellsword;
            } else if (hasMeleeL && hasMeleeR) {
                role = NPCRole::DualWield;
            } else if (hasDagger) {
                role = NPCRole::Assassin;
            } else if (hasAxeMace) {
                role = NPCRole::AxeMace;
            } else if (hasMagicL || hasMagicR) {
                RE::ActorValue skill = RE::ActorValue::kDestruction;
                if (hasMagicL && spellL) skill = spellL->GetAssociatedSkill();
                else if (hasMagicR && spellR) skill = spellR->GetAssociatedSkill();
                
                if (skill == RE::ActorValue::kRestoration) role = NPCRole::MageHealer;
                else if (skill == RE::ActorValue::kConjuration) role = NPCRole::MageConjurer;
                else role = NPCRole::MageDestruction;
            } else {
                role = NPCRole::Melee1H;
            }
        }

        float healthGain = settings->fHealthGainPerLevel;
        float magickaGain = settings->fMagickaGainPerLevel;
        float staminaGain = settings->fStaminaGainPerLevel;
        float attackDamageGain = settings->fAttackDamageMultPerLevel;
        float spellPowerGain = settings->fSpellPowerModPerLevel;
        float speedGain = 0.0f;

        switch (role) {
            case NPCRole::ShieldTank:
                healthGain *= 3.0f;
                attackDamageGain *= 0.0f;
                staminaGain *= 1.0f;
                break;
            case NPCRole::Melee1H:
                healthGain *= 2.0f;
                attackDamageGain *= 0.10f;
                staminaGain *= 1.2f;
                break;
            case NPCRole::AxeMace:
                healthGain *= 2.2f;
                attackDamageGain *= 0.20f;
                staminaGain *= 1.5f;
                break;
            case NPCRole::DualWield:
                healthGain *= 1.2f;
                attackDamageGain *= 0.70f;
                staminaGain *= 2.0f;
                speedGain = 10.0f;
                break;
            case NPCRole::Melee2H:
                healthGain *= 1.5f;
                attackDamageGain *= 0.60f;
                staminaGain *= 1.5f;
                break;
            case NPCRole::Assassin:
                healthGain *= 0.5f;
                attackDamageGain *= 1.0f;
                staminaGain *= 1.5f;
                speedGain = 20.0f;
                break;
            case NPCRole::Spellsword:
                healthGain *= 1.2f;
                magickaGain *= 1.2f;
                attackDamageGain *= 0.15f;
                spellPowerGain *= 0.15f;
                break;
            case NPCRole::Spearman:
                healthGain *= 1.5f;
                attackDamageGain *= 0.30f;
                staminaGain *= 1.5f;
                break;
            case NPCRole::Rifleman:
                healthGain *= 0.8f;
                attackDamageGain *= 0.60f;
                staminaGain *= 0.5f;
                break;
            case NPCRole::Archer:
                healthGain *= 0.8f;
                attackDamageGain *= 0.25f;
                staminaGain *= 2.0f;
                break;
            case NPCRole::MageDestruction:
                healthGain *= 0.1f;
                magickaGain *= 2.5f;
                spellPowerGain *= 0.40f;
                break;
            case NPCRole::MageHealer:
                healthGain *= 0.8f;
                magickaGain *= 3.0f;
                spellPowerGain *= 0.0f;
                break;
            case NPCRole::MageConjurer:
                healthGain *= 0.3f;
                magickaGain *= 3.0f;
                spellPowerGain *= 0.10f;
                break;
        }

        float multiplier = 1.0f;
        if (IsBoss(actorPtr)) {
            multiplier = settings->fBossMultiplier;
        }

        // Tier/Bracket: her 10 seviyede bonus çarpan
        float tierMultiplier = 1.0f + (static_cast<float>(playerLevel / 10) * settings->fTierMultiplierPer10Levels);

        // Rastgele çarpan: her NPC'ye farklı güç
        std::uniform_real_distribution<float> dist(settings->fRandomMin, settings->fRandomMax);
        float randomMultiplier = dist(GetRNG());

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
        
        // Mod Speed
        if (speedGain > 0.0f) {
            float finalSpeedGain = speedGain * combinedMult;
            avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kPermanent, RE::ActorValue::kSpeedMult, finalSpeedGain);
        }

        // Track applied level difference
        avOwner->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kPermanent, RE::ActorValue::kVariable10, static_cast<float>(levelDiff));
    }

    // Bir handle listesindeki tüm aktörleri işler
    void ProcessActorList(RE::BSTArray<RE::ActorHandle>& handles, uint16_t playerLevel)
    {
        for (auto& handle : handles) {
            auto actorPtr = handle.get();
            if (actorPtr) {
                ProcessSingleActor(actorPtr.get(), playerLevel);
            }
        }
    }

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

            if (a_event->menuName == RE::StatsMenu::MENU_NAME && !a_event->opening) {
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
            if (a_event && a_event->actor && a_event->newState != RE::ACTOR_COMBAT_STATE::kNone) {
                auto settings = Settings::GetSingleton();
                if (!settings->bEnableMod) return RE::BSEventNotifyControl::kContinue;
                
                auto player = RE::PlayerCharacter::GetSingleton();
                if (player) {
                    auto actor = a_event->actor.get()->As<RE::Actor>();
                    if (actor) {
                        ProcessSingleActor(actor, player->GetLevel());
                    }
                }
            }
            return RE::BSEventNotifyControl::kContinue;
        }
    };

    // NPC yüklendiğinde tetiklenen olay
    class ObjectLoadedEventHandler : public RE::BSTEventSink<RE::TESObjectLoadedEvent>
    {
    public:
        static ObjectLoadedEventHandler* GetSingleton()
        {
            static ObjectLoadedEventHandler singleton;
            return &singleton;
        }

        RE::BSEventNotifyControl ProcessEvent(const RE::TESObjectLoadedEvent* a_event, RE::BSTEventSource<RE::TESObjectLoadedEvent>*) override
        {
            if (!a_event || !a_event->loaded) return RE::BSEventNotifyControl::kContinue;

            auto settings = Settings::GetSingleton();
            if (!settings->bEnableMod) return RE::BSEventNotifyControl::kContinue;

            auto form = RE::TESForm::LookupByID(a_event->formID);
            if (!form) return RE::BSEventNotifyControl::kContinue;

            auto actor = form->As<RE::Actor>();
            if (!actor) return RE::BSEventNotifyControl::kContinue;

            auto player = RE::PlayerCharacter::GetSingleton();
            if (!player) return RE::BSEventNotifyControl::kContinue;

            uint16_t playerLevel = player->GetLevel();
            ProcessSingleActor(actor, playerLevel);

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
            scripts->AddEventSink(CombatEventHandler::GetSingleton());
            scripts->AddEventSink(ObjectLoadedEventHandler::GetSingleton());
            SKSE::log::info("Registered Combat and ObjectLoaded Event Sinks");
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

        // Tüm aktör listelerini tara
        ProcessActorList(processManager->highActorHandles, playerLevel);
        ProcessActorList(processManager->middleHighActorHandles, playerLevel);
        ProcessActorList(processManager->middleLowActorHandles, playerLevel);
        ProcessActorList(processManager->lowActorHandles, playerLevel);
    }
}

# Dynamic NPC Level System

## Türkçe (Turkish)

### Modun Amacı ve Ne İşe Yaradığı
**Dynamic NPC Level System**, Skyrim'deki düşmanları ve NPC'leri oyuncunun seviyesine göre dinamik olarak güçlendiren bir SKSE modudur. Oyunun zorluğunu sürekli ve dengeli kılmak amacıyla tasarlanmıştır.

Bu mod sayesinde:
- Düşmanların seviyesi, oyuncunun mevcut seviyesine göre yukarı çekilir.
- NPC'lerin **Sağlık, Efsun (Magicka) ve Dayanıklılık (Stamina)** statları, level farkına göre dinamik olarak artar.
- Düşman sınıfları kendi uzmanlıklarına göre ekstra güçlenir:
  - **Tank ve Kılıç kullananlar:** Sağlık 2x artış, dayanıklılık 1.2x artış, fiziksel hasar artışı %10. Devasa canlarıyla etten duvar gibi olurlar, ama hasarları düşüktür.
  - **Okçu ve Arbalet kullananlar:** Dayanıklılık 2x artış, sağlık 0.8x (orta seviye), fiziksel hasar artışı %50. Yüksek dayanıklılıkları sayesinde sürekli ok atabilirler.
  - **Büyücüler:** Magicka 2.5x artış, sağlık 0.1x (çok az), büyü hasarı (Destruction) %75 artış. Cam toplar gibi kırılgandırlar ama büyüleri çok ölümcüldür.
- Boss niteliğindeki düşmanlar ve ejderhalar için özel çarpanlar devreye girerek daha efsanevi savaşlar sunulur.

### Seviye Kademe Sistemi (Level Brackets)
Oyuncunun seviyesi her 10 levelde bir kademe atlayarak NPC'lere ek bonus çarpan uygulanır:
| Oyuncu Seviyesi | Kademe | Çarpan |
|:---:|:---:|:---:|
| 1 - 9 | 0 | 1.0x |
| 10 - 19 | 1 | 1.1x |
| 20 - 29 | 2 | 1.2x |
| 50 - 59 | 5 | 1.5x |
| 100 | 10 | 2.0x |

### Rastgelelik Sistemi (Random Variance)
Her NPC'ye buff uygulanırken **%80 ile %120** arasında rastgele bir çarpan atanır. Böylece aynı seviyedeki iki haydut bile farklı güçte olur — her savaş farklı bir deneyim sunar!

### INI ile Ayarlanabilir Değerler
`Data/SKSE/Plugins/DynamicNPCLevelSystem.ini` dosyasıyla tüm değerler özelleştirilebilir:
```ini
[General]
bEnableMod = 1

[Stats]
fHealthGainPerLevel = 10.0
fMagickaGainPerLevel = 10.0
fStaminaGainPerLevel = 10.0

[Boss]
fBossMultiplier = 2.0

[Resistance]
fDamageResistPerLevel = 1.0
fMagicResistPerLevel = 1.0

[Damage]
fAttackDamageMultPerLevel = 0.05
fSpellPowerModPerLevel = 0.05

[Randomness]
fRandomMin = 0.8
fRandomMax = 1.2

[Tier]
fTierMultiplierPer10Levels = 0.10
```

### Uyumluluk
- Mod CommonLibSSE-NG altyapısıyla geliştirildiği için tek bir DLL dosyası ile **Skyrim Special Edition (1.5.97)**, **Skyrim Anniversary Edition (1.6.xx)** ve **Skyrim VR** sürümleriyle tam uyumludur.
- Düşman statlarını değiştiren diğer modlarla çalışabilir; dinamik hesaplamalar mevcut statlar üzerine eklenir. 

### Gereksinimler
- [SKSE64](http://skse.silverlock.org/) (Sürümünüze uygun olan)
- [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)

### Kurulum
1. `DynamicNPCLevelSystem.dll` dosyasını `Data/SKSE/Plugins/` klasörüne kopyalayın.
2. (İsteğe bağlı) `DynamicNPCLevelSystem.ini` dosyası oluşturarak yukarıdaki ayarları özelleştirin.
3. Oyunu SKSE üzerinden başlatın.

---

## English

### Purpose and Features
**Dynamic NPC Level System** is an SKSE plugin that dynamically scales and buffs enemies and NPCs based on the player's level, ensuring a consistent and balanced challenge throughout your Skyrim playthrough.

With this mod:
- Enemy levels are scaled up dynamically to match or exceed the player's level.
- NPCs' **Health, Magicka, and Stamina** stats are dynamically increased based on the level difference.
- Enemy classes gain specific bonuses based on their combat style:
  - **Tanks and Melee Fighters:** Health 2x gain, stamina 1.2x gain, attack damage increase only 10%. They become walls of flesh with massive health but very low extra damage.
  - **Archers and Crossbowmen:** Stamina 2x gain, health 0.8x (moderate), attack damage increase 50%. High stamina lets them fire arrows relentlessly.
  - **Mages:** Magicka 2.5x gain, health 0.1x (very low), spell damage (Destruction) increase 75%. Fragile as glass cannons but their spells are deadly.
- Bosses and dragons receive special multipliers for truly epic battles.

### Level Bracket System (Tier Scaling)
Every 10 player levels, NPCs receive an additional bonus multiplier:
| Player Level | Tier | Multiplier |
|:---:|:---:|:---:|
| 1 - 9 | 0 | 1.0x |
| 10 - 19 | 1 | 1.1x |
| 20 - 29 | 2 | 1.2x |
| 50 - 59 | 5 | 1.5x |
| 100 | 10 | 2.0x |

### Random Variance System
Each NPC receives a random multiplier between **0.8x and 1.2x** when buffed. This means two bandits of the same level may have different stats — every encounter feels unique!

### Configurable via INI
All values can be customized through `Data/SKSE/Plugins/DynamicNPCLevelSystem.ini`:
```ini
[General]
bEnableMod = 1

[Stats]
fHealthGainPerLevel = 10.0
fMagickaGainPerLevel = 10.0
fStaminaGainPerLevel = 10.0

[Boss]
fBossMultiplier = 2.0

[Resistance]
fDamageResistPerLevel = 1.0
fMagicResistPerLevel = 1.0

[Damage]
fAttackDamageMultPerLevel = 0.05
fSpellPowerModPerLevel = 0.05

[Randomness]
fRandomMin = 0.8
fRandomMax = 1.2

[Tier]
fTierMultiplierPer10Levels = 0.10
```

### Compatibility
- Built with CommonLibSSE-NG, this mod uses a single DLL that is fully compatible with **Skyrim Special Edition (1.5.97)**, **Skyrim Anniversary Edition (1.6.xx)**, and **Skyrim VR**.
- Highly compatible with other mods that modify enemy stats, as the dynamic bonuses are applied on top of existing values.

### Requirements
- [SKSE64](http://skse.silverlock.org/) (Version matching your game)
- [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)

### Installation
1. Copy `DynamicNPCLevelSystem.dll` to `Data/SKSE/Plugins/`.
2. (Optional) Create a `DynamicNPCLevelSystem.ini` file to customize the settings listed above.
3. Launch the game through SKSE.

---

## License / Lisans
Copyright (c) 2026 Arif KULPU. All Rights Reserved. — Tüm Hakları Saklıdır. See LICENSE for details.

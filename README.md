# Dynamic NPC Level System

## Türkçe (Turkish)

### Modun Amacı ve Ne İşe Yaradığı
**Dynamic NPC Level System**, Skyrim'deki düşmanları ve NPC'leri oyuncunun seviyesine göre dinamik olarak güçlendiren bir SKSE modudur. Oyunun zorluğunu sürekli ve dengeli kılmak amacıyla tasarlanmıştır. Yüksek levellerde bile düşmanlar sizi zorlayacak — artık herkese tek atamazsınız!

Bu mod sayesinde:
- Düşmanların statları, oyuncunun mevcut seviyesine göre dinamik olarak artar.
- **Sadece düşman NPC'ler** etkilenir — takipçiler, tüccarlar ve siviller güçlenmez.
- Hayvanlar (kurt, ayı, örümcek), ejderhalar ve tüm düşman yaratıklar sisteme dahildir.
- Düşman sınıfları kendi uzmanlıklarına göre farklı şekilde güçlenir:
  - **Tank ve Kılıç kullananlar:** Devasa can havuzuyla etten duvar olurlar, ama hasarları düşüktür.
  - **Okçu ve Arbalet kullananlar:** Yüksek dayanıklılıkla sürekli ok atabilirler, orta seviye cana sahiptirler.
  - **Büyücüler:** Çok yüksek manayla ölümcül büyüler atarlar ama cam top gibi kırılgandırlar.
- Boss niteliğindeki düşmanlar ve ejderhalar için özel çarpanlar (%50 bonus) devreye girer.

### Sınıf Bazlı Stat Artışları

| Stat | Tank/Kılıçlı | Okçu | Büyücü |
|:---|:---:|:---:|:---:|
| **Can (Health)** | ×2.0 | ×0.8 | ×0.1 |
| **Mana (Magicka)** | ×0.1 | ×0.1 | ×2.5 |
| **Dayanıklılık (Stamina)** | ×1.2 | ×2.0 | ×0.2 |
| **Fiziksel Hasar** | %10 | %25 | — |
| **Büyü Hasarı** | — | — | %40 |

### Hangi NPC'ler Etkilenir?

| NPC Tipi | Etkilenir mi? |
|:---|:---:|
| Haydutlar, korsanlar | ✅ |
| Kurtlar, ayılar, örümcekler | ✅ |
| Ejderhalar (Boss çarpanıyla) | ✅ |
| Draugr, vampirler | ✅ |
| Gardiyanlar | ✅ |
| Takipçiler (Lydia vb.) | ❌ |
| Tüccarlar, siviller | ❌ |
| Essential / Invulnerable NPC'ler | ❌ |

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
fBossMultiplier = 1.5

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
**Dynamic NPC Level System** is an SKSE plugin that dynamically scales and buffs enemies and NPCs based on the player's level, ensuring a consistent and balanced challenge throughout your Skyrim playthrough. Even at high levels, enemies will keep you on your toes — no more one-shotting everything!

With this mod:
- Enemy stats are dynamically increased based on the level difference with the player.
- **Only hostile NPCs** are affected — followers, merchants and civilians are not buffed.
- Animals (wolves, bears, spiders), dragons and all hostile creatures are included.
- Enemy classes gain specific bonuses based on their combat style:
  - **Tanks and Melee Fighters:** Massive health pools make them walls of flesh, but their extra damage is very low.
  - **Archers and Crossbowmen:** High stamina lets them fire arrows relentlessly, with moderate health.
  - **Mages:** Very high magicka with deadly spells, but fragile as glass cannons.
- Bosses and dragons receive a special multiplier (50% bonus) for truly epic battles.

### Class-Based Stat Multipliers

| Stat | Tank/Melee | Archer | Mage |
|:---|:---:|:---:|:---:|
| **Health** | ×2.0 | ×0.8 | ×0.1 |
| **Magicka** | ×0.1 | ×0.1 | ×2.5 |
| **Stamina** | ×1.2 | ×2.0 | ×0.2 |
| **Physical Damage** | 10% | 25% | — |
| **Spell Damage** | — | — | 40% |

### Which NPCs Are Affected?

| NPC Type | Affected? |
|:---|:---:|
| Bandits, pirates | ✅ |
| Wolves, bears, spiders | ✅ |
| Dragons (with Boss multiplier) | ✅ |
| Draugr, vampires | ✅ |
| Guards | ✅ |
| Followers (Lydia, etc.) | ❌ |
| Merchants, civilians | ❌ |
| Essential / Invulnerable NPCs | ❌ |

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
fBossMultiplier = 1.5

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

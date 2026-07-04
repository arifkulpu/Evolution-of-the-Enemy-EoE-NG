# Evolution of the Enemy (EoE) NG

## Türkçe (Turkish)

### Modun Amacı ve Ne İşe Yaradığı
**Evolution of the Enemy (EoE) NG**, Skyrim'deki düşmanları ve NPC'leri oyuncunun seviyesine göre dinamik olarak güçlendiren bir SKSE modudur. Oyunun zorluğunu sürekli ve dengeli kılmak amacıyla tasarlanmıştır. Yüksek levellerde bile düşmanlar sizi zorlayacak — artık herkese tek atamazsınız!

Bu mod sayesinde:
- Düşmanların statları, oyuncunun mevcut seviyesine göre dinamik olarak artar.
- **Sadece düşman NPC'ler** etkilenir — takipçiler, tüccarlar ve siviller güçlenmez.
- Hayvanlar (kurt, ayı, örümcek), ejderhalar ve tüm düşman yaratıklar sisteme dahildir.
- Mod, düşmanların ellerindeki silah ve büyülere göre **11 farklı sınıf** tespit eder ve onlara uygun bonuslar verir (Örneğin bir suikastçı çok hızlı koşar, bir tankın devasa canı olur).
- Modlu silahlar (Tüfekler, Mızraklar, Arbaletler) otomatik olarak tanınır ve uygun sınıflara dahil edilir.
- Boss niteliğindeki düşmanlar ve ejderhalar için özel çarpanlar (%50 bonus) devreye girer.

### Sınıf Bazlı Stat Artışları (Yeni Sistem)
Oyun içindeki düşmanlar ellerindeki silahlara göre aşağıdaki 11 sınıftan birine dahil edilir:

| Sınıf Adı | Silah / Büyü | Can | Hasar | Stamina | Mana | Ekstra Özellik |
|:---|:---|:---:|:---:|:---:|:---:|:---|
| **Kalkanlı Tank** | Kalkan | **3.0x** | %0 | 1.0x | - | Sadece hasar emer. |
| **Gürz/Balta Uzmanı** | Tek Elli Balta/Gürz | 2.2x | %20 | 1.5x | - | Kılıca göre ağır hasar. |
| **Savaşçı (Kılıçlı)**| Tek Elli Kılıç | 2.0x | %10 | 1.2x | - | Dengeli eski tank. |
| **Berserker** | Çift Elli Silah | 1.5x | **%60** | 1.5x | - | Yavaş ama ölümcül. |
| **Çift Silah (Dual)** | İki Elde Silah | 1.2x | **%70** | 2.0x | - | +%10 Hız bonusu. |
| **Suikastçı** | Hançer | 0.5x | **%100** | 1.5x | - | +%20 Hız bonusu. |
| **Mızrakçı (Mod)** | Mızrak / Kargı | 1.5x | %30 | 1.5x | - | Orta menzil dövüşçü. |
| **Tüfekçi / Arbalet**| Tüfek / Arbalet | 0.8x | %60 | 0.5x | - | Keskin nişancı. |
| **Okçu** | Yay | 0.8x | %25 | 2.0x | - | Sürekli atış yapar. |
| **Büyülü Şövalye** | Kılıç + Büyü | 1.2x | %15 | - | 1.2x | %15 Büyü hasarı. |
| **Yıkım Büyücüsü** | Yıkım Büyüsü/Asa | 0.1x | - | - | **2.5x** | %40 Büyü hasarı. |
| **Şifacı (Healer)** | İyileştirme Büyüsü | 0.8x | - | - | **3.0x** | %0 Büyü hasarı. |
| **Ölüçağırıcı** | Çağırma Büyüsü | 0.3x | - | - | **3.0x** | %10 Büyü hasarı. |

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
`Data/SKSE/Plugins/DynamicNPCLevelSystem.ini` dosyasıyla taban değerler özelleştirilebilir. (Bu değerler yukarıdaki sınıf çarpanlarıyla çarpılır).
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
**Evolution of the Enemy (EoE) NG** is an SKSE plugin that dynamically scales and buffs enemies and NPCs based on the player's level, ensuring a consistent and balanced challenge throughout your Skyrim playthrough. Even at high levels, enemies will keep you on your toes — no more one-shotting everything!

With this mod:
- Enemy stats are dynamically increased based on the level difference with the player.
- **Only hostile NPCs** are affected — followers, merchants and civilians are not buffed.
- Animals (wolves, bears, spiders), dragons and all hostile creatures are included.
- The mod detects **11 different classes** based on equipped weapons/spells and applies specific stat modifiers (e.g. Assassins run faster, Shield Tanks have massive health).
- Modded weapons (Rifles, Spears, Crossbows) are automatically detected and mapped to appropriate classes.
- Bosses and dragons receive a special multiplier (50% bonus) for truly epic battles.

### Class-Based Stat Multipliers (New System)
Enemies are classified into one of the following 11 classes based on their equipment:

| Class Name | Weapon / Spell | Health | Damage | Stamina | Magicka | Extra Features |
|:---|:---|:---:|:---:|:---:|:---:|:---|
| **Shield Tank** | Shield | **3.0x** | 0% | 1.0x | - | Pure damage sponge. |
| **Axe/Mace Expert** | 1H Axe/Mace | 2.2x | 20% | 1.5x | - | Hits harder than swords. |
| **Warrior (Sword)**| 1H Sword | 2.0x | 10% | 1.2x | - | Balanced melee. |
| **Berserker** | 2H Weapon | 1.5x | **60%** | 1.5x | - | Slow but deadly. |
| **Dual Wield** | Two Weapons | 1.2x | **70%** | 2.0x | - | +10% Speed bonus. |
| **Assassin** | Dagger | 0.5x | **100%** | 1.5x | - | +20% Speed bonus. |
| **Spearman (Mod)**| Spear / Pike | 1.5x | 30% | 1.5x | - | Mid-range fighter. |
| **Rifle / Crossbow**| Rifle / Crossbow| 0.8x | 60% | 0.5x | - | Sniper damage. |
| **Archer** | Bow | 0.8x | 25% | 2.0x | - | Constant fire. |
| **Spellsword** | Sword + Spell | 1.2x | 15% | - | 1.2x | +15% Spell power. |
| **Destruction Mage**| Destruction/Staff| 0.1x | - | - | **2.5x** | +40% Spell power. |
| **Healer** | Restoration | 0.8x | - | - | **3.0x** | +0% Spell power. |
| **Conjurer** | Conjuration | 0.3x | - | - | **3.0x** | +10% Spell power. |

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

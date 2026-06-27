# Dynamic NPC Level System

## Türkçe (Turkish)

### Modun Amacı ve Ne İşe Yaradığı
**Dynamic NPC Level System**, Skyrim'deki düşmanları ve NPC'leri oyuncunun seviyesine göre dinamik olarak güçlendiren bir SKSE modudur. Oyunun zorluğunu sürekli ve dengeli kılmak amacıyla tasarlanmıştır.

Bu mod sayesinde:
- Düşmanların seviyesi, oyuncunun mevcut seviyesine göre yukarı çekilir.
- NPC'lerin **Sağlık, Efsun (Magicka) ve Dayanıklılık (Stamina)** statları, level farkına göre dinamik olarak artar.
- Düşman sınıfları kendi uzmanlıklarına göre ekstra güçlenir:
  - **Tank ve Kılıç kullananlar:** Daha yüksek sağlık değerlerine ve fiziksel hasar direncine sahip olurlar.
  - **Okçu ve Arbalet kullananlar:** Daha yüksek dayanıklılığa (stamina) sahip olurlar.
  - **Büyücüler:** Daha yüksek magicka, büyü hasarı (Destruction) ve büyü direncine sahip olurlar.
- Boss niteliğindeki düşmanlar ve ejderhalar için özel çarpanlar devreye girerek daha efsanevi savaşlar sunulur.

### Uyumluluk
- Mod CommonLibSSE-NG altyapısıyla geliştirildiği için tek bir DLL dosyası ile **Skyrim Special Edition (1.5.97)**, **Skyrim Anniversary Edition (1.6.xx)** ve **Skyrim VR** sürümleriyle tam uyumludur.
- Düşman statlarını değiştiren diğer modlarla çalışabilir; dinamik hesaplamalar mevcut statlar üzerine eklenir. 

### Gereksinimler
- [SKSE64](http://skse.silverlock.org/) (Sürümünüze uygun olan)
- [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)

---

## English (İngilizce)

### Purpose and Features
**Dynamic NPC Level System** is an SKSE plugin that dynamically scales and buffs enemies and NPCs based on the player's level, ensuring a consistent and balanced challenge throughout your Skyrim playthrough.

With this mod:
- Enemy levels are scaled up dynamically to match or exceed the player's level.
- NPCs' **Health, Magicka, and Stamina** stats are dynamically increased based on the level difference.
- Enemy classes gain specific bonuses based on their combat style:
  - **Tanks and Melee Fighters:** Gain higher health pools and physical damage resistance.
  - **Archers and Crossbowmen:** Gain higher stamina pools.
  - **Mages:** Gain higher magicka, destruction spell damage, and magic resistance.
- Bosses and dragons receive special multipliers for truly epic battles.

### Compatibility
- Built with CommonLibSSE-NG, this mod uses a single DLL that is fully compatible with **Skyrim Special Edition (1.5.97)**, **Skyrim Anniversary Edition (1.6.xx)**, and **Skyrim VR**.
- Highly compatible with other mods that modify enemy stats, as the dynamic bonuses are applied on top of existing values.

### Requirements
- [SKSE64](http://skse.silverlock.org/) (Version matching your game)
- [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)

---

## License / Lisans
Copyright (c) 2026 Arif KULPU. All Rights Reserved. — Tüm Hakları Saklıdır. See LICENSE for details.

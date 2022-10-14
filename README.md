# TF2-Weapon-Generator
A Team Fortress 2 weapon generator built from the ground up in C++.   
This generator tries to make *semi*-balanced weapons using a rating system, each stat has a rating, a given number of upsides are calculated and then downsides (or sometimes upsides if the weapon starts out with a rating deficit) are generated until the weapon balances out.

## Changelog: v.0.2.2
- **Added more weapon stats, such as weapon & class specific stats, meters, and some stats that came in pairs, e.g. The Beggar's Bazooka's barrage mechanic.**
- **Added stat flags in order to be able to pair stats together, as well as uphold the rule that all passive upsides must be paired with a passive downside.**
 - **Added the blacklist / whitelist system**
 	- This system makes sure weapons don't have stats that are impossible and / or don't make sense, as well as whitelists stats that are closed off to other weapons.
	- It is split into 4 parts: weapon slot, weapon type, class, & other weapon properties. Each part relates to a different attribute of the weapon. They are split in order to give each part a priority. From lowest to highest, the priotity is as follows: class, slot, properties, type. The priority is used to resolve conflicts if there are multple blacklists for each weapon.
	- This system utilizes the stats used system, changing the values of a stat's corresponding slot to allow / disallow stats from being generated from the get-go.
- **Added new stat categories: Projectile, Exclusive, & Special**
	- **Projectile**: Any stat exclusive to projectile & explosive based weapons e.g. projectile speed, blast radius, etc.
  - **Exclusive**: Any stat that is class or weapon exclusive. The projectile stats are excluded because they all relate to one specific property of the weapon besides the class or weapon type. This category is also already pretty bulky without the projectiles.
  - **Special**: This category does not contain stats, but constructors for special weapons such as coatables and lunchboxes that previously weren't able to be generated correctly. So far we have constructors for Lunchboxes, Battle Banners, coatables, & adding custom meters

- **Added new weapon properties: Has Meter, Projectile, Explosive, Coatable, Throwable, Clipless, Rapid Fire**
	- **Has Meter:** Weapons that already have a meter; e.g. Sniper Rifle, Sheild, etc.
  - **Projectile:** Projectile based weapons (including explosives); e.g. Crossbow, Grendade Launcher, etc.
  - **Explosive:** Projectile based weapons that explode, e.g. Rocket Launcher, Flare Gun, Grenade Launcher.
  - **Coatable:** Weapons that coat players in liquid giving them a debuff; e.g. Non-Milk Substance, Jar-Based Karate, Gas Canister
  - **Throwable:** Like coatables but weapons that can either be thrown or consumed (not always useable); e.g. Cleaver, Battle Banner, Lunchbox, etc.
  - **Clipless:** Weapons that do not have a clip; e.g. Flare Gun, Minigun, Sniper Rifle, etc.
  - **Rapid Fire:** Weapons with a high rate of fire; e.g. Pistol, Minigun, SMG

- **Combined some stats that don't have an upside / downside into one**
	- The stat that is chosen depends on if you're generating an upside or a downside.
  - These stats only add '1' to the used stat system in order to be able to have both stats able to be generated.
- **Updated the stats used system to work with the new blacklist system, new stat categories, & split stats**
- **Added more debugging tools & fixed other bugs**
- **Updated non-exsistant localization files**
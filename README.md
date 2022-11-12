# TF2-Weapon-Generator
A Team Fortress 2 weapon generator built from the ground up in C++.   
This generator tries to make *semi*-balanced weapons using a rating system, each stat has a rating, a given number of upsides are calculated and then downsides (or sometimes upsides if the weapon starts out with a rating deficit) are generated until the weapon balances out.

## Changelog: v.0.2.8

- **Added constructers for Swords, Mediguns, & Invis Watches & modified others**
	- Swords just have their first upside be the range bonus & holder penalty, the Medigun has its uber calculated, and the Invis Watch has its cloak chosen
  - Stat constructers for weapons like Battle Banners & Lunchboxes no longer have a negative stat bonus, instead they have a weapon rating deficit. This fixes issues with stat rating calculation by not having to worry about the weapon's deficit while calculating the stat's rating
- **Added new weapon property: Crit Gimmick**
	- This just shows if the weapon has a crit gimmick or not, and if it does, it will blacklist crit-affecting stats
- **Updated blacklist & stat ratings**
	- When blacklist prints to the console, each entry is now seperated by a newline for easier debugging
- **Stats defined as 'attribute' or 'uncatagorized' now appear before other stats, as well as some others**
- **Changed stat flags so that multiple stat flags can be in play at any given moment (the most recent one added is the one that is active**
- **Changed wording of 'max Overheal' stat to 'maximum overheal'**
- **Slightly decreased rating mod penalty for 'when active' upsides**
- **Fixed some issues with stat flags not being applied**
- **Fixed wearer conditions sometimes not applying to stats due to blank spots in the classSpWearerConditions array**
- **Fixed stats giving debuffs & critical hits vs buildings**
- **Fixed some lunchbox stats not replacing the '$w' word flag and other stats having incorrectly typed word flags**
- **Fixed a bug with stats that redfine the modifier range adjusting it incorrectly, causing stats to have percentage modifiers below 10% (there are no stats in TF2 that are below 10%)**
- **Fixed the rating base being 1 point over the necissary rating when the rating was gotten using word flags**
- **Fixed 'Scout' showing up as an all class melee weapon**
- **Fixed a stat showing up as 'Wearer annot jump' instead of 'Wearer cannot jump'**
- **Fixed some stats stats showing up as -100%, implying you were unable to do ceartian things, e.g. -100% movement speed**
- **Fixed weapons including blank stats**
- **Fixed '-1 jump' stat showing on weapons used by classes other than Scout**
- **Fixed '±1 jump' stats showing as '±1 jumps' (should only be jumps when number is not ±1)**
- **Fixed weapons having both 'deploy' & 'holster' stats and 'switch speed' stats**
- **Fixed stats that have two stats in one slot due to one being only positive and one being only negative showing up twice due to not updating the statsUsed array**
- **Fixed issues with Demoman's shields regarding resistances**
- **Fixed weapons that are like primarys / secondaries not having according chances to be 'when active' (their chances are according to their real weapon slot instead)**
- **Fixed a while loop during seed generation being infinite due to the seed being zero, effectively causing the program to 'freeze'**
- **Fixed debugging tools & other bugs**
- **Updated & balanced some stat ratings**
=======
=======
>>>>>>> origin/main
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
>>>>>>> origin/main

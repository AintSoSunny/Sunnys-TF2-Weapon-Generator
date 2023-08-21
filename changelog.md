# TF2-Weapon-Generator Full Changelog

## v.0.2.8 - November 18th, 2022
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
- **Fixed stat modifier values of 0**
- **Fixed debugging tools & other bugs**
- **Updated & balanced some stat ratings**
- 
## v.0.2.3 - October 17th, 2022
- **Fixed problems with currently implemented special weapon types** (Lunchbox, Shield (Demoman), Battle Banner, Coatable, Meter)
- **Removed 'wet' from list of debuffs**
	- The stat seemed redundant because coatables already make an enemy wet and a wetness immunity sounds extremely situational.
- **Removed 'critical hit chance' from list of stats for conditional increase / decrease**
	-  This was the only way critical hit chance was modified, so there is no stat modifying your critical hit chance, besides 100% chance or zero chance.
- **Removed 'ammo from boxes & dispensers' from list of stats for conditional increase / decrease**
	- The stat is already underwhelming most of the time as an upside, let alone as a conditional upside from things like lunchboxes and banners.
- **Updated blacklist & stat ratings**
- **Fixed debugging tools & other bugs**
- **Localized updation files**
	- This is the last time I'm doing this bit it's getting old lmao
  
## v.0.2.2 - October 14th, 2022 
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

## v.0.2 - September 30th, 2022
- **Finished adding universal weapon stats**

- **Added weapon properties: Wearable, Already Bad**
	- **Wearable:** Weapons that are worn on the body; e.g. Boots, Sheild, etc.
  - **Already Bad:** Weapons that are, well, bad; e.g. Syringe Gun, Gas Canister, etc.
  - **Has Alt-Fire:** Weapons that already have an alt-fire; e.g. Flame Thrower, Minigun, Sniper Rifle, etc.  
  - The first two categories have a modified rating from the start depending on the weapon, such as Boots replacing Demoman's Grenade Launcher will have less of a rating deficit than the Sheild replacing Demoman's Stickybomb Launcher.

- **Added a system to track the stats used on a weapon to make sure duplicate stats are not generated**
	 - The system uses an array of vectors filled with zeros, each slot representing a stat. Once a stat is used, the number is changed to 1.
   - The coordinates of the numbers are reflective of the stat category number and the substat number. For example, attack has a category number of one, and reload time has a substat value of 9, so its co-ordinates are {1,9}.
- **Added non-exsistant localization files**

## v.0.1 - September 23rd, 2022
- **Started adding weapon types as well as basic, universal stats from all of the weapons in Team Fortress 2**
	- Until the blacklist is implemented, some class & weapon specific stats like cloak duration and spin up time will not be included. Weapons like Lunchboxes, Battle Banners, Jars, and Mediguns will also remain

- **Added stat categories: Uncaregorized, Attack, Defense, Utility**
	- **Uncategorized**: Any stat that doesn't fit in the categories and / or does not have any varying values; e.g. The 'Sword Atrribute' (melee range & switch speed), The Machina's 'tracer rounds', etc.
  - **Attack**: Any stat that affects your ability to deal damage, e.g. damage, attack speed, conditional crits & buffs, etc.
  - **Defense**: Any stat that affects your ability to tank damage, e.g. damage resistance, max health, etc.
  - **Utility**: Any stat that affects general uses & aspects of the weapon; e.g. movement speed, switch speed, capture rate, etc

- **Weapon rating system created**
	- Each stat has a seperate rating determined by a base rating, the value modifier, a rating modifier, and a rating bonus / penalty.
  - The complete stats rating is determined by (v * b + s) * m where v = the value modifier, b = the rating base, s = the rating bonus, and m = the rating modifier.
  - The value modifier is a number, usually ranging from 2-20 (some stats have different ranges), determines the number value on the stat, e.g. +20%, -15%, or +4. This modifier is multiplied with the value interval, usually 5, and then displayed on the stat. The value interval does not affect rating. 
  - The base rating is from the stat's template. For example, a damage bonus / penalty has a base rating of 5. Most of the rating system uses this as a baseline. More complex stats, such as conditional crits / minicrits, can have multiple base ratings determined by, in this case, which type of crits are used.
  - The stat modifier affects the rating of a weapon, usually determined by a condition or property of a stat, such as 'vs burning players'.
  - The stat bonus is currently unused but it will add or subtract a flat value to the rating before the weapon modifier is applied.
  - The weapon stats are calculated by generating a given number of upsides, and then generating downsides until the weapon is 'balanced', or the rating is in a range of 5 to -5.

- **Randomly generated the localization files**